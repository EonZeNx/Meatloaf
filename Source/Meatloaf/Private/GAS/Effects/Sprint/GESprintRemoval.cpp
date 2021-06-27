// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Sprint/GESprintRemoval.h"
#include "GAS/LoafAttributeSet.h"


UGESprintRemoval::UGESprintRemoval()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	InheritableOwnedTagsContainer = FInheritedTagContainer();

	FGameplayTagContainer AddedTags = FGameplayTagContainer();
	AddedTags.AddTag(FGameplayTag::RequestGameplayTag("State.SprintingRemoval"));
	InheritableOwnedTagsContainer.Added = AddedTags;
	
	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo MaxMoveSpeed = FGameplayModifierInfo();
	MaxMoveSpeed.Attribute = ULoafAttributeSet::GetMaxMoveSpeedAttribute();
	MaxMoveSpeed.ModifierOp = EGameplayModOp::Additive;
	MaxMoveSpeed.ModifierMagnitude = FScalableFloat(-256);

	Modifiers.Add(MaxMoveSpeed);
}
