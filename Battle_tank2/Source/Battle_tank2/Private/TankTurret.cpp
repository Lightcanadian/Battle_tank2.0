// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) 
{
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1)* MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + ElevationChange;
	//UE_LOG(LogTemp, Warning, TEXT("totator: %s"), *deltaRotator.ToString());
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
