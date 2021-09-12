// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "PBAbilityTask_WaitOverlapHit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitCollisionDelegate, const FGameplayAbilityTargetDataHandle &, TargetData);

class AActor;
class UPrimitiveComponent;

/**
 *	Async Task that continuously returns TargetData when a Hit or Overlap collision occurs until stopped using EndTask()
 */
UCLASS()
class PROJECTB_API UPBAbilityTask_WaitOverlapHit : public UAbilityTask
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable)
	FWaitCollisionDelegate OnOverlap;

	UPROPERTY(BlueprintAssignable);
	FWaitCollisionDelegate OnHit;

	UFUNCTION()
	void OnOverlapBeginCallback(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	virtual void Activate() override;

	/** Continuously get overlap or hit events with other actor's root primitive component. Stop with EndTask() */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UPBAbilityTask_WaitOverlapHit *WaitForOverlapHit(UGameplayAbility *OwningAbility);

private:
	virtual void OnDestroy(bool AbilityEnded) override;

	UPrimitiveComponent *GetComponent();

	void BroadcastHit(FWaitCollisionDelegate &Delegate, AActor *OtherActor, const FHitResult &Hit);
};
