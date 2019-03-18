// Fill out your copyright notice in the Description page of Project Settings.

#include "LGameState.h"
#include "LEnemySpawnPoint.h"
#include "LSaveGame.h"
#include "Kismet/GameplayStatics.h"


void ALGameState::BeginPlay()
{
	Super::BeginPlay();

	Difficulty = StartingDifficulty;

	SetupEnemySpawning();
}

void ALGameState::SpawnEnemy()
{
	//get spawn point
	FVector SpawnPoint = GetSpawnPoint();

	//spawn enemy at spawn point
	FActorSpawnParameters Parameters;
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyBlueprint, SpawnPoint, FRotator::ZeroRotator, Parameters);
}

void ALGameState::SetupEnemySpawning()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALEnemySpawnPoint::StaticClass(), OutActors);

	//cast all actors to desired class then add them to spawnpoints array
	for (int i = 0; i < OutActors.Num(); i++)
	{
		ALEnemySpawnPoint* SpawnPoint = Cast<ALEnemySpawnPoint>(OutActors[i]);
		SpawnPoints.Add(SpawnPoint);
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ALGameState::SpawnEnemy, Difficulty, true, 2.0f); //difficulty is timer interval
}

void ALGameState::EndGame()
{
	//you need to first get old data from drive because savegame object discards it after saving
	TArray <FSaveGameData> SavedGameData;

	GetSaveGameData(SavedGameData);
	SaveGameData(SavedGameData);
}

void ALGameState::AddScore()
{
	Score += 100.0f;

	Difficulty = FMath::Clamp(Difficulty - DifficultyScalar, 0.1f, StartingDifficulty);

	//GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ALGameState::SpawnEnemy, Difficulty, true, 0.0f); //difficulty is timer interval
}

FVector ALGameState::GetSpawnPoint() const
{
	int randIndex = FMath::RandHelper(SpawnPoints.Num());
	FVector Point = SpawnPoints[randIndex]->GetActorLocation();
	return Point;
}

float ALGameState::GetScore() const
{
	return Score;
}

float ALGameState::GetTopScore()
{
	TArray <FSaveGameData> SavedGameData;

	GetSaveGameData(SavedGameData);

	UE_LOG(LogTemp, Warning, TEXT("Play has begun: %d"), SavedGameData.Num());

	return SavedGameData[0].Score;
}

float ALGameState::GetSecondScore()
{
	TArray <FSaveGameData> SavedGameData;

	GetSaveGameData(SavedGameData);

	return SavedGameData[1].Score;
}

float ALGameState::GetThirdScore()
{
	TArray <FSaveGameData> SavedGameData;

	GetSaveGameData(SavedGameData);

	return SavedGameData[2].Score;
}

void ALGameState::GetSaveGameData(TArray<FSaveGameData> OutSaveGameData)
{
	TArray <FSaveGameData> SavedGameData;

	ULSaveGame* LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	SavedGameData = TArray<FSaveGameData>(LoadGameInstance->GetSaveData());

}

void ALGameState::SaveGameData(TArray<FSaveGameData> OutSaveGameData)
{
	ULSaveGame* SaveGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	SaveGameInstance->SetSaveData("Dean Large Pants", Score, OutSaveGameData);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

}
