// Fill out your copyright notice in the Description page of Project Settings.

#include "Gas/Abilities/GASprint.h"

#include "Characters/LoafCharacter.h"
#include "GAS/Data/LoafGasStates.h"
#include "GAS/Effects/Sprint/GESprint.h"
#include "GAS/Effects/Sprint/GESprintRemoval.h"


UGASprint::UGASprint()
{
	AbilityInputID = ELoafAbilityInputID::Sprint;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Sprint")));

	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Sprinting")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.SprintingRemoval")));
}

void UGASprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo)) return;

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	UGESprint* GESprint = NewObject<UGESprint>();
	GESprintingHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GESprint, 1.0f);
}

bool UGASprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) { return false; }

	const ALoafCharacter* LoafCharacter = CastChecked<ALoafCharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return LoafCharacter->IsValidLowLevelFast();
}

void UGASprint::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UGASprint::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGASprint::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
		return;
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	// GESprintRemoval is for client prediction, as it cannot predict we are going to remove a gameplay tag.
	// This allows us to block sprinting on the client before the Server replies with its sprint removal confirmation.
	UGESprintRemoval* GESprintRemoval =  NewObject<UGESprintRemoval>();
	const FActiveGameplayEffectHandle GESprintingRemovalHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, GESprintRemoval, 1.0f);

	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(GESprintingHandle);
	ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(GESprintingRemovalHandle);
}
