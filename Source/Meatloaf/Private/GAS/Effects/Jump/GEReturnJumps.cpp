// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Jump/GEReturnJumps.h"
#include "GAS/LoafAttributeSet.h"


UGEReturnJumps::UGEReturnJumps()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo UseJump = FGameplayModifierInfo();
	UseJump.Attribute = ULoafAttributeSet::GetCurrentJumpsAttribute();
	UseJump.ModifierOp = EGameplayModOp::Override;
	UseJump.ModifierMagnitude = FScalableFloat(0.f);

	Modifiers.Add(UseJump);
}
