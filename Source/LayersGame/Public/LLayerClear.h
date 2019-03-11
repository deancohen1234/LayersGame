// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LPowerUp.h"
#include "LLayerClear.generated.h"

/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALLayerClear : public ALPowerUp
{
	GENERATED_BODY()
	
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float DamageRadius = 500.0f;

	virtual void OnPlayerPickUp(AActor* Player) override;
	
};
