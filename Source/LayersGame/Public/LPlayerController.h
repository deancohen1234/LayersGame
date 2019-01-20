// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	private:
		AActor* BottomPlatform;
		AActor* MiddlePlatform;
		AActor* TopPlatform;

		AActor* CurrentLayer = nullptr; //layer player is currently on

		AActor* FindNextLayer(bool bGoingUp); //true player is teleporting up from current layer

	protected:

		UPROPERTY(EditDefaultsOnly)
		FString BottomPlatformName;

		UPROPERTY(EditDefaultsOnly)
		FString MiddlePlatformName;

		UPROPERTY(EditDefaultsOnly)
		FString TopPlatformName;

		void SetBottomPlatform(AActor* BotPlatform);
		void SetMiddlePlatform(AActor* MidPlatform);
		void SetTopPlatform(AActor* TopPlatform);

	public:

		virtual void BeginPlay() override;

		void MoveUpLayer(); //called from character and teleport player to new platform
		void MoveDownLayer();
};
