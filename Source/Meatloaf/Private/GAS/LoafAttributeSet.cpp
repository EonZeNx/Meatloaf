// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/LoafAttributeSet.h"
#include "Net/UnrealNetwork.h"


ULoafAttributeSet::ULoafAttributeSet()
{
	
}

void ULoafAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULoafAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULoafAttributeSet, JumpPower, COND_None, REPNOTIFY_Always);
}

void ULoafAttributeSet::OnRep_CharacterLevel(const FGameplayAttributeData& OldCharacterLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULoafAttributeSet, CharacterLevel, OldCharacterLevel);
}

void ULoafAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULoafAttributeSet, Health, OldHealth);
}

void ULoafAttributeSet::OnRep_JumpPower(const FGameplayAttributeData& OldJumpPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULoafAttributeSet, JumpPower, OldJumpPower);
}

void ULoafAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULoafAttributeSet, MaxHealth, OldMaxHealth);
}

void ULoafAttributeSet::OnRep_MaxJumpPower(const FGameplayAttributeData& OldMaxJumpPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULoafAttributeSet, MaxJumpPower, OldMaxJumpPower);
}

