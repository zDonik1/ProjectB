// Copyright Epic Games, Inc. All Rights Reserved.

#include "PBGameMode.h"
#include "PBPlayerController.h"
#include "PBCharacter.h"
#include "UObject/ConstructorHelpers.h"

APBGameMode::APBGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APBPlayerController::StaticClass();
}