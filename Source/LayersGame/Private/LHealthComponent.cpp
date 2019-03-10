// Fill out your copyright notice in the Description page of Project Settings.

#include "LHealthComponent.h"
#include "LGameState.h"
#include "Kismet/GameplayStatics.h"

/*
Idea
Make 3 UDamageType classes
Layer Transfer Damage
Player Hurt Damage
Self Damage
Powerup Damage
*/

// Sets default values for this component's properties
ULHealthComponent::ULHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
	
}


// Called every frame
void ULHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float ULHealthComponent::HandleDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;

	if (CurrentHealth <= 0) 
	{
		if (!DamageCauser) DamageAmount;
		TArray<FName> Tags = DamageCauser->Tags;
		if (Tags[0] == "Player")
		{
			ALGameState* GameState = Cast<ALGameState>(UGameplayStatics::GetGameState(GetWorld()));

			if (GameState) 
			{
				//enemy was killed by player, so add score
				UE_LOG(LogTemp, Warning, TEXT("Adding Score"));
				GameState->AddScore();
			}
		}

		//character killed
		OnDeath.Broadcast();
	}

	return DamageAmount;
}

float ULHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

