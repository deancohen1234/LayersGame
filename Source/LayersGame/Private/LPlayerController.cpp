// Fill out your copyright notice in the Description page of Project Settings.

#include "LPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "LayerPlatform.h"
#include "LCharacter.h"

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
	if (CurrentLayer == nullptr) return;
	if (GetPawn() == nullptr) return;

	CurrentLayer->SetLayerActive(false); //set old layer active to false
	//local space location of pawn
	FVector PreviousLocalLocation = GetLocalLayerPosition();

	CurrentLayer = bMoveUp ? CurrentLayer->GetAboveLayer() : CurrentLayer->GetBelowLayer();
	CurrentLayer->SetLayerActive(true); //set new layer to active

	//set current layer as active

	if (CurrentLayer == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Layer Null"))
		return;
	}

	FVector NewGlobalLocation = CurrentLayer->GetTransform().TransformPosition(PreviousLocalLocation);

	GetPawn()->SetActorLocation(NewGlobalLocation);
	ALCharacter* Character = Cast<ALCharacter>(GetPawn());

	if (Character) 
	{
		Character->MakeDamageExplosion();
	}
}

FVector ALPlayerController::GetLocalLayerPosition()
{
	if (!GetPawn()) return FVector::ZeroVector;
	
	FVector LocalLocation = CurrentLayer->GetTransform().InverseTransformPosition(GetPawn()->GetActorLocation());
	return LocalLocation;
}

void ALPlayerController::KillPlayer()
{
	UnPossess();
	GetPawn()->Destroy();
}
