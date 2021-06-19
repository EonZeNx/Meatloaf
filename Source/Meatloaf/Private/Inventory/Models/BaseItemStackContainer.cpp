#include "Inventory/Models/BaseItemStackContainer.h"

UBaseItemStackContainer::UBaseItemStackContainer(int MaxInventorySize)
{
	this->MaxInventorySize = MaxInventorySize;
	this->ItemStacks.Init(nullptr, MaxInventorySize);
}

FItemStack* UBaseItemStackContainer::GetItemStackAtIndex(const int Index) const
{
	if(this->ItemStacks.IsValidIndex(Index))
	{
		return this->ItemStacks[Index];
	}
	return nullptr;
}

void UBaseItemStackContainer::SetItemStackAtIndex(const int Index, const FItemStack* ItemStack)
{
	if(this->ItemStacks.IsValidIndex(Index))
	{
		FItemStack* NewItemStack = ItemStack->MakeCopy();
		
		this->ItemStacks[Index] = NewItemStack;
	}
	// Else, do nothing.
}

int UBaseItemStackContainer::GetContainerSize() const
{
	return this->MaxInventorySize;
}

bool UBaseItemStackContainer::CanInsertItemStack_Implementation(const FItemStack* ItemStack) const
{
	// Negative/zero quantity check
	if(ItemStack->Quantity <= 0)
	{
		return true;
	}

	// Loop through and count up available space
	int FreeSpaceForItem = 0;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack* CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack == nullptr)
		{
			FreeSpaceForItem += ItemStack->Item.MaxStackQuantity;
		} else if(CurrentItemStack->Item.Id == ItemStack->Item.Id)
		{
			FreeSpaceForItem += CurrentItemStack->Item.MaxStackQuantity - CurrentItemStack->Quantity;
		}

		if(FreeSpaceForItem >= ItemStack->Quantity)
		{
			// At this point we know that there is enough room for whole stack
			return true;
		}
	}

	// Hasn't returned yet. There isn't any room for the stack.
	return false;
}

FItemStack* UBaseItemStackContainer::InsertItemStack_Implementation(const FItemStack* ItemStack)
{
	// Negative/zero quantity check
	if(ItemStack->Quantity <= 0)
	{
		return nullptr;
	}

	// Loop item stack insertion
	int QuantityToAdd = ItemStack->Quantity;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack* CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack == nullptr)
		{
			CurrentItemStack->Item = ItemStack->Item;
		} 
		if(CurrentItemStack->Item.Id == ItemStack->Item.Id)
		{
			// Try to insert into slot, scrape off the overflow and set TempItemStack quantity to overflow
			CurrentItemStack->Quantity += QuantityToAdd;
			QuantityToAdd = CurrentItemStack->Quantity - CurrentItemStack->Item.MaxStackQuantity;
			if(QuantityToAdd <= 0)
			{
				return nullptr;
			}
			CurrentItemStack->Quantity -= QuantityToAdd; // Scrape off overflow
		}
	}

	// Negative/zero quantity check
	if(QuantityToAdd <= 0)
	{
		return nullptr;
	}

	// Create stack containing overflow quantity
	FItemStack* OverflowItemStack = ItemStack->MakeCopy(); 
	OverflowItemStack->Quantity = QuantityToAdd;
	return OverflowItemStack;
}

bool UBaseItemStackContainer::CanRemoveItemStack_Implementation(const FItemStack* ItemStack) const
{
	// Negative/zero quantity check
	if(ItemStack->Quantity <= 0)
	{
		return nullptr;
	}

	// Count all items of same type
	int Quantity = 0;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack* CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack->Item.Id == ItemStack->Item.Id)
		{
			Quantity += CurrentItemStack->Quantity;
			if(Quantity >= ItemStack->Quantity)
			{
				// We know at this point that enough items of this type exist in the inventory.
				return true;
			}
		}
	}
	return false;
}

FItemStack* UBaseItemStackContainer::RemoveItemStack_Implementation(const FItemStack* ItemStack)
{
	// Negative/zero quantity check
	if(ItemStack->Quantity <= 0)
	{
		return nullptr;
	}

	// Loop item stack insertion
	int QuantityToRemove = ItemStack->Quantity;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack* CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack->Item.Id == ItemStack->Item.Id)
		{
			// Try to remove from slot
			CurrentItemStack->Quantity -= QuantityToRemove;
			QuantityToRemove = -CurrentItemStack->Quantity;
			if(QuantityToRemove <= 0)
			{
				return nullptr;
			}
			CurrentItemStack->Quantity = 0; // Normalize item stack quantity, since it is negative
		}
	}

	// Negative/zero quantity check
	if(QuantityToRemove <= 0)
	{
		return nullptr;
	}

	// Create stack containing overflow quantity
	FItemStack* OverflowItemStack = ItemStack->MakeCopy(); 
	OverflowItemStack->Quantity = QuantityToRemove;
	return OverflowItemStack;
}

TArray<FItemStack*> UBaseItemStackContainer::GetAllItemStacks_Implementation() const
{
	return ItemStacks;
}

TArray<FItemStack*> UBaseItemStackContainer::RemoveAllItemStacks_Implementation()
{
	TArray<FItemStack*> ItemStacksCopy = ItemStacks;
	for(int i = 0; i < MaxInventorySize; i++) // Set all stacks to null
	{
		ItemStacks[i] = nullptr; 
	}
	return ItemStacksCopy;
}

void UBaseItemStackContainer::UpdateItemSlot(const int Index)
{
	// If item has a quantity of zero, slot should now be nullptr.
	FItemStack* ItemStack = this->GetItemStackAtIndex(Index);
	if(ItemStack != nullptr && ItemStack->Quantity == 0)
	{
		ItemStacks[Index] = nullptr;
	}
}

