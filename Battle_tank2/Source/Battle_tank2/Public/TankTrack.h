// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLE_TANK2_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UTankTrack();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplySidewayForce();

	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	void DrivingTrack();

	//Max force per track in newton  (Force = mass * acceleration)
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 400000; //assum 40 tonnetank and 1g accelleration

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThottle = 0;
};
