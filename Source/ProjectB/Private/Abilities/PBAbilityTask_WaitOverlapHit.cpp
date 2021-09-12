// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

#include "Abilities/PBAbilityTask_WaitOverlapHit.h"

UPBAbilityTask_WaitOverlapHit::UPBAbilityTask_WaitOverlapHit(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UPBAbilityTask_WaitOverlapHit::OnOverlapBeginCallback(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    BroadcastHit(OnOverlap, OtherActor, SweepResult);
}

void UPBAbilityTask_WaitOverlapHit::OnHitCallback(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    BroadcastHit(OnHit, OtherActor, Hit);
}

/**
*	Need:
*	-Easy way to specify which primitive components should be used for this overlap test
*	-Easy way to specify which types of actors/collision overlaps that we care about/want to block on
*/

UPBAbilityTask_WaitOverlapHit *UPBAbilityTask_WaitOverlapHit::WaitForOverlapHit(UGameplayAbility *OwningAbility)
{
    UPBAbilityTask_WaitOverlapHit *MyObj = NewAbilityTask<UPBAbilityTask_WaitOverlapHit>(OwningAbility);
    return MyObj;
}

void UPBAbilityTask_WaitOverlapHit::Activate()
{
    SetWaitingOnAvatar();

    UPrimitiveComponent *PrimComponent = GetComponent();
    if (PrimComponent)
    {
        PrimComponent->OnComponentBeginOverlap.AddDynamic(this, &UPBAbilityTask_WaitOverlapHit::OnOverlapBeginCallback);
        PrimComponent->OnComponentHit.AddDynamic(this, &UPBAbilityTask_WaitOverlapHit::OnHitCallback);
    }
}

void UPBAbilityTask_WaitOverlapHit::OnDestroy(bool AbilityEnded)
{
    UPrimitiveComponent *PrimComponent = GetComponent();
    if (PrimComponent)
    {
        PrimComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UPBAbilityTask_WaitOverlapHit::OnOverlapBeginCallback);
        PrimComponent->OnComponentHit.RemoveDynamic(this, &UPBAbilityTask_WaitOverlapHit::OnHitCallback);
    }

    Super::OnDestroy(AbilityEnded);
}

UPrimitiveComponent *UPBAbilityTask_WaitOverlapHit::GetComponent()
{
    // TEMP - we are just using root component's collision. A real system will need more data to specify which component to use
    UPrimitiveComponent *PrimComponent = nullptr;
    AActor *ActorOwner = GetAvatarActor();
    if (ActorOwner)
    {
        PrimComponent = Cast<UPrimitiveComponent>(ActorOwner->GetRootComponent());
        if (!PrimComponent)
        {
            PrimComponent = ActorOwner->FindComponentByClass<UPrimitiveComponent>();
        }
    }

    return PrimComponent;
}

void UPBAbilityTask_WaitOverlapHit::BroadcastHit(FWaitCollisionDelegate &Delegate, AActor *OtherActor, const FHitResult &Hit)
{
    if (OtherActor)
    {
        // Construct TargetData
        FGameplayAbilityTargetData_SingleTargetHit *TargetData = new FGameplayAbilityTargetData_SingleTargetHit(Hit);

        // Give it a handle and return
        FGameplayAbilityTargetDataHandle Handle;
        Handle.Data.Add(TSharedPtr<FGameplayAbilityTargetData>(TargetData));
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            Delegate.Broadcast(Handle);
        }
    }
}