// Fill out your copyright notice in the Description page of Project Settings.

#include "LCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "LPlayerController.h"


// Sets default values
ALCharacter::ALCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 3.0f;
	DamageRadius = 75.0f;

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

void ALCharacter::MakeDamageExplosion()
{
	TSubclassOf<UDamageType> type;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, GetActorLocation(), DamageRadius, type, IgnoredActors);
	DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 16, FColor::Cyan, false, 1.0f, 0, 1.0f);
	
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

	playerController->MoveLayer(true);
}

void ALCharacter::GoDownLayer()
{
	ALPlayerController* playerController = Cast<ALPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->MoveLayer(false);
}

float ALCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	UE_LOG(LogTemp, Warning, TEXT("Taking Damaged"));

	this->Destroy(); //if you take damage you die

	return DamageAmount;
}



