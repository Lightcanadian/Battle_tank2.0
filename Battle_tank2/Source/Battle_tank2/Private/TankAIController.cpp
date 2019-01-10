// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AI controller begin play"));

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller not Controlling a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlling: %s"), *ControlledTank->GetName());
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}