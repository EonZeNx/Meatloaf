// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * Basic player controller
 */
UCLASS()
class MEATLOAF_API ACustomPlayerController : public APlayerController
{
private:
	GENERATED_BODY()

	/* VARIABLES */
public:
protected:
	/* References */
	bool bPawnImplementsBasicMovement;

	/* Controller */
	float ControllerPitchLimit;
	float ControllerYawLimit;
	
	/* Input */
	float MouseXSensitivity;
	float MouseYSensitivity;
	
private:

	/* FUNCTIONS */
public:
	ACustomPlayerController();
	
protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	/* AXES */
	void LookYaw(float value);
	void LookPitch(float value);
	
	void MoveForwardBackward(float value);
	void MoveLeftRight(float value);

	/* ACTIONS */
	void CustomJump();
	
	void ToggleSprint();
	void StartSprint();
	void StopSprint();

	void ToggleCrouch();
	void StartCrouch();
	void StopCrouch();
};
