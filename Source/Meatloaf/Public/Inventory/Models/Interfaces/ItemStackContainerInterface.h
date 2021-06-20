#pragma once

#include "CoreMinimal.h"

#include "Inventory/Structs/ItemStack.h"
#include "UObject/Interface.h"
#include "ItemStackContainerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UItemStackContainerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implemented by classes which hold and manage a collection of item stacks.
 */
class MEATLOAF_API IItemStackContainerInterface
{
	GENERATED_BODY()
public:
	/**
	 * @brief Check if an item stack can be inserted into this item container without overflowing.
	 * @param ItemStack Item stack to insert
	 * @return True if stack there is enough space for items. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	bool CanInsertItemStack(const FItemStack ItemStack) const;
	
	/**
	 * @brief Insert an item stack into this item container.
	 * Any quantity of items that could not be inserted will be returned from this method as an ItemStack.
	 * @param ItemStack Item stack to insert
	 * @return Overflow item stack
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	FItemStack InsertItemStack(const FItemStack ItemStack);

	/**
	* @brief Check if an item stack can be removed from this item container in its entirety.
	* @param ItemStack Item stack to insert
	* @return True if there are enough items to remove. False otherwise.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	bool CanRemoveItemStack(const FItemStack ItemStack) const;
	
	/**
	 * @brief Remove an item stack from this item container.
	 * Returns a stack representing the items removed.
	 * If all items could not be removed, use the stack to compare what was removed.
	 * @param ItemStack Item stack to insert
	 * @return Items that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	FItemStack RemoveItemStack(const FItemStack ItemStack);
	
	/**
	 * @brief Get all item stacks part of this item container.
	 * Returns a TArray of item stacks representing the items in the inventory.
	 * @return All items
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory All Slots")
	TArray<FItemStack> GetAllItemStacks() const;

	/**
	 * @brief Remove all item stacks part of this item container
	 * @return All item stacks that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory All Slots")
	TArray<FItemStack> RemoveAllItemStacks();
};
