// Fill out your copyright notice in the Description page of Project Settings.

#include "LPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "LayerPlatform.h"

void ALPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Find current/starting platform
	TArray<AActor*> OutArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALayerPlatform::StaticClass(), OutArray);

	for (int i = 0; i < OutArray.Num(); i++) 
	{
		ALayerPlatform* layer = Cast<ALayerPlatform>(OutArray[i]);

		if (layer->IsLayerActive()) 
		{
			CurrentLayer = layer;
			break;
		}
	}

	if (CurrentLayer == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to starting platform"));
	}
}

//TODO condense move up and move down functions into one with a bool determining up or down
void ALPlayerController::MoveLayer(bool bMoveUp)
{
	if (CurrentLayer == nullptr)
	{
		return;
	}

	//local space location of pawn
	FVector PreviousLocalLocation = CurrentLayer->GetTransform().InverseTransformPosition(GetPawn()->GetActorLocation());

	CurrentLayer = bMoveUp ? CurrentLayer->GetAboveLayer() : CurrentLayer->GetBelowLayer();

	if (CurrentLayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Layer Null"))
		return;
	}

	FVector NewGlobalLocation = CurrentLayer->GetTransform().TransformPosition(PreviousLocalLocation);

	GetPawn()->SetActorLocation(NewGlobalLocation);

}