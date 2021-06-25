// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BasicMovement.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/GAS_AbilitySystemComponent.h"
#include "GAS/GAS_AttributeSet.h"

#include "EntityCharacter.generated.h"

UCLASS()
class MEATLOAF_API AEntityCharacter : public ACharacter, public IBasicMovement, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()

	/** VARIABLES **/
public:
	/* GAS */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	class UGAS_AbilitySystemComponent* ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	class UGAS_AttributeSet* Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TArray<TSubclassOf<class UGAS_GameplayAbility>> DefaultAbilities;
protected:
	/** References. **/
	/* A reference to the owners' movement component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defaults")
	UCharacterMovementComponent* CMC;

	
	/** Movement. **/
	/* Default sprint speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	float SprintSpeed;

	/* Default run speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	float RunSpeed;

	/* Default crouch speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	float CrouchSpeed;

	/* Whether or not the character is sprinting */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	bool bIsSprinting;

	/* Whether or not the character is crouching */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	bool bIsCrouching;

	
	/** Stance config. **/
	float StandingCapsuleHalfHeight;
	float StandingCapsuleRadius;
	float CrouchingCapsuleHalfHeight;
	float CrouchingCapsuleRadius;

	/* Stance timings. */
	float CrouchTransitionTime;
	float CurrentCrouchTransitionTime;

	
	/** Jump config. **/
	/* Maximum in-air jumps. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Config")
	int MaxAirJumps;
	
	/* Current in-air jumps. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Config")
	int CurrentAirJumps;
	
	/* Default air jump force. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Config")
	float JumpScalar;
	
private:
	
	/** FUNCTIONS **/
public:
	// Sets default values for this character's properties
	AEntityCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Required to use the Ability System Component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	virtual void BeginPlay() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	// Basic Movement implementations
	UFUNCTION(BlueprintCallable)
    virtual void MoveForBack_Implementation(float value) override;
	UFUNCTION(BlueprintCallable)
    virtual void MoveLeftRight_Implementation(float value) override;
	
	UFUNCTION(BlueprintCallable)
    virtual void CustomJump_Implementation() override;
	
	// Sprint
	UFUNCTION(BlueprintCallable)
    virtual void ToggleSprint_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StartSprint_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StopSprint_Implementation() override;
	
	// Crouch
	UFUNCTION(BlueprintCallable)
    virtual void ToggleCrouch_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StartCrouch_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StopCrouch_Implementation() override;
	
private:
	/* Ability System Component */
	virtual void InitAttributes();
	virtual void GiveAbilities();
};
