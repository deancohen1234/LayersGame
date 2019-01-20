// Fill out your copyright notice in the Description page of Project Settings.

#include "LCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "LPlayerController.h"


// Sets default values
ALCharacter::ALCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 3.0f;

}

// Called when the game starts or when spawned
void ALCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ALCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ALCharacter::MoveRight);

	PlayerInputComponent->BindAction("GoUp", IE_Pressed, this, &ALCharacter::GoUpLayer);
	PlayerInputComponent->BindAction("GoDown", IE_Pressed, this, &ALCharacter::GoDownLayer);

}

void ALCharacter::MoveForward(float Value) 
{
	AddMovementInput(GetActorForwardVector() * Value, MoveSpeed);
}

void ALCharacter::MoveRight(float Value) 
{
	AddMovementInput(GetActorRightVector() * Value, MoveSpeed);
}

void ALCharacter::GoUpLayer()
{
	ALPlayerController* playerController = Cast<ALPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->MoveUpLayer();
}

void ALCharacter::GoDownLayer()
{
	ALPlayerController* playerController = Cast<ALPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->MoveDownLayer();
}



