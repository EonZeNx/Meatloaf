// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/ItemStackContainer.h"
#include "UObject/Object.h"
#include "BaseItemStackContainer.generated.h"

/**
 * A basic item stack container implementation that holds items in a basic list.
 */
UCLASS()
class MEATLOAF_API UBaseItemStackContainer : public UObject, public IItemStackContainer
{
	GENERATED_BODY()

private:
	// Private variables
	int MaxInventorySize;
	TArray<FItemStack*> ItemStacks;
	
public:
	// Init
	UBaseItemStackContainer(int MaxInventorySize);

	// Methods
	/**
	 * @brief Get an item at an index.
	 * Index starts at 0. If no item can be found, return null.
	 * @param Index Index of list
	 * @return ItemStack
	 */
	FItemStack* GetItemAtIndex(int Index) const;

	/**
	 * @brief Get the size of the item list.
	 * @return Total count of items
	 */
	int GetItemCount() const;

	// IItemStackContainer implementation methods
	/**
	* @brief Insert an item into this item container.
	* Any items that could not be inserted will be returned from this method as an ItemStack.
	* @param Item Item type to insert
	* @param Quantity Amount of items to insert
	* @return Overflow item stack
	*/
	virtual FItemStack* InsertItem_Implementation(FItem* Item, int Quantity) override;

	/**
	* @brief Remove an item from this item container.
	* Returns a stack representing the items removed.
	* If all items could not be removed, use the stack to compare what was removed.
	* @param Item Item type to remove
	* @param Quantity Amount of items to remove
	* @return Items that were removed
	*/
	virtual FItemStack* RemoveItem_Implementation(FItem* Item, int Quantity) override;

	/**
	* @brief Get all items part of this item container.
	* Returns a TArray of item stacks representing the items in the inventory.
	* @return All items
	*/
	virtual TArray<FItemStack*> GetAllItems_Implementation() const override;

	/**
	* @brief Remove all items part of this item container
	* @return All items that were removed
	*/
	virtual TArray<FItemStack*> RemoveAllItems_Implementation() override;
};
