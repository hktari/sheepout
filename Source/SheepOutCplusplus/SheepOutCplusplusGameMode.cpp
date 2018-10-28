// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SheepOutCplusplusGameMode.h"
#include "SheepOutCplusplusPlayerController.h"
#include "SheepOutCplusplusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASheepOutCplusplusGameMode::ASheepOutCplusplusGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASheepOutCplusplusPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}