// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/LoafGasStates.h"

#include "LoafGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MEATLOAF_API ULoafGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:
	ULoafGameplayAbility();

	// Abilities with this set will auto activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	ELoafAbilityInputID AbilityInputID = ELoafAbilityInputID::None;
};
