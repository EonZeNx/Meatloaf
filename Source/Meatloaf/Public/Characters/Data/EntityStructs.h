#pragma once

#include "EntityStructs.generated.h"

USTRUCT(BlueprintType)
struct FBasicMovement
{
	GENERATED_BODY()

	UPROPERTY()
	float Speed;

	UPROPERTY()
	float Acceleration;

	UPROPERTY()
	float BrakingFrictionFactor;


	explicit FBasicMovement(float speed = 450.f, float acceleration = 2048.f, float brakingFrictionFactor = 1.f)
	{
		Speed = speed;
		Acceleration = acceleration;
		BrakingFrictionFactor = brakingFrictionFactor;
	} 
};
