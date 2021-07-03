// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Sprint/GESprintRemoval.h"
#include "GAS/LoafAttributeSet.h"


UGESprintRemoval::UGESprintRemoval()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;

	const FGameplayTag RemovalTag = FGameplayTag::RequestGameplayTag("State.Skill.Sprint.PendingRemoval", true);
	InheritableOwnedTagsContainer.AddTag(RemovalTag);
}
