// Fill out your copyright notice in the Description page of Project Settings.

#include "LPowerUp.h"


// Sets default values
ALPowerUp::ALPowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
}

// Called when the game starts or when spawned
void ALPowerUp::BeginPlay()
{
	Super::BeginPlay();	
}

void ALPowerUp::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor->Tags[0] == "Player") 
	{
		OnPlayerPickUp(OtherActor);
	}
}

void ALPowerUp::OnPlayerPickUp(AActor* Player) 
{
	this->Destroy();
}

// Called every frame
void ALPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

