// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Math/UnrealMathUtility.h"


void UTankBarrel::Elevate(float RelativeSpeed) 
{
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed,-1,1 )* MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	//UE_LOG(LogTemp, Warning, TEXT("elevation reach"));
	SetRelativeRotation(FRotator(FMath::Clamp<float>( RawNewElevation,MinElevationDegree,MaxElevationDegree), 0, 0));
}