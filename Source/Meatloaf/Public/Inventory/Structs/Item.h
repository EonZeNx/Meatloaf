// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "Item.generated.h"

/**
 * Represents an item definition. i.e. Sword, Wood, Stone etc.
 */
USTRUCT(BlueprintType)
struct MEATLOAF_API FItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	FString Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	FString Name;
};
