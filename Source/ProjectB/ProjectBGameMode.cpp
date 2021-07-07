// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBGameMode.h"
#include "ProjectBPlayerController.h"
#include "ProjectBCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectBGameMode::AProjectBGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectBPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}