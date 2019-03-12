// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LSaveGame.generated.h"

USTRUCT() 
struct FSaveGameData 
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY()
	FString PlayerName;

	UPROPERTY()
	float Score;
};
/**
 * 
 */

UCLASS()
class LAYERSGAME_API ULSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	//top score is first in array [0], lowest score is bottom on array [2]

	UPROPERTY(VisibleAnywhere, Category = Basic)
	TArray<FSaveGameData> TopPlayerData; //top 3 players with score

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	uint32 UserIndex;

	ULSaveGame();

	
	void SetSaveData(FString PlayerName, float Score, TArray<FSaveGameData> OldData);
	TArray<FSaveGameData> GetSaveData() const;
};
