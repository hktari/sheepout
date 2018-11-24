// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SheepOutCplusplusGameMode.h"
#include "SheepOutCplusplusPlayerController.h"
#include "SheepOutCplusplusCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SheepOutCplusplus.h"

ASheepOutCplusplusGameMode::ASheepOutCplusplusGameMode()
{
	// use our custom PlayerController class
	static ConstructorHelpers::FClassFinder<AController> PlayerControllerBPClass(TEXT("/Game/TopDownCPP/Blueprints/PlayerController_BP"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	else 
	{
		UE_LOG(LogSheepError, Warning, TEXT("Player controller BP not found !"));
	}
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}