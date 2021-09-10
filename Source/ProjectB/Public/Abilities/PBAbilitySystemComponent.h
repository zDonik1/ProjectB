// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "PBAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTagChanged, FGameplayTag, Tag, bool, Exists);

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

	UFUNCTION(BlueprintCallable)
	void AddTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void RemoveTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	bool HasActiveAbilityWithTag(FGameplayTag Tag);

	// Returns the primary instance (on Actor Instanced Abilities only)
	UFUNCTION(BlueprintCallable)
	UGameplayAbility *GetAbilityPrimaryInstanceByClass(TSubclassOf<UGameplayAbility> Ability);

	virtual void AbilityLocalInputPressed(int32 InputID) override;
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec &Spec) override;

	virtual void OnTagUpdated(const FGameplayTag &Tag, bool TagExists) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FTagChanged OnTagChanged;
};
