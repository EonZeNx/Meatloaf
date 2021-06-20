// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Interfaces/InventoryActorComponentInterface.h"
#include "Inventory/Models/BaseItemStackContainer.h"
#include "Inventory/Models/Structs/ItemStack.h"
#include "BaseInventoryActorComponent.generated.h"

/**
 * This component handles storage of items in a defined basic list-based inventory.
 */
UCLASS(Blueprintable)
class MEATLOAF_API UBaseInventoryActorComponent : public UActorComponent, public IInventoryActorComponentInterface
{
	GENERATED_BODY()

private:
	/**
	 * @brief This will keep track of the inventory's contents.
	 */
	UPROPERTY(EditAnywhere)
	UBaseItemStackContainer* Inventory;
	
public:
	/**
	 * @brief Populate this in blueprints, it contains a definition of all valid items
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Definitions")
	UDataTable* ItemDefinitions;
	
	// Sets default values for this component's properties
	UBaseInventoryActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Inventory Single Slot")
	FItemStack GetItemStackAtIndex(const int Index) const;
	
	UFUNCTION(BlueprintCallable, Category="Inventory Single Slot")
	void SetItemStackAtIndex(const int Index, const FItemStack ItemStack);
	
	UFUNCTION(BlueprintCallable, Category="Inventory Properties")
	int GetContainerSize() const;

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	void SwapItemStacks(const int FirstIndex, const int SecondIndex);
	
	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	virtual bool CanInsertItemStack_Implementation(const FItemStack ItemStack) const override;

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	virtual FItemStack InsertItemStack_Implementation(const FItemStack ItemStack) override;

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	virtual bool CanRemoveItemStack_Implementation(const FItemStack ItemStack) const override;

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	virtual FItemStack RemoveItemStack_Implementation(const FItemStack ItemStack) override;

	UFUNCTION(BlueprintCallable, Category="Inventory All Slots")
	virtual TArray<FItemStack> GetAllItemStacks_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category="Inventory All Slots")
	virtual TArray<FItemStack> RemoveAllItemStacks_Implementation() override;
};
