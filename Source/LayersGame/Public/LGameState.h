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

	float Score;

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

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	float DifficultyScalar = 0.1f; //amount of seconds taken away from cooldown each enemy death
	
public:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	float GetScore() const;

	UFUNCTION(BlueprintCallable)
	float GetTopScore() const;

	UFUNCTION(BlueprintCallable)
	float GetSecondScore() const;

	UFUNCTION(BlueprintCallable)
	float GetThirdScore() const;

	UFUNCTION(BlueprintCallable)
	void EndGame ();

	void AddScore();
};
