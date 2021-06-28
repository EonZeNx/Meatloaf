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
}
