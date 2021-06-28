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
	DefaultAttributes = CreateDefaultSubobject<ULoafAttributeSet>(TEXT("DefaultAttributes"));

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

ULoafAttributeSet* ALoafPlayerState::GetDefaultAttributes() const
{
	return DefaultAttributes;
}

bool ALoafPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}


/** ATTRIBUTES **/
int32 ALoafPlayerState::GetCharacterLevel() const
{
	return DefaultAttributes->GetCharacterLevel();
}


float ALoafPlayerState::GetHealth() const
{
	return DefaultAttributes->GetHealth();
}

float ALoafPlayerState::GetMaxHealth() const
{
	return DefaultAttributes->GetMaxHealth();
}


float ALoafPlayerState::GetJumpPower() const
{
	return DefaultAttributes->GetJumpPower();
}

float ALoafPlayerState::GetMaxJumpPower() const
{
	return DefaultAttributes->GetMaxJumpPower();
}


int ALoafPlayerState::GetCurrentJumps() const
{
	return DefaultAttributes->GetCurrentJumps();
}

int ALoafPlayerState::GetMaxJumps() const
{
	return DefaultAttributes->GetMaxJumps();
}


float ALoafPlayerState::GetMoveAccel() const
{
	return DefaultAttributes->GetMoveAccel();
}

float ALoafPlayerState::MaxMoveSpeed() const
{
	return DefaultAttributes->GetMaxMoveSpeed();
}
