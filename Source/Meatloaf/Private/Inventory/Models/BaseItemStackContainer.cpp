// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Models/BaseItemStackContainer.h"

UBaseItemStackContainer::UBaseItemStackContainer(int MaxInventorySize)
{
	this->MaxInventorySize = MaxInventorySize;
	this->ItemStacks.Init(nullptr, MaxInventorySize);
}

FItemStack* UBaseItemStackContainer::GetItemAtIndex(const int Index) const
{
	if(this->ItemStacks.IsValidIndex(Index))
	{
		return this->ItemStacks[Index];
	}
	return nullptr;
}

int UBaseItemStackContainer::GetItemCount() const
{
	return this->MaxInventorySize;
}

FItemStack* UBaseItemStackContainer::InsertItem_Implementation(FItem* Item, int Quantity)
{
	return {};
}

FItemStack* UBaseItemStackContainer::RemoveItem_Implementation(FItem* Item, int Quantity)
{
	return {};
}

TArray<FItemStack*> UBaseItemStackContainer::GetAllItems_Implementation() const
{
	return {};
}

TArray<FItemStack*> UBaseItemStackContainer::RemoveAllItems_Implementation()
{
	return {};
}

