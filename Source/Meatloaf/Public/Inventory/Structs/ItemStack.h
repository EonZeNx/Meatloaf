// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Item.h"

#include "ItemStack.generated.h"

/**
 * 
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