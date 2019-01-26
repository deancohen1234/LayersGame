// Fill out your copyright notice in the Description page of Project Settings.

#include "LAIController.h"
#include "Kismet/GameplayStatics.h"

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
	}

	MoveToActor(GoalActor, AcceptanceRadius);
}

