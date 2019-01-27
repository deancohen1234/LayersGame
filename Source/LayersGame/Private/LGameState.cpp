// Fill out your copyright notice in the Description page of Project Settings.

#include "LGameState.h"
#include "LEnemySpawnPoint.h"
#include "Kismet/GameplayStatics.h"


void ALGameState::BeginPlay()
{
	Super::BeginPlay();

	Difficulty = StartingDifficulty;

	TArray<AActor*> OutActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALEnemySpawnPoint::StaticClass(), OutActors);

	//cast all actors to desired class then add them to spawnpoints array
	for (int i = 0; i < OutActors.Num(); i++) 
	{
		ALEnemySpawnPoint* SpawnPoint = Cast<ALEnemySpawnPoint>(OutActors[i]);
		SpawnPoints.Add(SpawnPoint);
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ALGameState::SpawnEnemy, Difficulty, true, 2.0f); //difficulty is timer interval

	UE_LOG(LogTemp, Warning, TEXT("Play has begun"));

}


void ALGameState::SpawnEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning Enemy"));
	//get spawn point
	FVector SpawnPoint = GetSpawnPoint();

	//spawn enemy at spawn point
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(EnemyBlueprint, SpawnPoint, FRotator::ZeroRotator, Parameters);

}

FVector ALGameState::GetSpawnPoint()
{
	int randIndex = FMath::RandHelper(SpawnPoints.Num());
	FVector Point = SpawnPoints[randIndex]->GetActorLocation();
	return Point;
}
