// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class ATank;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLE_TANK2_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category= Input)
	void IntendMovementForward(float Throw);

protected:
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerMusicSkill)
	ATank* tank = nullptr;*/
};
