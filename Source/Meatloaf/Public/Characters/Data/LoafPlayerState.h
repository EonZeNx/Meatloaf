// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GAS/LoafAbilitySystemComponent.h"
#include "GAS/LoafAttributeSet.h"

#include "LoafPlayerState.generated.h"


UCLASS()
class MEATLOAF_API ALoafPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

/** VARIABLES **/
protected:
	UPROPERTY()
	class ULoafAbilitySystemComponent* ASC;

	UPROPERTY()
	class ULoafAttributeSet* DefaultAttributes;  // AttributeSetBase

	FGameplayTag DeadTag;

	
	/** ATTRIBUTES **/
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes")
    int32 GetCharacterLevel() const;

	
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Health")
    float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Health")
    float GetMaxHealth() const;

	
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Jump Power")
    float GetJumpPower() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Jump Power")
    float GetMaxJumpPower() const;

	
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Jumps")
    int GetCurrentJumps() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Jumps")
    int GetMaxJumps() const;

	
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Movement")
    float GetMoveAccel() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Movement")
    float MaxMoveSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Movement")
    float GetSprintAccel() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes|Movement")
    float GetMaxSprintMoveSpeed() const;

	
/** FUNCTIONS **/
public:
	ALoafPlayerState();

	// Implement IAbilitySystemInterface
	virtual class ULoafAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class ULoafAttributeSet* GetDefaultAttributes() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState")
    bool IsAlive() const;
};
