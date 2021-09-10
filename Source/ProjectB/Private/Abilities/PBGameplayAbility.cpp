// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021


#include "Abilities/PBGameplayAbility.h"

void UPBGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo)
{
    BlueprintInputPressed();
}