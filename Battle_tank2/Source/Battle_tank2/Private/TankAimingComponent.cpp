// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (RoundLeft <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecond)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Lock;
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))return;
	
	FVector OutLaunchVelocity;
	FVector StartLocation =  Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace)) {
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		
		MoveBarrelToward(AimDirection);
	}
	
	
}

int32 UTankAimingComponent::GetRoundLeft() const
{
	return RoundLeft;
}

void UTankAimingComponent::Fire()
{
	//bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond;
	if (!ensure(Barrel)) return;
	if (!ensure(ProjectileBlueprint)) return;

	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo) {
		FRotator Rotation = FRotator(0);
		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));		
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::MoveBarrelToward(FVector TargetAimDirection)
{
	if (!ensure(Barrel && Turret)) return;
	//Workout difference between current and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = TargetAimDirection.Rotation();
	auto deltaRotator = AimAsRotator - BarrelRotator;
	
	if (deltaRotator.Yaw < -180 || deltaRotator.Yaw > 180) {
		Turret->Rotate(-deltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(deltaRotator.Yaw);
	}
	
	Barrel->Elevate(deltaRotator.Pitch);
	//move the barrel certain amount this frame

}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;
	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.01);
}

