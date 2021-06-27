// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoafPlayerController.generated.h"

/**
 * Basic player controller
 */
UCLASS()
class MEATLOAF_API ALoafPlayerController : public APlayerController
{
	GENERATED_BODY()

/** VARIABLES **/
protected:
	/** REFERENCES **/
	bool bPawnImplementsBasicMovement;

	/** CONTROLLER **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Yaw")
	float ControllerUpperYawLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Yaw")
	float ControllerLowerYawLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Pitch")
	float ControllerUpperPitchLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Pitch")
	float ControllerLowerPitchLimit;
	
	/** INPUT **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MouseXSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MouseYSensitivity;
	
private:

/** FUNCTIONS **/
public:
	ALoafPlayerController();
	
	/** AXES **/
	void LookYaw(float value);
	void LookPitch(float value);
	
	
protected:
	/** OVERRIDES **/
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;
	
private:
	/** ACTIONS **/
	void CustomJump();
	
	void ToggleSprint();
	void StartSprint();
	void StopSprint();

	void ToggleCrouch();
	void StartCrouch();
	void StopCrouch();
};
