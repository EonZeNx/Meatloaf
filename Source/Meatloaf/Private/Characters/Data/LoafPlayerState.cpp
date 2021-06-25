#include "Characters/Data/LoafPlayerState.h"

#include "AbilitySystemComponent.h"


ALoafPlayerState::ALoafPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	ASC = CreateDefaultSubobject<ULoafAbilitySystemComponent>(TEXT("ASC"));
	ASC->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSetBase = CreateDefaultSubobject<ULoafAttributeSet>(TEXT("AttributeSetBase"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	// Cache tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

ULoafAbilitySystemComponent* ALoafPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

ULoafAttributeSet* ALoafPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ALoafPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ALoafPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
	
}


/** ATTRIBUTES **/
float ALoafPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ALoafPlayerState::GetJumpPower() const
{
	return AttributeSetBase->GetJumpPower();
}
