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
	//Add new entry, sort, then remove fourth entry
	/*if (SDG.Score > OldData[2].Score)
	{
		if (SDG.Score > OldData[1].Score)
		{
			if (SDG.Score > OldData[0].Score)
			{
				//player has new highest score
				float oldFirst = OldData[0].Score;
				float oldSecond = OldData[0].Score;
				OldData[0] = SDG;
			}
			else 
			{
				OldData[1] = SDG;
			}
		}
		else 
		{
			OldData[2] = SDG;
		}
	}*/

	OldData.Add(SDG);

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


