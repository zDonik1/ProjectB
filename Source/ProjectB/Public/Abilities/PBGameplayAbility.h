// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ProjectB.h"
#include "PBGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EPBAbilityInputID AbilityInputID = EPBAbilityInputID::None;
};
