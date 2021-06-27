// Fill out your copyright notice in the Description page of Project Settings.

#include "Gas/Abilities/GA_CharacterJump.h"

#include "Characters/LoafCharacter.h"
#include "GAS/Data/LoafGasStates.h"


UGA_CharacterJump::UGA_CharacterJump()
{
	AbilityInputID = ELoafAbilityInputID::Jump;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
}

void UGA_CharacterJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}

		ALoafCharacter* LoafCharacter = CastChecked<ALoafCharacter>(ActorInfo->AvatarActor.Get());
		LoafCharacter->CustomJump_Implementation();
	}
}

bool UGA_CharacterJump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) { return false; }

	const ALoafCharacter* LoafCharacter = CastChecked<ALoafCharacter>(ActorInfo->AvatarActor.Get(), ECastCheckedType::NullAllowed);
	return LoafCharacter && (
		LoafCharacter->GetCurrentJumps() < LoafCharacter->GetMaxJumps() || !LoafCharacter->IsFalling()
	);
}

void UGA_CharacterJump::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

void UGA_CharacterJump::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	if (ScopeLockCount > 0)
	{
		WaitingToExecute.Add(FPostLockDelegate::CreateUObject(this, &UGA_CharacterJump::CancelAbility, Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility));
		return;
	}

	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	ALoafCharacter* Character = CastChecked<ALoafCharacter>(ActorInfo->AvatarActor.Get());
	Character->StopJumping();
}
