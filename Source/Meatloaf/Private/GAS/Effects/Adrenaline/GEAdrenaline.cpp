// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Adrenaline/GEAdrenaline.h"

#include "GAS/LoafAttributeSet.h"


UGEAdrenaline::UGEAdrenaline()
{
	DurationPolicy = EGameplayEffectDurationType::HasDuration;
	DurationMagnitude = FScalableFloat(5.f);
	
	const FGameplayTag ActiveTag = FGameplayTag::RequestGameplayTag("State.Skill.Adrenaline.Active");
	InheritableOwnedTagsContainer.AddTag(ActiveTag);

	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo MaxMoveSpeed = FGameplayModifierInfo();
	MaxMoveSpeed.Attribute = ULoafAttributeSet::GetMaxMoveSpeedAttribute();
	MaxMoveSpeed.ModifierOp = EGameplayModOp::Multiplicitive;
	MaxMoveSpeed.ModifierMagnitude = FScalableFloat(2);

	Modifiers.Add(MaxMoveSpeed);
}
