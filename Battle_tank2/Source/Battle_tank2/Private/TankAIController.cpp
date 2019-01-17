// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI controller begin play"));

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI controller cannot find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Looking at: %s"), *PlayerTank->GetName());
	}

}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {return nullptr;}
	else {return Cast<ATank>(PlayerPawn);}
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!GetControlledTank()) {
		UE_LOG(LogTemp, Warning, TEXT("can't find imself"));
	}
	else {
		if (!GetPlayerTank()) {
			UE_LOG(LogTemp, Warning, TEXT("can't find player"));
		}
		else {
			GetControlledTank()->AimAt(GetPlayerTank()->GetTargetLocation());
			//UE_LOG(LogTemp, Warning, TEXT("Target: %s  VS  actor: %s"), *GetPlayerTank()->GetTargetLocation().ToString(), *GetPlayerTank()->GetActorLocation().ToString());
		}
	}
	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}