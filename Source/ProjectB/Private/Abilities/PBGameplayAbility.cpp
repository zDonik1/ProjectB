// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021


#include "Abilities/PBGameplayAbility.h"

void UPBGameplayAbility::InitInstance()
{
    BlueprintInitInstance();
}

void UPBGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo)
{
    BlueprintInputPressed();
}

void UPBGameplayAbility::AddTag(FGameplayTag Tag)
{
    AbilityTags.AddTag(Tag);
}

void UPBGameplayAbility::RemoveTag(FGameplayTag Tag)
{
    AbilityTags.RemoveTag(Tag);
}