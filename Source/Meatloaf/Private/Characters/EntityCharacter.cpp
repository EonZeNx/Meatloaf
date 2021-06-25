// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EntityCharacter.h"

#include "GAS/GAS_AbilitySystemComponent.h"
#include "GAS/GAS_GameplayAbility.h"
#include "GAS/GAS_AttributeSet.h"
#include "GameplayEffectTypes.h"


// Sets default values
AEntityCharacter::AEntityCharacter()
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
	JumpScalar = 750.f;
	MaxAirJumps = 1;
	CurrentAirJumps = 0;

	/* GAS */
	ASC = CreateDefaultSubobject<UGAS_AbilitySystemComponent>("ASC");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<UGAS_AttributeSet>("Attributes");
}

// Called when the game starts or when spawned
void AEntityCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEntityCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEntityCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// May get called in an init state where one is not setup yet.
	if (ASC && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGasAbilityInputID",
            static_cast<int32>(EGasAbilityInputID::Confirm),
            static_cast<int32>(EGasAbilityInputID::Cancel));
		
		ASC->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void AEntityCharacter::Landed(const FHitResult& Hit)
{
	CurrentAirJumps = 0;
}

void AEntityCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server GAS init
	// ASC->InitAbilityActorInfo(this, this);
	ASC->InitAbilityActorInfo(NewController, this);

	InitAttributes();
	GiveAbilities();
}

void AEntityCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ASC->InitAbilityActorInfo(this, this);
	InitAttributes();

	if (ASC && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "EGasAbilityInputID",
			static_cast<int32>(EGasAbilityInputID::Confirm),
			static_cast<int32>(EGasAbilityInputID::Cancel));
		
		ASC->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}


// Functions
void AEntityCharacter::MoveForBack_Implementation(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AEntityCharacter::MoveLeftRight_Implementation(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AEntityCharacter::CustomJump_Implementation()
{
	if (CMC->IsFalling() && CurrentAirJumps >= MaxAirJumps) return;
	
	FVector JumpForce = FVector(0, 0, 1);

	JumpForce = JumpForce * JumpScalar;
	LaunchCharacter(JumpForce, false, false);

	if (CMC->IsFalling()) CurrentAirJumps++;
}

// Sprint
void AEntityCharacter::ToggleSprint_Implementation()
{
	if (bIsSprinting) {
		StopSprint_Implementation();
	}
	else {
		StartSprint_Implementation();
	}
}

void AEntityCharacter::StartSprint_Implementation()
{
	if (bIsSprinting) { return; }

	StopCrouch_Implementation();
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AEntityCharacter::StopSprint_Implementation()
{
	if (!bIsSprinting) { return; }

	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

// Crouch
void AEntityCharacter::ToggleCrouch_Implementation()
{
	if (bIsCrouching) {
		StopCrouch_Implementation();
	}
	else {
		StartCrouch_Implementation();
	}
}

void AEntityCharacter::StartCrouch_Implementation()
{
	if (bIsCrouching) { return; }

	StopSprint_Implementation();
	CurrentCrouchTransitionTime = 0.f;
	bIsCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
}

void AEntityCharacter::StopCrouch_Implementation()
{
	if (!bIsCrouching) { return; }

	CurrentCrouchTransitionTime = CrouchTransitionTime;
	bIsCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

/* GAS */
class UAbilitySystemComponent* AEntityCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AEntityCharacter::InitAttributes()
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

void AEntityCharacter::GiveAbilities()
{
	// if (HasAuthority() && ASC) { }
	if (!HasAuthority() || !ASC) return;

	for(TSubclassOf<UGAS_GameplayAbility>& StartupAbility : DefaultAbilities)
	{
		ASC->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}
}
