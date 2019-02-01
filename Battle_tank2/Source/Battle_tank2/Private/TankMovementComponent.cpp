// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMovementForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	//TODO prevent double speed
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	auto AiForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(AiForwardIntention, TankForward);
	IntendMovementForward(ForwardThrow);
	IntendTurnLeft(FVector::CrossProduct(AiForwardIntention,TankForward).Z);

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %f"), *TankName, test);
}
