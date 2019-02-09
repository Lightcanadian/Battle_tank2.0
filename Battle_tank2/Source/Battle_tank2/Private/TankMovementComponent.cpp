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
	//TODO prevent double speed
	if (!ensure(LeftTrack && RightTrack)) return;
	UE_LOG(LogTemp, Warning, TEXT("Move forward received: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) return;
	UE_LOG(LogTemp, Warning, TEXT("Turn right received: %f"), Throw);
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
	IntendTurnRight(FVector::CrossProduct(AiForwardIntention,TankForward).Z);
}
