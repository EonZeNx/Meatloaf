// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BasicMovement.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/LoafAbilitySystemComponent.h"
#include "GAS/LoafAttributeSet.h"

#include "LoafCharacter.generated.h"

UCLASS()
class MEATLOAF_API ALoafCharacter : public ACharacter, public IBasicMovement, public IAbilitySystemInterface
{
	GENERATED_BODY()

/** VARIABLES **/
public:
	/** GAS **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	class ULoafAbilitySystemComponent* ASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="GAS")
	class ULoafAttributeSet* Attributes;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TArray<TSubclassOf<class ULoafGameplayAbility>> DefaultAbilities;

	
protected:
	/** REFERENCES **/
	/* A reference to the owners' movement component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defaults")
	UCharacterMovementComponent* CMC;

	
	/** MOVEMENT **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	float CrouchSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Config")
	bool bIsCrouching;

	
	/** STANCE **/
	float StandingCapsuleHalfHeight;
	float StandingCapsuleRadius;
	float CrouchingCapsuleHalfHeight;
	float CrouchingCapsuleRadius;

	/* Stance timings */
	float CrouchTransitionTime;
	float CurrentCrouchTransitionTime;

	
	/** JUMP **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Config")
	int MaxAirJumps;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Config")
	int CurrentAirJumps;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump Config")
	float JumpScalar;
	
private:

	
/** FUNCTIONS **/
public:
	ALoafCharacter();

	/** GAS **/
	// Required to use the Ability System Component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	
protected:
	/** OVERRIDES **/
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Tick(float DeltaTime) override;

	
	/** MOVEMENT **/
	UFUNCTION(BlueprintCallable)
    virtual void MoveForBack_Implementation(float value) override;
	UFUNCTION(BlueprintCallable)
    virtual void MoveLeftRight_Implementation(float value) override;

	
	/** ACTIONS **/
	UFUNCTION(BlueprintCallable)
    virtual void CustomJump_Implementation() override;
	
	/* Sprint */
	UFUNCTION(BlueprintCallable)
    virtual void ToggleSprint_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StartSprint_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StopSprint_Implementation() override;
	
	/* Crouch */
	UFUNCTION(BlueprintCallable)
    virtual void ToggleCrouch_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StartCrouch_Implementation() override;
	UFUNCTION(BlueprintCallable)
    virtual void StopCrouch_Implementation() override;

	
private:
	/** GAS **/
	virtual void InitAttributes();
	virtual void GiveAbilities();
};
