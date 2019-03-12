// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"

class ALayerPlatform;
class USoundCue;
/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	private:
		ALayerPlatform* CurrentLayer = nullptr; //layer player is currently on

		float LastMoveLayerTime = 0.0f;

	protected:

		UPROPERTY(EditDefaultsOnly, Category = "Effects")
		TSubclassOf<UCameraShake> LayerMoveShake;

		UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UForceFeedbackEffect* FeedbackEffect;

		UPROPERTY(EditDefaultsOnly, Category = "Sounds")
		USoundCue* LayerTransferSound;

		UPROPERTY(EditDefaultsOnly, Category = "Player Attributes")
		float MoveLayerCooldown = 0.5f;

	public:

		virtual void BeginPlay() override;

		void MoveLayer(bool bMoveUp); //called from character and teleport player to new platform

		FVector GetLocalLayerPosition();

		void KillPlayer();

		//no other way to access game state from player controller
		UFUNCTION(BlueprintCallable)
		void EndGame();
};
