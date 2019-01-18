// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) 
{
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1)* MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	//UE_LOG(LogTemp, Warning, TEXT("totator: %s"), *deltaRotator.ToString());
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
