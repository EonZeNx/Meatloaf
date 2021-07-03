// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GAS/LoafGameplayAbility.h"
#include "GAAdrenaline.generated.h"


class UAbilityTask_WaitGameplayEffectRemoved;
UCLASS()
class MEATLOAF_API UGAAdrenaline : public ULoafGameplayAbility
{
	GENERATED_BODY()

public:
	UGAAdrenaline();
	
	FActiveGameplayEffectHandle GEAdrenalineHandle;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void CancelAbilityDelegate(const FGameplayEffectRemovalInfo& GameplayEffectRemovalInfo);
	void StoreAbilityValues(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);

private:
	bool EffectEnded = false;

	UPROPERTY()
	UAbilityTask_WaitGameplayEffectRemoved* WGERAdrenaline;
	TScriptDelegate<> DelegateCancel;

	FGameplayAbilitySpecHandle ThisHandle;
	const FGameplayAbilityActorInfo* ThisActorInfo;
	FGameplayAbilityActivationInfo ThisActivationInfo;
};
