// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LoafCharacter.h"

#include "GAS/LoafAbilitySystemComponent.h"
#include "GAS/LoafGameplayAbility.h"
#include "GAS/LoafAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Characters/Data/LoafPlayerState.h"
#include "Controllers/LoafPlayerController.h"
#include "GAS/Effects/GEReturnJumps.h"
#include "GAS/Effects/GEUseJump.h"


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

	/** GAS **/
	ASC = CreateDefaultSubobject<ULoafAbilitySystemComponent>("ASC");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	DefaultAttributes = CreateDefaultSubobject<ULoafAttributeSet>("DefaultAttributes");
}


/** OVERRIDES **/
void ALoafCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALoafCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ALoafPlayerController* CastController = Cast<ALoafPlayerController>(NewController);
	if (CastController) LoafController = CastController;

	// Server GAS init
	if (ALoafPlayerState* PS = GetPlayerState<ALoafPlayerState>())
	{
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		ASC = Cast<ULoafAbilitySystemComponent>(PS->GetAbilitySystemComponent());

		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in init twice for heroes that have PlayerControllers.
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		// Set the DefaultAttributes for convenience attribute functions
		DefaultAttributes = PS->GetDefaultAttributes();

		// If we handle players disconnecting and rejoining in the future, we'll have to change this so that possession from rejoining doesn't reset attributes.
		// For now assume possession = spawn/respawn.
		InitAttributes();
		// AddStartupEffects();
		AddCharacterAbilities();
	}
}

void ALoafCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ASC->InitAbilityActorInfo(this, this);
	InitAttributes();

	if (ASC.IsValid() && InputComponent)
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

	/** AXES **/
	PlayerInputComponent->BindAxis("LookYaw", this, &ALoafCharacter::LookYaw);
	PlayerInputComponent->BindAxis("LookPitch", this, &ALoafCharacter::LookPitch);

	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &ALoafCharacter::MoveForBack_Implementation);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &ALoafCharacter::MoveLeftRight_Implementation);

	// May get called in an init state where one is not setup yet.
	if (ASC.IsValid() && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel", "ELoafAbilityInputID",
            static_cast<int32>(ELoafAbilityInputID::Confirm),
            static_cast<int32>(ELoafAbilityInputID::Cancel));
		
		ASC->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

void ALoafCharacter::Landed(const FHitResult& Hit)
{
	UGEReturnJumps* ReturnJumps = NewObject<UGEReturnJumps>();
	ASC->ApplyGameplayEffectToSelf(ReturnJumps, 1.0f, ASC->MakeEffectContext());
}

void ALoafCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


/** FUNCTIONS **/
/** CAMERA **/
void ALoafCharacter::LookYaw(float Value)
{
	if (!IsAlive()) return;
	
	if (Value != 0.0f)
	{
		LoafController->LookYaw(Value);
	}
}

void ALoafCharacter::LookPitch(float Value)
{
	if (!IsAlive()) return;
	
	if (Value != 0.0f)
	{
		LoafController->LookPitch(Value);
	}
}


/** CMC **/
bool ALoafCharacter::IsFalling() const
{
	return CMC->IsFalling();
}


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
	if (CMC->IsFalling() && GetCurrentJumps() >= GetMaxJumps()) return;
	
	FVector JumpForce = FVector(0, 0, 1);

	JumpForce = JumpForce * GetJumpPower();
	LaunchCharacter(JumpForce, false, true);

	if (CMC->IsFalling())
	{
		UGEUseJump* UseJump = NewObject<UGEUseJump>();
		ASC->ApplyGameplayEffectToSelf(UseJump, 1.0f, ASC->MakeEffectContext());
	}
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
	return ASC.Get();
}

int32 ALoafCharacter::GetAbilityLevel(ELoafAbilityInputID AbilityID) const
{
	return 1;
}


void ALoafCharacter::InitAttributes()
{
	if (!ASC.IsValid()) return;

	if (!DefaultAttributeEffect)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle NewHandle = ASC->MakeOutgoingSpec(DefaultAttributeEffect, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = ASC->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), ASC.Get());
	}
}

void ALoafCharacter::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !ASC.IsValid() || ASC->CharacterAbilitiesGiven) return;

	for (TSubclassOf<ULoafGameplayAbility>& StartupAbility : DefaultAbilities)
	{
		ASC->GiveAbility(
            FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	ASC->CharacterAbilitiesGiven = true;
}


bool ALoafCharacter::IsAlive()
{
	return GetHealth() > 0.0f;
}

/* Getters */
int32 ALoafCharacter::GetCharacterLevel() const
{
	if (!DefaultAttributes.IsValid()) { return 0; }

	return static_cast<int32>(DefaultAttributes->GetCharacterLevel());
}

float ALoafCharacter::GetHealth() const
{
	if (!DefaultAttributes.IsValid()) { return 0.0f; }

	return DefaultAttributes->GetHealth();
}

float ALoafCharacter::GetMaxHealth() const
{
	if (!DefaultAttributes.IsValid()) { return 0.0f; }
	
	return DefaultAttributes->GetMaxHealth();
}

float ALoafCharacter::GetJumpPower() const
{
	if (!DefaultAttributes.IsValid()) { return 0.0f; }
	
	return DefaultAttributes->GetJumpPower();
}

float ALoafCharacter::GetMaxJumpPower() const
{
	if (!DefaultAttributes.IsValid()) { return 0.0f; }
	
	return DefaultAttributes->GetMaxJumpPower();
}

int ALoafCharacter::GetCurrentJumps() const
{
	if (!DefaultAttributes.IsValid()) { return 0; }
	
	return static_cast<int>(DefaultAttributes->GetCurrentJumps());
}

int ALoafCharacter::GetMaxJumps() const
{
	if (!DefaultAttributes.IsValid()) { return 0; }
	
	return static_cast<int>(DefaultAttributes->GetMaxJumps());
}
