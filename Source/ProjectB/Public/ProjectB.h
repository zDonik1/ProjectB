// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

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