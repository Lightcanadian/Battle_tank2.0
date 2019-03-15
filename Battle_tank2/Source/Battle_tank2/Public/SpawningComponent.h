// Copyright embraced IT limited

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawningComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK2_API USpawningComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawningComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:	

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AActor> SpawnClass;
		
};
