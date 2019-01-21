// Fill out your copyright notice in the Description page of Project Settings.

#include "LayerPlatform.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALayerPlatform::ALayerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LayerType = ELayerType::TopLayer;
}

// Called when the game starts or when spawned
void ALayerPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetupReferencePlatforms(); //find layer's above and below platforms and set them	
}

// Called every frame
void ALayerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALayerPlatform::SetupReferencePlatforms()
{
	TArray<AActor*> OutArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALayerPlatform::StaticClass(), OutArray);

	ELayerType AboveEnum = GetAboveLayerEnum(LayerType); //layer type is specific for this actor
	ELayerType BelowEnum = GetBelowLayerEnum(LayerType);

	//go through array and set above and below platforms
	for (int i = 0; i < OutArray.Num(); i++) 
	{
		ALayerPlatform* layer = Cast<ALayerPlatform>(OutArray[i]);

		if (layer == nullptr) return;

		if (layer->GetLayerType() == AboveEnum) 
		{
			AbovePlatform = layer;
		}
		else if (layer->GetLayerType() == BelowEnum) 
		{
			BelowPlatform = layer;
		}
	}
}

ELayerType ALayerPlatform::GetBelowLayerEnum(ELayerType Layer)
{
	int val = (int)Layer;
	val++;

	if (val >= 3) 
	{
		val = 0;
	}

	return (ELayerType)val;
}

ELayerType ALayerPlatform::GetAboveLayerEnum(ELayerType Layer)
{
	int val = (int)Layer;
	val--;

	if (val <= -1)
	{
		val = 2;
	}

	return (ELayerType)val;
}

ELayerType ALayerPlatform::GetLayerType() const
{
	return LayerType;
}

bool ALayerPlatform::IsLayerActive() const
{
	return bIsActiveLayer;
}

ALayerPlatform * ALayerPlatform::GetAboveLayer() const
{
	return AbovePlatform;
}

ALayerPlatform * ALayerPlatform::GetBelowLayer() const
{
	return BelowPlatform;
}

