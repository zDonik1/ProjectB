// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogProjectB, Log, All);

UENUM(BlueprintType)
enum class EPBAbilityInputID : uint8
{
    None,
    Cancel,
    Confirm,
    BasicAttack,
    Dash,
};