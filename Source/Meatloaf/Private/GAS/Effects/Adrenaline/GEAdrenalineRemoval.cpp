// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Adrenaline/GEAdrenalineRemoval.h"

#include "GAS/LoafAttributeSet.h"


UGEAdrenalineRemoval::UGEAdrenalineRemoval()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	InheritableOwnedTagsContainer = FInheritedTagContainer();

	FInheritedTagContainer NewAdded = FInheritedTagContainer();
	NewAdded.AddTag(FGameplayTag::RequestGameplayTag("Effect.Skill.AdrenalineRemoval"));
	InheritableOwnedTagsContainer = NewAdded;
	
	FGameplayTagContainer AddedTags = FGameplayTagContainer();
	AddedTags.AddTagFast(FGameplayTag::RequestGameplayTag("Effect.Skill.AdrenalineRemoval"));
	InheritableOwnedTagsContainer.Added = AddedTags;
}