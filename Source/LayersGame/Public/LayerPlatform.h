// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LayerPlatform.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ELayerType : uint8
{
	TopLayer,
	MiddleLayer,
	BottomLayer
};

UCLASS()
class LAYERSGAME_API ALayerPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALayerPlatform();

private:
	ALayerPlatform* AbovePlatform;
	ALayerPlatform* BelowPlatform;

	void SetupReferencePlatforms(); //finds platforms above and below it

	ELayerType GetAboveLayerEnum(ELayerType Layer); //gets next enum in sequence, even with looping
	ELayerType GetBelowLayerEnum(ELayerType Layer); //gets previous enum in sequence, even with looping

protected:

	UPROPERTY(EditAnywhere)
	ELayerType LayerType; //layer type is set in scene for each platform

	UPROPERTY(EditAnywhere)
	bool bIsActiveLayer; //is this layer the one the player is on

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ELayerType GetLayerType() const;
	bool IsLayerActive() const;

	ALayerPlatform* GetAboveLayer() const;
	ALayerPlatform* GetBelowLayer() const;
	
};
