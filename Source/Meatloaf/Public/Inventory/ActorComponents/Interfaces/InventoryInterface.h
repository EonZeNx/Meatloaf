// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Inventory/Structs/ItemStack.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEATLOAF_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * @brief Check if an item stack can be inserted into this inventory without overflowing.
	 * @param ItemStack Item stack to insert
	 * @return True if stack there is enough space for items. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Checks")
	bool CanInsertItemStack(const FItemStack ItemStack) const;
	
	/**
	 * @brief Insert an item stack into this inventory.
	 * Any quantity of items that could not be inserted will be returned from this method as an ItemStack.
	 * @param ItemStack Item stack to insert
	 * @return Overflow item stack
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	FItemStack InsertItemStack(const FItemStack ItemStack);

	/**
	* @brief Check if an item stack can be removed from this inventory in its entirety.
	* @param ItemStack Item stack to insert
	* @return True if there are enough items to remove. False otherwise.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Checks")
	bool CanRemoveItemStack(const FItemStack ItemStack) const;
	
	/**
	 * @brief Remove an item stack from this inventory.
	 * Returns a stack representing the items removed.
	 * If all items could not be removed, use the stack to compare what was removed.
	 * @param ItemStack Item stack to insert
	 * @return Items that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	FItemStack RemoveItemStack(const FItemStack ItemStack);
	
	/**
	 * @brief Get all item stacks part of this inventory.
	 * Returns a TArray of item stacks representing the items in the inventory.
	 * @return All items
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory All Slots")
	TArray<FItemStack> GetAllItemStacks() const;

	/**
	 * @brief Remove all item stacks part of this inventory
	 * @return All item stacks that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory All Slots")
	TArray<FItemStack> RemoveAllItemStacks();
};
