#pragma once

#include "EntityStates.generated.h"

UENUM(BlueprintType)
enum class EEntityStance : uint8 {
	Stance_Normal		UMETA(DisplayName="Normal"),
	Stance_Sneak		UMETA(DisplayName="Sneak"),
	Stance_Ragdoll		UMETA(DisplayName="Ragdoll")
};

UENUM(BlueprintType)
enum class EEntityGait : uint8 {
	Gait_Normal		UMETA(DisplayName="Normal"),
    Gait_Fast		UMETA(DisplayName="Fast"),
	Gait_Slow		UMETA(DisplayName="Slow"),
};
