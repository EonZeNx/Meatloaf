// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GAS_AttributeSet.h"
#include "Net/UnrealNetwork.h"


UGAS_AttributeSet::UGAS_AttributeSet()
{
	
}

void UGAS_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSet, JumpPower, COND_None, REPNOTIFY_Always);
}

void UGAS_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, Health, OldHealth);
}

void UGAS_AttributeSet::OnRep_JumpPower(const FGameplayAttributeData& OldJumpPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSet, JumpPower, OldJumpPower);
}
