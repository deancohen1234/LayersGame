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

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	float AttackDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Attacking")
	float AttackDistance = 10.0f; //distance at which enemies will try and attack

	AActor* GoalActor = nullptr;

	float AttackStartTime = 0.0f; //time when AI wanted to start attack
	bool bIsAttacking = false;

	bool IsActorInRange(AActor* TargetActor, float Range); //checks if target actor is within range of pawn
	void Attack();


public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
