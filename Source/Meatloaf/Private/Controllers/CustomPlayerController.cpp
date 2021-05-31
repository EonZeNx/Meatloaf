// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/CustomPlayerController.h"
#include "Components/InputComponent.h"
#include "Interfaces/BasicMovement.h"
#include "Kismet/KismetMathLibrary.h"


ACustomPlayerController::ACustomPlayerController()
{
	/* Input */
	MouseXSensitivity = 0.33f;
	MouseYSensitivity = 0.33f;

	/* Camera */
	ControllerUpperPitchLimit = 70.f;
	ControllerLowerPitchLimit = -70.f;
	ControllerUpperYawLimit = 179.99f;
	ControllerLowerYawLimit = -179.99f;
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
	AddYawInput(Actual);
}

void ACustomPlayerController::LookPitch(float value)
{
	const float Actual = value * MouseYSensitivity;
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

void ACustomPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APawn* WorldPawn = GetPawn())
	{
		const FRotator PawnRotation = WorldPawn->GetActorRotation();

		const float NewPitchMin = FRotator::NormalizeAxis(ControllerLowerPitchLimit + PawnRotation.Pitch);
		if (PlayerCameraManager->ViewPitchMin != NewPitchMin)
			PlayerCameraManager->ViewPitchMin = UKismetMathLibrary::FInterpTo(PlayerCameraManager->ViewPitchMin, NewPitchMin, DeltaTime, 5.f);

		const float NewPitchMax = FRotator::NormalizeAxis(ControllerUpperPitchLimit + PawnRotation.Pitch);
		if (PlayerCameraManager->ViewPitchMax != NewPitchMax)
			PlayerCameraManager->ViewPitchMax = UKismetMathLibrary::FInterpTo(PlayerCameraManager->ViewPitchMax, NewPitchMax, DeltaTime, 5.f);
	}
}