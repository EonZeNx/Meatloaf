// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LoafCharacter.h"

#include "GAS/LoafAbilitySystemComponent.h"
#include "GAS/LoafGameplayAbility.h"
#include "GAS/LoafAttributeSet.h"
#include "GameplayEffectTypes.h"


ALoafCharacter::ALoafCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	/** REFERENCES **/
	CMC = GetCharacterMovement();

	/** MOVEMENT **/
	SprintSpeed = 750.f;
	RunSpeed = 500.f;
	CrouchSpeed = 350.f;

	bIsSprinting = false;
	bIsCrouching = false;

	/** STANCE **/
	StandingCapsuleHalfHeight = 88.f;
	StandingCapsuleRadius = 34.f;
	CrouchingCapsuleHalfHeight = 44.f;
	CrouchingCapsuleRadius = 34.f;
	
	/* Stance timings */
	CrouchTransitionTime = 0.2f;
	CurrentCrouchTransitionTime = 0.f;

	/** JUMP **/
	JumpScalar = 750.f;
	MaxAirJumps = 1;
	CurrentAirJumps = 0;

	/** GAS **/
	ASC = CreateDefaultSubobject<ULoafAbilitySystemComponent>("ASC");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<ULoafAttributeSet>("Attributes");
}


/** OVERRIDES **/
void ALoafCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALoafCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server GAS init
	// ASC->InitAbilityActorInfo(this, this);
	ASC->InitAbilityActorInfo(NewController, this);

	InitAttributes();
	GiveAbilities();
}

void ALoafCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ASC->InitAbilityActorInfo(this, this);
	InitAttributes();

	if (ASC && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ELoafAbilityInputID",
            static_cast<int32>(ELoafAbilityInputID::Confirm),
            static_cast<int32>(ELoafAbilityInputID::Cancel));
		
		ASC->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ALoafCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// May get called in an init state where one is not setup yet.
	if (ASC && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ELoafAbilityInputID",
            static_cast<int32>(ELoafAbilityInputID::Confirm),
            static_cast<int32>(ELoafAbilityInputID::Cancel));
		
		ASC->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ALoafCharacter::Landed(const FHitResult& Hit)
{
	CurrentAirJumps = 0;
}

void ALoafCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/** FUNCTIONS **/

/** MOVEMENT **/
void ALoafCharacter::MoveForBack_Implementation(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ALoafCharacter::MoveLeftRight_Implementation(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

/** ACTIONS **/
void ALoafCharacter::CustomJump_Implementation()
{
	if (CMC->IsFalling() && CurrentAirJumps >= MaxAirJumps) return;
	
	FVector JumpForce = FVector(0, 0, 1);

	JumpForce = JumpForce * JumpScalar;
	LaunchCharacter(JumpForce, false, false);

	if (CMC->IsFalling()) CurrentAirJumps++;
}

/* Sprint */
void ALoafCharacter::ToggleSprint_Implementation()
{
	if (bIsSprinting) {
		StopSprint_Implementation();
	}
	else {
		StartSprint_Implementation();
	}
}

void ALoafCharacter::StartSprint_Implementation()
{
	if (bIsSprinting) { return; }

	StopCrouch_Implementation();
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void ALoafCharacter::StopSprint_Implementation()
{
	if (!bIsSprinting) { return; }

	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

/* Crouch */
void ALoafCharacter::ToggleCrouch_Implementation()
{
	if (bIsCrouching) {
		StopCrouch_Implementation();
	}
	else {
		StartCrouch_Implementation();
	}
}

void ALoafCharacter::StartCrouch_Implementation()
{
	if (bIsCrouching) { return; }

	StopSprint_Implementation();
	CurrentCrouchTransitionTime = 0.f;
	bIsCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}

void ALoafCharacter::StopCrouch_Implementation()
{
	if (!bIsCrouching) { return; }

	CurrentCrouchTransitionTime = CrouchTransitionTime;
	bIsCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}


/** GAS **/
class UAbilitySystemComponent* ALoafCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void ALoafCharacter::InitAttributes()
{
	if (ASC && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);

		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ALoafCharacter::GiveAbilities()
{
	// if (HasAuthority() && ASC) { }
	if (!HasAuthority() || !ASC) return;

	for(TSubclassOf<ULoafGameplayAbility>& StartupAbility : DefaultAbilities)
	{
		ASC->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}
}
