// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"

class ALayerPlatform;
/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	private:
		ALayerPlatform* CurrentLayer = nullptr; //layer player is currently on

	public:

		virtual void BeginPlay() override;

		void MoveLayer(bool bMoveUp); //called from character and teleport player to new platform

		FVector GetLocalLayerPosition();
};
