// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "Delegates/DelegateCombinations.h"
#include "PBCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChange, float, AttributeValue);

UCLASS(Blueprintable)
class APBCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APBCharacter();

	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent *GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent *GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent *GetCursorToWorld() { return CursorToWorld; }

	virtual class UAbilitySystemComponent *GetAbilitySystemComponent() const override;

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

	virtual void InitializeAttributes();
	virtual void GrantAbilities();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void GrantAbility(TSubclassOf<UPBGameplayAbility> Ability);

	void GrantAbilityUnsafe(TSubclassOf<UPBGameplayAbility> Ability);

	void OnHealthUpdated(const FOnAttributeChangeData &Data);

private:
	void TryInitAbilityInputBinds();

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities");
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities");
	TArray<TSubclassOf<class UPBGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FAttributeChange OnHealthChange;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent *CursorToWorld;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	class UPBAbilitySystemComponent *AbilitySystemComponent;

	UPROPERTY()
	class UPBHealthAttributeSet *HealthAttributeSet;
};
