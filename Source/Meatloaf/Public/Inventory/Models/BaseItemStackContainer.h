// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/ItemStackContainer.h"
#include "UObject/Object.h"
#include "BaseItemStackContainer.generated.h"

/**
 * A basic item stack container implementation that holds items in a basic list.
 * Any nullptrs in the list will be treated as empty slots.
 */
UCLASS()
class MEATLOAF_API UBaseItemStackContainer : public UObject, public IItemStackContainer
{
	GENERATED_BODY()

	// Private variables
	int MaxInventorySize;
	TArray<FItemStack*> ItemStacks;
	
public:
	// Init
	explicit UBaseItemStackContainer(int MaxInventorySize);

	// Methods
	/**
	 * @brief Get an item stack at index.
	 * Index starts at 0. If no item can be found, return null.
	 * @param Index Index of list
	 * @return ItemStack
	 */
	FItemStack* GetItemStackAtIndex(const int Index) const;

	
	/**
	 * @brief Set an item stack at index.
	 * Index starts at 0. If index is out of range, return null.
	 * @param Index Index of list
	 */
	void SetItemStackAtIndex(const int Index, const FItemStack* ItemStack);
	
	/**
	 * @brief Get the size of the item list.
	 * @return Total count of items
	 */
	int GetContainerSize() const;

	// IItemStackContainer implementation methods
	/**
	* @brief Check if an item stack can be inserted into this item container without overflowing.
	* @param ItemStack Item stack to insert
	* @return True if stack there is enough space for items. False otherwise.
	*/
	virtual bool CanInsertItemStack_Implementation(const FItemStack* ItemStack) const override;

	/**
	* @brief Insert an item stack into this item container.
	* Any quantity of items that could not be inserted will be returned from this method as an ItemStack.
	* @param ItemStack Item stack to insert
	* @return Overflow item stack
	*/
	virtual FItemStack* InsertItemStack_Implementation(const FItemStack* ItemStack) override;

	/**
	* @brief Check if an item stack can be removed from this item container in its entirety.
	* @param ItemStack Item stack to insert
	* @return True if there are enough items to remove. False otherwise.
	*/
	virtual bool CanRemoveItemStack_Implementation(const FItemStack* ItemStack) const override;

	/**
	* @brief Remove an item stack from this item container.
	* Returns a stack representing the items removed.
	* If all items could not be removed, use the stack to compare what was removed.
	* @param ItemStack Item stack to insert
	* @return Items that were removed
	*/
	virtual FItemStack* RemoveItemStack_Implementation(const FItemStack* ItemStack) override;

	/**
	* @brief Get all item stacks part of this item container.
	* Returns a TArray of item stacks representing the items in the inventory.
	* @return All items
	*/
	virtual TArray<FItemStack*> GetAllItemStacks_Implementation() const override;

	/**
	* @brief Remove all item stacks part of this item container
	* @return All item stacks that were removed
	*/
	virtual TArray<FItemStack*> RemoveAllItemStacks_Implementation() override;

private:
	
	/**
	 * @brief Update the item slot. This should perform any cleanup actions needed,
	 * i.e. making the slot into a nullptr if the quantity/durability is 0.
	 * @param Index Index of slot to update
	 */
	void UpdateItemSlot(const int Index);
};
