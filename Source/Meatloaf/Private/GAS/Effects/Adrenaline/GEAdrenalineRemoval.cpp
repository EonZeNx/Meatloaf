// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Effects/Adrenaline/GEAdrenalineRemoval.h"

#include "GAS/LoafAttributeSet.h"


UGEAdrenalineRemoval::UGEAdrenalineRemoval()
{
	DurationPolicy = EGameplayEffectDurationType::Infinite;
	InheritableOwnedTagsContainer = FInheritedTagContainer();

	const FGameplayTag RemovalTag = FGameplayTag::RequestGameplayTag("State.Skill.Adrenaline.PendingRemoval");
	InheritableOwnedTagsContainer.AddTag(RemovalTag);
}
