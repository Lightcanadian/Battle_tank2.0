// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//Never call, change in constructor
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankTrack::ApplySidewayForce()
{	
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	UE_LOG(LogTemp, Warning, TEXT("right vector: %s    Velocity: %s"), *GetRightVector().ToString(), *GetComponentVelocity().ToString());
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	
	UE_LOG(LogTemp, Warning, TEXT("Sideway: %f  to %s %s"), CorrectionForce.Size(), *GetOwner()->GetName(), *GetName());
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThottle = FMath::Clamp<float>(CurrentThottle + Throttle, -1, 1);
}

void UTankTrack::DrivingTrack()
{	
	auto ForceApplied = GetForwardVector() * CurrentThottle * TrackMaxDrivingForce;
	auto Forcelocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());	
	UE_LOG(LogTemp, Warning, TEXT("Applying: %f  to %s %s"), ForceApplied.Size(), *GetOwner()->GetName(), *GetName());
	TankRoot->AddForceAtLocation(ForceApplied, Forcelocation);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("track hiting the ground"));
	//ApplySidewayForce();
	DrivingTrack();
	CurrentThottle = 0;
}