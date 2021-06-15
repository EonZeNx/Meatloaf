// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BasicMovement.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EntityCharacter.generated.h"

UCLASS()
class MEATLOAF_API AEntityCharacter : public ACharacter, public IBasicMovement
{
	GENERATED_BODY()

	/** VARIABLES **/
public:
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
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
};
