#pragma once

#include "GAS_States.generated.h"

UENUM(BlueprintType)
enum class EGasAbilityInputID : uint8 {
	None		UMETA(DisplayName="None"),
	Confirm		UMETA(DisplayName="Confirm"),
	Cancel		UMETA(DisplayName="Cancel"),
	Jump		UMETA(DisplayName="Jump"),
};
