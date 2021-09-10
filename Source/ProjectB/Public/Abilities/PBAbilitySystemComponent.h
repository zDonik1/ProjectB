// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "PBAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTB_API UPBAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CancelAbilityByClass(TSubclassOf<UGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable)
	void CancelAbilityByTag(FGameplayTag Tag);

	virtual void AbilityLocalInputPressed(int32 InputID) override;
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec &Spec) override;
};
