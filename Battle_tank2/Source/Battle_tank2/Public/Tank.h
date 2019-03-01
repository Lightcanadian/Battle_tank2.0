// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//#include "Delegates/Delegate.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declaration
class UTankBarrel;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
//DECLARE_DELEGATE_OneParam(MyTestDelecte);

UCLASS()
class BATTLE_TANK2_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	void ApplyDamage(int32 amount);

	//Retrun current heath as a percentage of starting health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

protected:
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 Health = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth = Health;	
};
