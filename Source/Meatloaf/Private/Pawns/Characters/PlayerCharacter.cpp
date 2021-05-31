// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Characters/PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/** References. **/
	/* A reference to the owners' movement component. */
	CMC = GetCharacterMovement();
	
	/* Default sprint speed */
	SprintSpeed = 750.f;
	/* Default run speed */
	RunSpeed = 500.f;
	/* Default crouch speed */
	CrouchSpeed = 350.f;

	/* Whether or not the character is sprinting */
	bIsSprinting = false;
	/* Whether or not the character is crouching */
	bIsCrouching = false;

	/** Stance config. **/
	StandingCapsuleHalfHeight = 88.f;
	StandingCapsuleRadius = 34.f;
	CrouchingCapsuleHalfHeight = 44.f;
	CrouchingCapsuleRadius = 34.f;
	
	/* Stance timings. */
	CrouchTransitionTime = 0.2f;
	CurrentCrouchTransitionTime = 0.f;

	/** Jump config. */
	JumpScalar = 550.f;
	MaxAirJumps = 1;
	CurrentAirJumps = MaxAirJumps;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


// Functions
void APlayerCharacter::MoveForBack_Implementation(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void APlayerCharacter::MoveLeftRight_Implementation(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void APlayerCharacter::CustomJump_Implementation()
{
	FVector JumpForce = FVector(0, 0, 1);

	JumpForce = JumpForce * JumpScalar;
	LaunchCharacter(JumpForce, false, false);
}

// Sprint
void APlayerCharacter::ToggleSprint_Implementation()
{
	if (bIsSprinting) {
		StopSprint_Implementation();
	}
	else {
		StartSprint_Implementation();
	}
}

void APlayerCharacter::StartSprint_Implementation()
{
	if (bIsSprinting) { return; }

	StopCrouch_Implementation();
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APlayerCharacter::StopSprint_Implementation()
{
	if (!bIsSprinting) { return; }

	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

// Crouch
void APlayerCharacter::ToggleCrouch_Implementation()
{
	if (bIsCrouching) {
		StopCrouch_Implementation();
	}
	else {
		StartCrouch_Implementation();
	}
}

void APlayerCharacter::StartCrouch_Implementation()
{
	if (bIsCrouching) { return; }

	StopSprint_Implementation();
	CurrentCrouchTransitionTime = 0.f;
	bIsCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}

void APlayerCharacter::StopCrouch_Implementation()
{
	if (!bIsCrouching) { return; }

	CurrentCrouchTransitionTime = CrouchTransitionTime;
	bIsCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}
