// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "Camera/PlayerCameraManager.h"
#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *  Created on lecture 128
 */
UCLASS()
class BATTLE_TANK2_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:

	/**
	* Return the controled tank that the user or the AI is using
	*/
	ATank* GetControlledTank() const;

	void AimTowardCrosshair();

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	
	bool GetLookDirection(FVector2D screenLocation, FVector& lookDirection) const;

	bool GetLookVectorHitLocation(FVector& hitlocation, FVector lookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0;


};