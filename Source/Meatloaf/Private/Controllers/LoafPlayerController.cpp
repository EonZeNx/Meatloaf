// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/LoafPlayerController.h"

#include "Characters/Data/LoafPlayerState.h"
#include "Components/InputComponent.h"
#include "Interfaces/BasicMovement.h"
#include "Kismet/KismetMathLibrary.h"


ALoafPlayerController::ALoafPlayerController()
{
	/** CONTROLLER **/
	ControllerUpperPitchLimit = 70.f;
	ControllerLowerPitchLimit = -70.f;
	ControllerUpperYawLimit = 179.99f;
	ControllerLowerYawLimit = -179.99f;
	
	/** INPUT **/
	MouseXSensitivity = 0.33f;
	MouseYSensitivity = 0.33f;
}

void ALoafPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	/** ACTIONS **/
	// Basic Movement actions.
	InputComponent->BindAction("Jump", IE_Pressed, this, &ALoafPlayerController::CustomJump);
	
	InputComponent->BindAction("ToggleSprint", IE_Pressed, this, &ALoafPlayerController::ToggleSprint);
	InputComponent->BindAction("HoldSprint", IE_Pressed, this, &ALoafPlayerController::StartSprint);
	InputComponent->BindAction("HoldSprint", IE_Released, this, &ALoafPlayerController::StopSprint);
	
	InputComponent->BindAction("ToggleCrouch", IE_Pressed, this, &ALoafPlayerController::ToggleCrouch);
	InputComponent->BindAction("HoldCrouch", IE_Pressed, this, &ALoafPlayerController::StartCrouch);
	InputComponent->BindAction("HoldCrouch", IE_Released, this, &ALoafPlayerController::StopCrouch);
}


/** AXES **/
void ALoafPlayerController::LookYaw(float Value)
{
	const float Actual = Value * MouseXSensitivity;
	AddYawInput(Actual);
}

void ALoafPlayerController::LookPitch(float Value)
{
	const float Actual = Value * MouseYSensitivity;
	AddPitchInput(Actual);
}


/** ACTIONS **/
/* Jump */
void ALoafPlayerController::CustomJump()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_CustomJump(GetPawn());
	}
}


/* Sprint */
void ALoafPlayerController::ToggleSprint()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_ToggleSprint(GetPawn());
	}
}

void ALoafPlayerController::StartSprint()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StartSprint(GetPawn());
	}
}

void ALoafPlayerController::StopSprint()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StopSprint(GetPawn());
	}
}


/* Crouch */
void ALoafPlayerController::ToggleCrouch()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_ToggleCrouch(GetPawn());
	}
}

void ALoafPlayerController::StartCrouch()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StartCrouch(GetPawn());
	}
}

void ALoafPlayerController::StopCrouch()
{
	if (bPawnImplementsBasicMovement)
	{
		IBasicMovement::Execute_StopCrouch(GetPawn());
	}
}


/** OVERRIDES **/
void ALoafPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	bPawnImplementsBasicMovement = GetPawn()->GetClass()->ImplementsInterface(UBasicMovement::StaticClass());

	ALoafPlayerState* PS = GetPlayerState<ALoafPlayerState>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
}

void ALoafPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void ALoafPlayerController::Tick(float DeltaTime)
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
