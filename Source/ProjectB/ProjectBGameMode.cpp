// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectBGameMode.h"
#include "ProjectBPlayerController.h"
#include "ProjectBCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectBGameMode::AProjectBGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectBPlayerController::StaticClass();
}