// @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com> 2021

#include "Abilities/PBAbilitySystemComponent.h"
#include "Abilities/PBGameplayAbility.h"

void UPBAbilitySystemComponent::CancelAbilityByClass(TSubclassOf<UGameplayAbility> Ability)
{
    CancelAbility(Ability.GetDefaultObject());
}

void UPBAbilitySystemComponent::CancelAbilityByTag(FGameplayTag Tag)
{
    FGameplayTagContainer Tags(Tag);
    CancelAbilities(&Tags);
}

void UPBAbilitySystemComponent::AddTag(FGameplayTag Tag)
{
    AddLooseGameplayTag(Tag);
}

void UPBAbilitySystemComponent::RemoveTag(FGameplayTag Tag)
{
    RemoveLooseGameplayTag(Tag);
}

bool UPBAbilitySystemComponent::HasActiveAbilityWithTag(FGameplayTag Tag)
{
    TArray<FGameplayAbilitySpec *> AbilitySpecs;
    GetActivatableGameplayAbilitySpecsByAllMatchingTags(FGameplayTagContainer(Tag), AbilitySpecs);
    return AbilitySpecs.Num() != 0 && AbilitySpecs.Last()->IsActive();
}

UGameplayAbility *UPBAbilitySystemComponent::GetAbilityPrimaryInstanceByClass(TSubclassOf<UGameplayAbility> Ability)
{
    auto AbilitySpecs = GetActivatableAbilities();
    for (auto &Spec : AbilitySpecs)
    {
        if (Spec.Ability == Ability.GetDefaultObject())
        {
            return Spec.GetPrimaryInstance();
        }
    }
    return nullptr;
}

void UPBAbilitySystemComponent::AbilityLocalInputPressed(int32 InputID)
{
    // Consume the input if this InputID is overloaded with GenericConfirm/Cancel and the GenericConfim/Cancel callback is bound
    if (IsGenericConfirmInputBound(InputID))
    {
        LocalInputConfirm();
        return;
    }

    if (IsGenericCancelInputBound(InputID))
    {
        LocalInputCancel();
        return;
    }

    // ---------------------------------------------------------

    ABILITYLIST_SCOPE_LOCK();
    for (FGameplayAbilitySpec &Spec : ActivatableAbilities.Items)
    {
        if (Spec.InputID == InputID)
        {
            if (Spec.Ability)
            {
                Spec.InputPressed = true;
                if (Spec.IsActive())
                {
                    if (Spec.Ability->bReplicateInputDirectly && IsOwnerActorAuthoritative() == false)
                    {
                        ServerSetInputPressed(Spec.Handle);
                    }

                    // Invoke the InputPressed event. This is not replicated here. If someone is listening, they may replicate the InputPressed event to the server.
                    InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
                }
                else
                {
                    UPBGameplayAbility *GA = Cast<UPBGameplayAbility>(Spec.Ability);
                    if (GA && GA->bActivateOnInputPressed)
                    {
                        // Ability is not active, so try to activate it
                        TryActivateAbility(Spec.Handle);
                    }
                }
                AbilitySpecInputPressed(Spec);
            }
        }
    }
}

void UPBAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec &Spec)
{
    if (Spec.Ability->GetInstancingPolicy() == EGameplayAbilityInstancingPolicy::NonInstanced)
    {
        Spec.Ability->InputPressed(Spec.Handle, AbilityActorInfo.Get(), Spec.ActivationInfo);
    }
    else
    {
        TArray<UGameplayAbility *> Instances = Spec.GetAbilityInstances();
        for (UGameplayAbility *Instance : Instances)
        {
            Instance->InputPressed(Spec.Handle, AbilityActorInfo.Get(), Spec.ActivationInfo);
        }
    }
}

void UPBAbilitySystemComponent::OnTagUpdated(const FGameplayTag &Tag, bool TagExists)
{
    OnTagChanged.Broadcast(Tag, TagExists);
}