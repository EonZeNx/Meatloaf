// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"

#include "InventoryActorComponent.generated.h"

/**
 * This component handles storage of items in a defined inventory.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MEATLOAF_API UInventoryActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Populate this in blueprints, it contains a definition of all valid items
	 */
	UPROPERTY(EditAnywhere)
	UDataTable* ItemDefinitions;
	
	// Sets default values for this component's properties
	UInventoryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
