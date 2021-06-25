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
	class ULoafAttributeSet* AttributeSetBase;

	FGameplayTag DeadTag;

	/** ATTRIBUTES **/
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes")
    float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|Attributes")
    float GetJumpPower() const;
	
/** FUNCTIONS **/
public:
	ALoafPlayerState();

	// Implement IAbilitySystemInterface
	virtual class ULoafAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class ULoafAttributeSet* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState")
    bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|LoafPlayerState|UI")
    void ShowAbilityConfirmCancelText(bool ShowText);
};
