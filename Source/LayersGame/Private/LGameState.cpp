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
	/*
	TArray <FSaveGameData> GameData;

	if (GetSaveGameData(GameData)) 
	{
		SaveGameData(GameData);
	}
	*/
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

void ALGameState::SetPlayerName(FString Name)
{
	PlayerName = Name;
	
	TArray <FSaveGameData> GameData;

	if (GetSaveGameData(GameData))
	{
		SaveGameData(GameData);
	}
}

FSaveGameData ALGameState::GetScoreSaveData(int32 ScoreIndex) 
{
	TArray <FSaveGameData> GameData;

	GetSaveGameData(GameData);

	if (GameData.Num() == 0) return FSaveGameData();
	UE_LOG(LogTemp, Warning, TEXT("Save Data Num : %d"), GameData.Num());


	return GameData[ScoreIndex];
}


bool ALGameState::GetSaveGameData(TArray<FSaveGameData>& OutData)
{
	ULSaveGame* LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	LoadGameInstance = Cast<ULSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));

	if (!LoadGameInstance) 
	{
		//if there is no data, create new data
		FSaveGameData Data; //Template data
		Data.PlayerName = "Dean";
		Data.Score = 100.0f;

		TArray<FSaveGameData> SaveData;
		SaveData.Add(Data);
		SaveGameData(SaveData);
		return false;
	}

	OutData = TArray<FSaveGameData>(LoadGameInstance->GetSaveData());

	return true;
}

void ALGameState::SaveGameData(TArray<FSaveGameData> OutSaveGameData)
{
	UE_LOG(LogTemp, Warning, TEXT("Saving Game"));

	ULSaveGame* SaveGameInstance = Cast<ULSaveGame>(UGameplayStatics::CreateSaveGameObject(ULSaveGame::StaticClass()));
	SaveGameInstance->SetSaveData(PlayerName, Score, OutSaveGameData);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

}
