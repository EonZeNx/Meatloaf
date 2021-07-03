// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Sprint/GESprint.h"
#include "GAS/LoafAttributeSet.h"
#include "Meatloaf/Meatloaf.h"


UGESprint::UGESprint()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;

	const FGameplayTag ActiveTag = FGameplayTag::RequestGameplayTag("State.Skill.Sprint.Active", true);
	InheritableOwnedTagsContainer.AddTag(ActiveTag);

	const bool HasTagAdded = InheritableOwnedTagsContainer.Added.HasTag(ActiveTag);
	DebugMsg(FString::Printf(TEXT("HasTag: %hs"), HasTagAdded ? "True" : "False"));
	
	Modifiers = TArray<FGameplayModifierInfo>();

	FGameplayModifierInfo MaxMoveSpeed = FGameplayModifierInfo();
	MaxMoveSpeed.Attribute = ULoafAttributeSet::GetMaxMoveSpeedAttribute();
	MaxMoveSpeed.ModifierOp = EGameplayModOp::Additive;
	MaxMoveSpeed.ModifierMagnitude = FScalableFloat(SprintAdditiveValue);

	Modifiers.Add(MaxMoveSpeed);
}
