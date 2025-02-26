// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LCharacter.generated.h"

class ULHealthComponent;
class UStaticMeshComponent;
class UAudioComponent;

UCLASS()
class LAYERSGAME_API ALCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALCharacter();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	ULHealthComponent* HealthComp = nullptr;

	//dynamic material to pulse
	UMaterialInstanceDynamic* MatInst;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	UCurveFloat* Curve;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MakeDamageExplosion();
	void Kill(); //kills character

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

	bool bTakenDamage; //player is in state of taking damage
	float DamageStartTime; //time of damage hit
	UAudioComponent* MusicComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void GoUpLayer();
	void GoDownLayer();
	void KillCharacter();

	void UpdateMaterialEffects();
	void HandlePlayerDamage();
	void FindMusicComponent();
};
