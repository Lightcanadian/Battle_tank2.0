// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel)return;
	
	FVector OutLaunchVelocity;
	FVector StartLocation =  Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,false,0,0,ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//MoveBarrelToward();
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s"), *GetOwner()->GetName() ,*AimDirection.ToString());
	}
	
	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BerrelToSet)
{
	Barrel = BerrelToSet;
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	//Workout difference between current and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto deltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5);
	//move the barrel certain amount this frame

}

