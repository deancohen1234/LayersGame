// Fill out your copyright notice in the Description page of Project Settings.

#include "LCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "LPlayerController.h"
#include "LHealthComponent.h"
#include "Components/AudioComponent.h"


// Sets default values
ALCharacter::ALCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MoveSpeed = 3.0f;
	DamageRadius = 75.0f;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HealthComp = CreateDefaultSubobject<ULHealthComponent>("Health Component");

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

	playerController->MoveLayer(true);
}

void ALCharacter::GoDownLayer()
{
	ALPlayerController* playerController = Cast<ALPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	playerController->MoveLayer(false);
}

//create damage radius around character
void ALCharacter::MakeDamageExplosion()
{
	TSubclassOf<UDamageType> type;
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this); //ignore yourself in the damage sphere

	UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, GetActorLocation(), DamageRadius, type, IgnoredActors, this);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
}

float ALCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	UE_LOG(LogTemp, Warning, TEXT("Taking Damaged"));

	HealthComp->HandleDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UpdateEffects(); //update visual and audio effects for damage hits

	return DamageAmount;
}

void ALCharacter::Kill()
{
	HealthComp->OnDeath.Broadcast(); //goes into health component and broadcasts death
}

void ALCharacter::UpdateEffects()
{
	UpdateMaterialEffects();
	UpdateMusicEffects();
}

void ALCharacter::UpdateMaterialEffects()
{
	if (MatInst == nullptr)
	{
		MatInst = MeshComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(0, MeshComponent->GetMaterial(0));
	}

	if (MatInst)
	{
		UE_LOG(LogTemp, Warning, TEXT("Updating Mat"));
		MatInst->SetScalarParameterValue("LastTimeDamageTaken", GetWorld()->TimeSeconds);
	}
}

void ALCharacter::UpdateMusicEffects()
{
	//only update music if character is player
	if (Tags[0] == "Player")
	{
		TArray<AActor*> OutArray;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Music", OutArray); //get the music actor

		if (OutArray.Num() > 1 || OutArray.Num() == 0)
		{
			UE_LOG(LogTemp, Error, TEXT("There are two actors or no actors with the Music tag, there can only be one"));
			return;
		}

		UAudioComponent* AudioComponent = Cast<UAudioComponent>(OutArray[0]->GetComponentByClass(UAudioComponent::StaticClass()));

		if (!AudioComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("Audio Component Not Found on Music Actor"));
			return;
		}

		//AudioComponent->SetFloatParameter(FName("Pitch"), 0.5f);
	}
}



