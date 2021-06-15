// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BasicMovement.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBasicMovement : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEATLOAF_API IBasicMovement
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void MoveForBack(float value);

	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void MoveLeftRight(float value);

	
	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void CustomJump();

	
	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void ToggleSprint();

	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void StartSprint();

	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void StopSprint();

	
	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void ToggleCrouch();

	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void StartCrouch();

	UFUNCTION(BlueprintNativeEvent, Category = "Basic Movement Interface")
    void StopCrouch();
};
