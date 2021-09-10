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
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo,
							  const FGameplayAbilityActivationInfo ActivationInfo) override;

	// Initializes the primary instance (if Actor Instanced), called when ability is granted
	void InitInstance();

	// Works only if actor instanced
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InitInstance"))
	void BlueprintInitInstance();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "InputPressed"))
	void BlueprintInputPressed();

	UFUNCTION(BlueprintCallable)
	void AddTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void RemoveTag(FGameplayTag Tag);

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability")
	EPBAbilityInputID AbilityInputID = EPBAbilityInputID::None;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability")
	bool bActivateOnInputPressed = true;
};
