// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacterAnimation.h"

void UFPSCharacterAnimation::NativeUpdateAnimation(float const DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (APawn* const Pawn = TryGetPawnOwner())
	{
		FVector const& Velocity = Pawn->GetVelocity();

		Speed = Velocity.Size2D();

		//TODO: Pawn->GetActorRotation() 적절성 확인
		Direction = CalculateDirection(Velocity, Pawn->GetActorRotation());
		Pitch = Pawn->GetBaseAimRotation().Pitch;
	}
}

void UFPSCharacterAnimation::SetCharacterPose(EFPSCharacterPose const Pose)
{
	CharacterPose = Pose;
}

void UFPSCharacterAnimation::SetAiming(bool const Aiming)
{
	bAiming = Aiming;
}