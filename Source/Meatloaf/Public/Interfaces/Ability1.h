// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability1.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAbility1 : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEATLOAF_API IAbility1
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Ability Interface")
    void ActivateAbility1();

	UFUNCTION(BlueprintNativeEvent, Category = "Ability Interface")
    void DeactivateAbility1();
};
