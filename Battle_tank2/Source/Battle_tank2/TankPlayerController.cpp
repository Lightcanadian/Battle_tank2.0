// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();	
	
	
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!ensure(AimingComponent)) { return; }
	FVector HitLoacation; // out param
	
	if (GetSightRayHitLocation(HitLoacation)) {
		AimingComponent->AimAt(HitLoacation);
	}	
	//if hit landscape
		//tell controlled tank to aim at this point
}

//Get world location when linetracing through crosshair and ray trace
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	//Find the crosshaire position
	int32 ViewportSizeX, ViewportSizeY;

	//Get the size of the viewport (Resolution)
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//Use the viewport size to determin a specific location on the screen
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);

	//de project the screen position of the crosshaire to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}
	//linetrace
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & lookDirection) const
{
	FVector WorldLocation;
	
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, lookDirection)) {
		return false;
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & hitlocation, FVector lookDirection) const
{
	FHitResult hitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (lookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)) {
		hitlocation = hitResult.Location;
		return true;
	}
	return false;
}

void ATankPlayerController::OnPosessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("My tank is dead"));
	//DetachFromPawn();
	StartSpectatingOnly();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PosessessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessessedTank)) { return; }
		//subscribe to death event
		PosessessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPosessedTankDeath);
	}
}
