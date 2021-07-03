// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Sprint/GESprint.h"
#include "GAS/LoafAttributeSet.h"


UGESprint::UGESprint()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;

	const FGameplayTag ActiveTag = FGameplayTag::RequestGameplayTag("State.Skill.Sprint.Active", true);
	InheritableOwnedTagsContainer.AddTag(ActiveTag);
	
	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo MaxMoveSpeed = FGameplayModifierInfo();
	MaxMoveSpeed.Attribute = ULoafAttributeSet::GetMaxMoveSpeedAttribute();
	MaxMoveSpeed.ModifierOp = EGameplayModOp::Additive;
	MaxMoveSpeed.ModifierMagnitude = FScalableFloat(SprintAdditiveValue);

	Modifiers.Add(MaxMoveSpeed);
}
