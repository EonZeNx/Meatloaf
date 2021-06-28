// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Adrenaline/GEAdrenaline.h"

#include "GAS/LoafAttributeSet.h"


UGEAdrenaline::UGEAdrenaline()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	InheritableOwnedTagsContainer = FInheritedTagContainer();

	FInheritedTagContainer NewAdded = FInheritedTagContainer();
	NewAdded.AddTag(FGameplayTag::RequestGameplayTag("Effect.Skill.Adrenaline"));
	InheritableOwnedTagsContainer = NewAdded;
	
	FGameplayTagContainer AddedTags = FGameplayTagContainer();
	AddedTags.AddTagFast(FGameplayTag::RequestGameplayTag("Effect.Skill.Adrenaline"));
	InheritableOwnedTagsContainer.Added = AddedTags;

	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo MaxMoveSpeed = FGameplayModifierInfo();
	MaxMoveSpeed.Attribute = ULoafAttributeSet::GetMaxMoveSpeedAttribute();
	MaxMoveSpeed.ModifierOp = EGameplayModOp::Multiplicitive;
	MaxMoveSpeed.ModifierMagnitude = FScalableFloat(2);

	Modifiers.Add(MaxMoveSpeed);
}
