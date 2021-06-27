// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BasicMovement.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Controllers/LoafPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/LoafAbilitySystemComponent.h"
#include "GAS/LoafAttributeSet.h"
#include "GAS/Data/LoafGasStates.h"


#include "LoafCharacter.generated.h"

UCLASS()
class MEATLOAF_API ALoafCharacter : public ACharacter, public IBasicMovement, public IAbilitySystemInterface
{
	GENERATED_BODY()

/** VARIABLES **/
public:
	/** GAS **/
	TWeakObjectPtr<class ULoafAbilitySystemComponent> ASC;  // AbilitySystemComponent
	TWeakObjectPtr<class ULoafAttributeSet> DefaultAttributes;  // DefaultAttributes

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS")
	TArray<TSubclassOf<class ULoafGameplayAbility>> DefaultAbilities;

	
protected:
	/** REFERENCES **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defaults")
	UCharacterMovementComponent* CMC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defaults")
	ALoafPlayerController* LoafController;

	
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
	
private:

	
/** FUNCTIONS **/
public:
	ALoafCharacter();

	
	/** CAMERA **/
	UFUNCTION(BlueprintCallable)
    virtual void LookYaw(float Value);
	
	UFUNCTION(BlueprintCallable)
    virtual void LookPitch(float Value);


	/** CMC **/
	UFUNCTION(BlueprintCallable)
    virtual bool IsFalling() const;

	
	/** GAS **/
	// Required to use the Ability System Component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
    virtual void CustomJump_Implementation() override;

	// Switch on AbilityID to return individual ability levels. Hardcoded to 1 for every ability in this project.
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter")
    virtual int32 GetAbilityLevel(ELoafAbilityInputID AbilityID) const;

	/* Getters */
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes")
    int32 GetCharacterLevel() const;
	
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes|Health")
    float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes|Health")
    float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes|Jump Power")
    float GetJumpPower() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes|Jump Power")
    float GetMaxJumpPower() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes|Jumps")
    int GetCurrentJumps() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafCharacter|Attributes|Jumps")
    int GetMaxJumps() const;
	
	
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
	virtual void AddCharacterAbilities();
	virtual bool IsAlive();
};
