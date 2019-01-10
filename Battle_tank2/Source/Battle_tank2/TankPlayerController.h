// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	/** 
	* Return the controled tank that the user or the AI is using
	*/
	ATank* GetControlledTank() const;

	void BeginPlay() override;


};
