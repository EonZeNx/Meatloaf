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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Yaw")
	float ControllerUpperYawLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Yaw")
	float ControllerLowerYawLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Pitch")
	float ControllerUpperPitchLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit|Pitch")
	float ControllerLowerPitchLimit;
	
	/* Input */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MouseXSensitivity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MouseYSensitivity;
	
private:

	/* FUNCTIONS */
public:
	ACustomPlayerController();
	
protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	
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
