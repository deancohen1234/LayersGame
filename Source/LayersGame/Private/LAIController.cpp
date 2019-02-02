// Fill out your copyright notice in the Description page of Project Settings.

#include "LAIController.h"
#include "Kismet/GameplayStatics.h"
#include "LCharacter.h"


void ALAIController::BeginPlay()
{
	Super::BeginPlay();

	GoalActor = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn(); //get player controllers pawn and use as goal
}

void ALAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GoalActor) 
	{
		UE_LOG(LogTemp, Error, TEXT("Goal Actor is null"))
		return;
	}

	MoveToActor(GoalActor, AcceptanceRadius);

	//try and damage player
	if (IsActorInRange(GoalActor, AttackDistance))
	{
		ALCharacter* Character = Cast<ALCharacter>(GetPawn());

		if (Character) 
		{
			Character->MakeDamageExplosion();
		}
	}
}

bool ALAIController::IsActorInRange(AActor * TargetActor, float Range)
{
	if (!TargetActor || !GetPawn()) return false;

	float distance = FVector::Distance(GetPawn()->GetActorLocation(), TargetActor->GetActorLocation());

	if (distance < Range)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

