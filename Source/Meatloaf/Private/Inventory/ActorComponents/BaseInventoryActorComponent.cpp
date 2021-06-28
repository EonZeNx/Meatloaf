// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/ActorComponents/BaseInventoryActorComponent.h"
#include "Inventory/Models/BaseItemStackContainer.h"


// Sets default values for this component's properties
UBaseInventoryActorComponent::UBaseInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize inventory
	Inventory = UBaseItemStackContainer::Make(40);
}

// Called when the game starts
void UBaseInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBaseInventoryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemStack UBaseInventoryActorComponent::GetItemStackAtIndex(const int Index) const
{
	return Inventory->GetItemStackAtIndex(Index);
}

void UBaseInventoryActorComponent::SetItemStackAtIndex(const int Index, const FItemStack ItemStack)
{
	return Inventory->SetItemStackAtIndex(Index, ItemStack);
}

int UBaseInventoryActorComponent::GetContainerSize() const
{
	return Inventory->GetContainerSize();
}

void UBaseInventoryActorComponent::SwapItemStacks(const int FirstIndex, const int SecondIndex)
{
	return Inventory->SwapItemStacks(FirstIndex, SecondIndex);
}

bool UBaseInventoryActorComponent::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	return Inventory->CanInsertItemStack(ItemStack);
}

FItemStack UBaseInventoryActorComponent::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	return Inventory->InsertItemStack(ItemStack);
}

bool UBaseInventoryActorComponent::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
{
	return Inventory->CanRemoveItemStack(ItemStack);
}

FItemStack UBaseInventoryActorComponent::RemoveItemStack_Implementation(const FItemStack ItemStack)
{
	return Inventory->RemoveItemStack(ItemStack);
}

TArray<FItemStack> UBaseInventoryActorComponent::GetAllItemStacks_Implementation() const
{
	return Inventory->GetAllItemStacks();
}

TArray<FItemStack> UBaseInventoryActorComponent::RemoveAllItemStacks_Implementation()
{
	return Inventory->RemoveAllItemStacks();
}

