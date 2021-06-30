// Fill out your copyright notice in the Description page of Project Settings.

#include "Gas/Abilities/GAAdrenaline.h"

#include "Characters/LoafCharacter.h"
#include "GAS/Data/LoafGasStates.h"
#include "GAS/Effects/Adrenaline/GEAdrenaline.h"
#include "GAS/Effects/Adrenaline/GEAdrenalineRemoval.h"


UGAAdrenaline::UGAAdrenaline()
{
	AbilityInputID = ELoafAbilityInputID::Adrenaline;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Adrenaline")));

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.Skill.Adrenaline")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Effect.Skill.AdrenalineRemoval")));
}

void UGAAdrenaline::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) return;

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	UGEAdrenaline* GEAdrenaline = NewObject<UGEAdrenaline>();
	GEAdrenalineHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GEAdrenaline, 1.0f);
}

bool UGAAdrenaline::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) { return false; }

	const ALoafCharacter* LoafCharacter = CastChecked<ALoafCharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return LoafCharacter->IsValidLowLevelFast();
}

void UGAAdrenaline::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	// TODO: Do not cancel the ability on input released
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UGAAdrenaline::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGAAdrenaline::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
		return;
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	// GEAdrenalineRemoval is for client prediction, as it cannot predict we are going to remove a gameplay tag.
	// This allows us to block adrenaline on the client before the Server replies with its adrenaline removal confirmation.
	UGEAdrenalineRemoval* GEAdrenalineRemoval = NewObject<UGEAdrenalineRemoval>();
	const FActiveGameplayEffectHandle GEAdrenalineRemovalHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GEAdrenalineRemoval, 1.0f);

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(GEAdrenalineHandle);
	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(GEAdrenalineRemovalHandle);
}
