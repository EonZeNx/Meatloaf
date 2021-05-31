// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Item.h"

#include "ItemStack.generated.h"

/**
 * Represents an instance of an item.
 * <br> This instance may have:
 * <br> - Quantity
 * <br> - Durability
 */
USTRUCT(BlueprintType)
struct MEATLOAF_API FItemStack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	FItem Item;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	int Quantity;
};