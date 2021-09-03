// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/PBHealthAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UPBHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UPBHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UPBHealthAttributeSet::OnRep_Health(const FGameplayAttributeData &OldHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UPBHealthAttributeSet, Health, OldHealth);
}