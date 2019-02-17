// Fill out your copyright notice in the Description page of Project Settings.

#include "LHealthComponent.h"


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
		OnDeath.Broadcast();
	}

	return DamageAmount;
}

float ULHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

