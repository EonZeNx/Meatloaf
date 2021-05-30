// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CustomPlayerController.h"
#include "Components/InputComponent.h"
#include "Interfaces/BasicMovement.h"


ACustomPlayerController::ACustomPlayerController()
{
	/* Input */
	MouseXSensitivity = 0.33f;
	MouseYSensitivity = 0.33f;

	/* Camera */
	ControllerPitchLimit = 70.f;
	ControllerYawLimit = 359.99f;
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/** Axes */
	InputComponent->BindAxis("LookYaw", this, &ACustomPlayerController::LookYaw);
	InputComponent->BindAxis("LookPitch", this, &ACustomPlayerController::LookPitch);

	InputComponent->BindAxis("MoveForwardBackward", this, &ACustomPlayerController::MoveForwardBackward);
	InputComponent->BindAxis("MoveLeftRight", this, &ACustomPlayerController::MoveLeftRight);

	/** Actions */
	// Basic Movement actions.
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACustomPlayerController::CustomJump);
	
	InputComponent->BindAction("ToggleSprint", IE_Pressed, this, &ACustomPlayerController::ToggleSprint);
	InputComponent->BindAction("HoldSprint", IE_Pressed, this, &ACustomPlayerController::StartSprint);
	InputComponent->BindAction("HoldSprint", IE_Released, this, &ACustomPlayerController::StopSprint);
	
	InputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &ACustomPlayerController::ToggleCrouch);
	InputComponent->BindAction("HoldCrouch", IE_Pressed, this, &ACustomPlayerController::StartCrouch);
	InputComponent->BindAction("HoldCrouch", IE_Released, this, &ACustomPlayerController::StopCrouch);
}


/* Camera */
void ACustomPlayerController::LookYaw(float value)
{
	const float Actual = value * MouseXSensitivity;
	if (FMath::Abs(ControlRotation.Yaw + Actual) > ControllerYawLimit) return;
	
	AddYawInput(Actual);
}

void ACustomPlayerController::LookPitch(float value)
{
	const float Actual = value * MouseYSensitivity;
	if (FMath::Abs(ControlRotation.Pitch + Actual) > ControllerPitchLimit) return;
	
	AddPitchInput(Actual);
}


// Movement functions
void ACustomPlayerController::MoveForwardBackward(float value)
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_MoveForBack(GetPawn(), value);
	}
}

void ACustomPlayerController::MoveLeftRight(float value)
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_MoveLeftRight(GetPawn(), value);
	}
}

void ACustomPlayerController::CustomJump()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_CustomJump(GetPawn());
	}
}


// Sprint
void ACustomPlayerController::ToggleSprint()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_ToggleSprint(GetPawn());
	}
}

void ACustomPlayerController::StartSprint()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StartSprint(GetPawn());
	}
}

void ACustomPlayerController::StopSprint()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StopSprint(GetPawn());
	}
}


// Crouch
void ACustomPlayerController::ToggleCrouch()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_ToggleCrouch(GetPawn());
	}
}

void ACustomPlayerController::StartCrouch()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StartCrouch(GetPawn());
	}
}

void ACustomPlayerController::StopCrouch()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StopCrouch(GetPawn());
	}
}


// Misc
void ACustomPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	bPawnImplementsBasicMovement = GetPawn()->GetClass()->ImplementsInterface(UBasicMovement::StaticClass());
}