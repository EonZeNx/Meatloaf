// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Inventory/Structs/Item.h"
#include "Inventory/Structs/ItemStack.h"
#include "UObject/Interface.h"
#include "ItemContainer.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UItemStackContainer : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implemented by classes which hold and manage a collection of item stacks.
 */
class MEATLOAF_API IItemStackContainer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief Insert an item into this item container.
	 * Any items that could not be inserted will be returned from this method as an ItemStack.
	 * @param Item Item type to insert
	 * @param Quantity Amount of items to insert
	 * @return Overflow item stack
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	FItemStack InsertItem(FItem Item, int Quantity);

	/**
	 * @brief Remove an item from this item container.
	 * Returns a stack representing the items removed.
	 * If all items could not be removed, use the stack to compare what was removed.
	 * @param Item Item type to remove
	 * @param Quantity Amount of items to remove
	 * @return Items that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	FItemStack RemoveItem(FItem Item, int Quantity);

	/**
	 * @brief Get all items part of this item container.
	 * Returns a TArray of item stacks representing the items in the inventory.
	 * @return All items
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	TArray<FItemStack> GetAllItems();

	/**
	 * @brief Remove all items part of this item container
	 * @return All items that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	TArray<FItemStack> RemoveAllItems();
};
