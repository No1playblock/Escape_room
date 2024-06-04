// Copyright Epic Games, Inc. All Rights Reserved.

#include "Escape_RoomGameMode.h"
#include "Escape_RoomCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEscape_RoomGameMode::AEscape_RoomGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
