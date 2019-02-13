// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLE_TANK2_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	//how close can the Ai can get
private:
	UTankAimingComponent* AimingComponent = nullptr;

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
		float AcceptanceRadius = 8000.0f;
};
