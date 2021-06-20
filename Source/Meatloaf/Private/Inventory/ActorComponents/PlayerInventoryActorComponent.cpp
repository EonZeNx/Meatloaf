// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ActorComponents/PlayerInventoryActorComponent.h"


// Sets default values for this component's properties
UPlayerInventoryActorComponent::UPlayerInventoryActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize inventory
	Inventory = UBaseItemStackContainer::Make(50);
}


// Called when the game starts
void UPlayerInventoryActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventoryActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemStack UPlayerInventoryActorComponent::GetItemStackAtIndex(const int Index) const
{
	return Inventory->GetItemStackAtIndex(Index);
}

void UPlayerInventoryActorComponent::SetItemStackAtIndex(const int Index, const FItemStack ItemStack)
{
	return Inventory->SetItemStackAtIndex(Index, ItemStack);
}

void UPlayerInventoryActorComponent::SwapItemStacks(const int FirstIndex, const int SecondIndex)
{
	return Inventory->SwapItemStacks(FirstIndex, SecondIndex);
}

bool UPlayerInventoryActorComponent::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	return Inventory->CanInsertItemStack(ItemStack);
}

FItemStack UPlayerInventoryActorComponent::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	return Inventory->InsertItemStack(ItemStack);
}

bool UPlayerInventoryActorComponent::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
{
	return Inventory->CanRemoveItemStack(ItemStack);
}

FItemStack UPlayerInventoryActorComponent::RemoveItemStack_Implementation(const FItemStack ItemStack)
{
	return Inventory->RemoveItemStack(ItemStack);
}

TArray<FItemStack> UPlayerInventoryActorComponent::GetAllItemStacks_Implementation() const
{
	return Inventory->GetAllItemStacks();
}

TArray<FItemStack> UPlayerInventoryActorComponent::RemoveAllItemStacks_Implementation()
{
	return Inventory->RemoveAllItemStacks();
}