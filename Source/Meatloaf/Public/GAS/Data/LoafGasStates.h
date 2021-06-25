#pragma once

#include "LoafGasStates.generated.h"

UENUM(BlueprintType)
enum class ELoafAbilityInputID : uint8 {
	None		UMETA(DisplayName="None"),
	Confirm		UMETA(DisplayName="Confirm"),
	Cancel		UMETA(DisplayName="Cancel"),
	Jump		UMETA(DisplayName="Jump"),
};
