// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LSaveGame.h"
#include "LGameState.generated.h"

class ALEnemySpawnPoint;
//struct FSaveGameData;
/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALGameState : public AGameStateBase
{
	GENERATED_BODY()
	
private:

	float Score;
	float Difficulty;

	TArray<ALEnemySpawnPoint*> SpawnPoints;
	FTimerHandle SpawnTimerHandle;

	void SpawnEnemy();
	void SetupEnemySpawning();
	FVector GetSpawnPoint() const;

	bool GetSaveGameData(TArray<FSaveGameData>& OutData);

	void SaveGameData(TArray<FSaveGameData> SaveGameData);

	FString PlayerName = "No Name";

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	TSubclassOf<AActor> EnemyBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	float StartingDifficulty = 3.0f; // time in seconds between each spawned enemy

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	float DifficultyScalar = 0.1f; //amount of seconds taken away from cooldown each enemy death
	
public:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	FSaveGameData GetScoreSaveData(int32 ScoreIndex);

	UFUNCTION(BlueprintCallable)
	float GetScore() const;

	UFUNCTION(BlueprintCallable)
	void SetPlayerName(FString Name);

	UFUNCTION(BlueprintCallable)
	void EndGame();

	void AddScore();
};
