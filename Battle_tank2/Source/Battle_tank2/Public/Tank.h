// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Public/TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLE_TANK2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent * TankAimingComponent = nullptr;

public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation);

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4000;

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

};
