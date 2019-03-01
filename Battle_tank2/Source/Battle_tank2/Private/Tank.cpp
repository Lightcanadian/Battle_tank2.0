// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();	
	CurrentHealth = Health;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoint = FMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp<int32>(DamagePoint, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("receiving damage: %f"), DamageAmount);
	ApplyDamage(DamageToApply);
	return DamageToApply;
}

void ATank::ApplyDamage(int32 amount)
{
	CurrentHealth -= amount;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("tank dead, braodcasting"));
		OnDeath.Broadcast();
	}
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/(float)Health;
}
