// Fill out your copyright notice in the Description page of Project Settings.

#include "LSaveGame.h"

ULSaveGame::ULSaveGame() 
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}

void ULSaveGame::SetSaveData(FString PlayerName, float Score, TArray<FSaveGameData> OldData)
{
	FSaveGameData SDG;
	SDG.PlayerName = PlayerName;
	SDG.Score = Score;

	UE_LOG(LogTemp, Warning, TEXT("Resetting Data: %d"), TopPlayerData.Num());


	if (OldData.Num() < 3) 
	{
		//populate array initially
		OldData.SetNum(3, true);
		
		OldData[0] = SDG;
		OldData[1] = SDG;
		OldData[2] = SDG;

	}

	//if player already has score under their name, don't add another score
	if (!DoesDataExist(SDG)) 
	{
		OldData.Add(SDG);
	}

	OldData.Sort([](const FSaveGameData& Lhs, const FSaveGameData& Rhs) -> bool {
		// sort by score, higher score moves up
		if (Lhs.Score > Rhs.Score) return true;
		if (Lhs.Score < Rhs.Score) return false;

		return true;
	});

	OldData.Pop(true);

	TopPlayerData = OldData;
}

TArray<FSaveGameData> ULSaveGame::GetSaveData() const
{
	return TopPlayerData;
}

bool ULSaveGame::DoesDataExist(FSaveGameData Data) 
{
	for (int i = 0; i < TopPlayerData.Num(); i++) 
	{
		FSaveGameData ArrayElement = TopPlayerData[i];
		
		if (ArrayElement.PlayerName == Data.PlayerName && ArrayElement.Score == Data.Score) 
		{
			//player already has score that is under their name, data does exist
			return true;
		}
	}

	return false;
}


