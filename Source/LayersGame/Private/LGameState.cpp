// Fill out your copyright notice in the Description page of Project Settings.

#include "LGameState.h"
#include "LEnemySpawnPoint.h"
#include "LSaveGame.h"
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

	GetTopScore();
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

float ALGameState::GetScore() const
{
	return Score;
}

float ALGameState::GetTopScore() const
{
	TArray <FSaveGameData> SavedGameData;

	ULSaveGame* LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	SavedGameData = TArray<FSaveGameData>(LoadGameInstance->GetSaveData());

	UE_LOG(LogTemp, Warning, TEXT("Play has begun: %d"), SavedGameData.Num());

	return SavedGameData[0].Score;
}

float ALGameState::GetSecondScore() const
{
	TArray <FSaveGameData> SavedGameData;

	ULSaveGame* LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	SavedGameData = TArray<FSaveGameData>(LoadGameInstance->GetSaveData());

	return SavedGameData[1].Score;
}

float ALGameState::GetThirdScore() const
{
	TArray <FSaveGameData> SavedGameData;

	ULSaveGame* LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	SavedGameData = TArray<FSaveGameData>(LoadGameInstance->GetSaveData());

	return SavedGameData[2].Score;
}

FVector ALGameState::GetSpawnPoint()
{
	int randIndex = FMath::RandHelper(SpawnPoints.Num());
	FVector Point = SpawnPoints[randIndex]->GetActorLocation();
	return Point;
}

void ALGameState::EndGame()
{
	//you need to first get old data from drive because savegame object discards it after saving
	TArray <FSaveGameData> SavedGameData;

	ULSaveGame* LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	SavedGameData = TArray<FSaveGameData>(LoadGameInstance->GetSaveData());

	ULSaveGame* SaveGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	SaveGameInstance->SetSaveData("Dean Large Pants", Score, SavedGameData);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void ALGameState::AddScore()
{
	Score += 100.0f;

	Difficulty = FMath::Clamp(Difficulty - DifficultyScalar, 0.1f, StartingDifficulty);

	//GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ALGameState::SpawnEnemy, Difficulty, true, 0.0f); //difficulty is timer interval
}
