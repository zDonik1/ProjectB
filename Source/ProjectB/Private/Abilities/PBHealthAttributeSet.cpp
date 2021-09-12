// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

#include "Abilities/PBHealthAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UPBHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UPBHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UPBHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UPBHealthAttributeSet::OnRep_Health(const FGameplayAttributeData &OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHealthAttributeSet, Health, OldHealth);
}

void UPBHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHealthAttributeSet, MaxHealth, OldMaxHealth);
}