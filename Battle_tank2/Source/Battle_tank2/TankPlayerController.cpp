// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("Player controller begin play"));
	
	ATank* ControlledTank = GetControlledTank();
	/*if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not Controlling a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlling: %s"), *ControlledTank->GetName());
	}*/
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLoacation; // out param
	if (GetSightRayHitLocation(HitLoacation)) {
		GetControlledTank()->AimAt(HitLoacation);
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
		
		GetLookVectorHitLocation(OutHitLocation, LookDirection);
		
		//UE_LOG(LogTemp, Warning, TEXT("Can't get the camera direction"));
		return true;
	}
	//linetrace
	
		


	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & lookDirection) const
{
	FVector WorldLocation;
	
	if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, lookDirection)) {
		UE_LOG(LogTemp, Warning, TEXT("Can't deproject"));
		return false;
	}
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & hitlocation, FVector lookDirection) const
{
	FHitResult hitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (lookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		hitlocation = hitResult.Location;
		return true;
	}
	return false;
}
