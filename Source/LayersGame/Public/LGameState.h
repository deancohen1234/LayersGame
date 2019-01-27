// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LGameState.generated.h"

class ALEnemySpawnPoint;
/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALGameState : public AGameStateBase
{
	GENERATED_BODY()
	
private:

	float Difficulty;

	TArray<ALEnemySpawnPoint*> SpawnPoints;

	FTimerHandle SpawnTimerHandle;

	void SpawnEnemy();

	FVector GetSpawnPoint();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	TSubclassOf<AActor> EnemyBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	float StartingDifficulty = 3.0f; // time in seconds between each spawned enemy
	
public:
	
	virtual void BeginPlay() override;
};
