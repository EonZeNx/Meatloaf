// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Data/GAS_States.h"

#include "GAS_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MEATLOAF_API UGAS_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:
	UGAS_GameplayAbility();

	// Abilities with this set will auto activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	EGasAbilityInputID AbilityInputID = EGasAbilityInputID::None;
};
