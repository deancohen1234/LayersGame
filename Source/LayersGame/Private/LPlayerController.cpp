// Fill out your copyright notice in the Description page of Project Settings.

#include "LPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ALPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//get references to three platforms
	TArray<AActor*> OutArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Platform", OutArray);

	UE_LOG(LogTemp, Warning, TEXT("Length %d"), OutArray.Num());

	for (int i = 0; i < OutArray.Num(); i++)
	{
		AActor* platform = OutArray[i];

		if (platform->GetName() == TopPlatformName) 
		{
			SetTopPlatform(platform);
		}

		else if (platform->GetName() == MiddlePlatformName) 
		{
			SetMiddlePlatform(platform);
		}

		else if (platform->GetName() == BottomPlatformName) 
		{
			SetBottomPlatform(platform);
		}

		else 
		{
			UE_LOG(LogTemp, Error, TEXT("Setting platforms failed. %s is the culprit"), *platform->GetName());
		}
	}

	CurrentLayer = MiddlePlatform; //defaulting top platform on start
}

void ALPlayerController::SetBottomPlatform(AActor * BPlatform)
{
	BottomPlatform = BPlatform;
}

void ALPlayerController::SetMiddlePlatform(AActor * MPlatform)
{
	MiddlePlatform = MPlatform;
}

void ALPlayerController::SetTopPlatform(AActor * TPlatform)
{
	TopPlatform = TPlatform;
}

//TODO condense move up and move down functions into one with a bool determining up or down
void ALPlayerController::MoveUpLayer()
{
	CurrentLayer = FindNextLayer(true);

	if (CurrentLayer == nullptr) 
	{
		return;
	}

	GetPawn()->SetActorLocation(CurrentLayer->GetActorLocation() + FVector(1.5f, 1.5f, 1.0f));
}

void ALPlayerController::MoveDownLayer()
{
	CurrentLayer = FindNextLayer(false);

	if (CurrentLayer == nullptr)
	{
		return;
	}

	GetPawn()->SetActorLocation(CurrentLayer->GetActorLocation() + FVector(1.5f, 1.5f, 1.0f));
}

//
AActor * ALPlayerController::FindNextLayer(bool bGoingUp)
{
	if (CurrentLayer == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("Current Layer is null"));
		return nullptr;
	}

	if (CurrentLayer == BottomPlatform) 
	{
		if (bGoingUp) 
		{
			return MiddlePlatform;
		}
		else 
		{
			return TopPlatform;
		}
	}

	else if (CurrentLayer == MiddlePlatform) 
	{
		if (bGoingUp) 
		{
			return TopPlatform;
		}

		else 
		{
			return BottomPlatform;
		}
	}

	else if (CurrentLayer == TopPlatform) 
	{
		if (bGoingUp) 
		{
			return BottomPlatform;
		}
		else 
		{
			return MiddlePlatform;
		}
	}

	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Current Layer not the same as the platforms"));
		return nullptr;
	}
}