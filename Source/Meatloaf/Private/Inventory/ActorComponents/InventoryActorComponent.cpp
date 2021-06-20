// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/ActorComponents/InventoryActorComponent.h"


// Sets default values for this component's properties
UInventoryActorComponent::UInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize inventory
	Inventory = UBaseItemStackContainer::Make(40);
}

// Called when the game starts
void UInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UInventoryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemStack UInventoryActorComponent::GetItemStackAtIndex(const int Index) const
{
	return Inventory->GetItemStackAtIndex(Index);
}

void UInventoryActorComponent::SetItemStackAtIndex(const int Index, const FItemStack ItemStack)
{
	return Inventory->SetItemStackAtIndex(Index, ItemStack);
}

int UInventoryActorComponent::GetContainerSize() const
{
	return Inventory->GetContainerSize();
}

void UInventoryActorComponent::SwapItemStacks(const int FirstIndex, const int SecondIndex)
{
	return Inventory->SwapItemStacks(FirstIndex, SecondIndex);
}

bool UInventoryActorComponent::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	return Inventory->CanInsertItemStack(ItemStack);
}

FItemStack UInventoryActorComponent::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	return Inventory->InsertItemStack(ItemStack);
}

bool UInventoryActorComponent::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
{
	return Inventory->CanRemoveItemStack(ItemStack);
}

FItemStack UInventoryActorComponent::RemoveItemStack_Implementation(const FItemStack ItemStack)
{
	return Inventory->RemoveItemStack(ItemStack);
}

TArray<FItemStack> UInventoryActorComponent::GetAllItemStacks_Implementation() const
{
	return Inventory->GetAllItemStacks();
}

TArray<FItemStack> UInventoryActorComponent::RemoveAllItemStacks_Implementation()
{
	return Inventory->RemoveAllItemStacks();
}

