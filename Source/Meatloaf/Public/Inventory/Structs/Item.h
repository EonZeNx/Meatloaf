// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MEATLOAF_API FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	FString Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	FString Name;
};
