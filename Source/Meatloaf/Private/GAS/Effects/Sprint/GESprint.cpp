// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Sprint/GESprint.h"
#include "GAS/LoafAttributeSet.h"


UGESprint::UGESprint()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	InheritableOwnedTagsContainer = FInheritedTagContainer();

	FInheritedTagContainer NewAdded = FInheritedTagContainer();
	NewAdded.AddTag(FGameplayTag::RequestGameplayTag("State.Sprinting"));
	InheritableOwnedTagsContainer = NewAdded;
	
	FGameplayTagContainer AddedTags = FGameplayTagContainer();
	AddedTags.AddTagFast(FGameplayTag::RequestGameplayTag("State.Sprinting"));
	InheritableOwnedTagsContainer.Added = AddedTags;

	// TODO: This is not removing the modifer from the value on CancelAbility
	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo MaxMoveSpeed = FGameplayModifierInfo();
	MaxMoveSpeed.Attribute = ULoafAttributeSet::GetMaxMoveSpeedAttribute();
	MaxMoveSpeed.ModifierOp = EGameplayModOp::Additive;
	MaxMoveSpeed.ModifierMagnitude = FScalableFloat(256);

	Modifiers.Add(MaxMoveSpeed);
}
