// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LAIController.generated.h"


/**
 * 
 */
UCLASS()
class LAYERSGAME_API ALAIController : public AAIController
{
	GENERATED_BODY()
	
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float AcceptanceRadius;

	AActor* GoalActor = nullptr;	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
