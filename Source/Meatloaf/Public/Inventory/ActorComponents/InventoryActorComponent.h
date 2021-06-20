// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Interfaces/InventoryInterface.h"
#include "Inventory/Models/BaseItemStackContainer.h"

#include "InventoryActorComponent.generated.h"

/**
 * This component handles storage of items in a defined inventory.
 * TODO: Make this implement an interface.
 */
UCLASS(Blueprintable)
class MEATLOAF_API UInventoryActorComponent : public UActorComponent, public IInventoryInterface
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
	UInventoryActorComponent();

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
	bool CanInsertItemStack(const FItemStack ItemStack) const;

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	FItemStack InsertItemStack(const FItemStack ItemStack);

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	bool CanRemoveItemStack(const FItemStack ItemStack) const;

	UFUNCTION(BlueprintCallable, Category="Inventory Actions")
	FItemStack RemoveItemStack(const FItemStack ItemStack);

	UFUNCTION(BlueprintCallable, Category="Inventory All Slots")
	TArray<FItemStack> GetAllItemStacks() const;

	UFUNCTION(BlueprintCallable, Category="Inventory All Slots")
	TArray<FItemStack> RemoveAllItemStacks();
};
