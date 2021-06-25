#pragma once

#include "LoafEntityStructs.generated.h"

USTRUCT(BlueprintType)
struct FBasicMovementStruct
{
	GENERATED_BODY()

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float Acceleration;

	UPROPERTY()
	float BrakingFrictionFactor;


	FBasicMovementStruct(float speed = 450.f, float acceleration = 2048.f, float brakingFrictionFactor = 1.f)
	{
		Speed = speed;
		Acceleration = acceleration;
		BrakingFrictionFactor = brakingFrictionFactor;
	} 
};
