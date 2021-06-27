// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/GEUseJump.h"

#include "GAS/LoafAttributeSet.h"

UGEUseJump::UGEUseJump()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo UseJump = FGameplayModifierInfo();
	UseJump.Attribute = ULoafAttributeSet::GetCurrentJumpsAttribute();
	UseJump.ModifierOp = EGameplayModOp::Additive;
	UseJump.ModifierMagnitude = FScalableFloat(1);

	Modifiers.Add(UseJump);
}
