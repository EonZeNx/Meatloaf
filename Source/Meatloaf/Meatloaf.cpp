// Copyright Epic Games, Inc. All Rights Reserved.

#include "Meatloaf.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, Meatloaf, "Meatloaf" );


void DebugMsg(FString Msg, float TimeToDisplay, FColor Colour)
{
	GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, Colour, Msg);
}
