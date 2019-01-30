// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Public/TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLE_TANK2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankAimingComponent * AimingComponentToSet);
	
	//UPROPERTY(BlueprintReadWrite)
	//UTankMovementComponent* TankMovementComponent = nullptr;

public:	
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	void BeginPlay() override;

	void AimAt(FVector HitLocation);

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Read https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf

	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSecond = 3;

	double LastFireTime = 0;

	UFUNCTION(BlueprintCallable, Category = Setup)
	UTankAimingComponent* GetAimingComponent() const;

private:
	UTankAimingComponent * TankAimingComponent = nullptr;
};
