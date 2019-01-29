// Fill out your copyright notice in the Description page of Project Settings.
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;		
}

void ATank::Initialise(UTankAimingComponent * AiminigComponentToSet)
{
	TankAimingComponent = AiminigComponentToSet;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	//UE_LOG(LogTemp, Warning, TEXT(" %s Hit location: %s"), *GetName(),*HitLocation.ToString());
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond;
	if (Barrel && isReloaded) {
		FRotator Rotation = FRotator(0);
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));

		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

UTankAimingComponent * ATank::GetAimingComponent() const
{
	return TankAimingComponent;
}

