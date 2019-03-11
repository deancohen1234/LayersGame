// Fill out your copyright notice in the Description page of Project Settings.

#include "LLayerClear.h"
#include "Kismet/GameplayStatics.h"

void ALLayerClear::OnPlayerPickUp(AActor* Player) 
{
	TSubclassOf<UDamageType> DamageType;
	TArray<AActor*> IgnoredActors = { Player };

	UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, Player->GetActorLocation(), 500.0f, DamageType, IgnoredActors, Player);

	Super::OnPlayerPickUp(Player); //destroys powerup
}


