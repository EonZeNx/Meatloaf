// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"  // This seems to smooth out the macros
#include "LoafAttributeSet.generated.h"


// Macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MEATLOAF_API ULoafAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	ULoafAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** ATTRIBUTES **/
	/* Character Level */
	UPROPERTY(BlueprintReadOnly, Category = "Attributes|Character Level", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, CharacterLevel)
	
	/* Health */
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, Health);

	/* Max Health */
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, MaxHealth);

	/* Jump power */
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Jump Power", ReplicatedUsing = OnRep_JumpPower)
	FGameplayAttributeData JumpPower;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, JumpPower);

	/* Max Jump Power */
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Jump Power", ReplicatedUsing = OnRep_MaxJumpPower)
	FGameplayAttributeData MaxJumpPower;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, MaxJumpPower);

	/* Current Jumps */
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Jumps", ReplicatedUsing = OnRep_CurrentJumps)
	FGameplayAttributeData CurrentJumps;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, CurrentJumps);

	/* Max Jumps */
	UPROPERTY(BlueprintReadOnly, Category="Attributes|Jumps", ReplicatedUsing = OnRep_MaxJumps)
	FGameplayAttributeData MaxJumps;
	ATTRIBUTE_ACCESSORS(ULoafAttributeSet, MaxJumps);


	/** ATTRIBUTE REPS **/
	/* Character Level */
	UFUNCTION()
	virtual void OnRep_CharacterLevel(const FGameplayAttributeData& OldCharacterLevel);
	
	/* Health */
	UFUNCTION()
    virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	/* Max Health */
	UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth);
	
	/* Jump power */
	UFUNCTION()
    virtual void OnRep_JumpPower(const FGameplayAttributeData& OldJumpPower);
	
	/* Max Jump Power */
	UFUNCTION()
    virtual void OnRep_MaxJumpPower(const FGameplayAttributeData& OldHealth);

	/* Current Jumps */
	UFUNCTION()
    virtual void OnRep_CurrentJumps(const FGameplayAttributeData& OldCurrentJumps);
	
	/* Max Jumps */
	UFUNCTION()
    virtual void OnRep_MaxJumps(const FGameplayAttributeData& OldMaxJumps);
};
