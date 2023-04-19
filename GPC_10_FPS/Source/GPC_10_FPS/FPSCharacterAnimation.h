// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "FPSCharacterAnimationInterface.h"
#include "FPSCharacterAnimation.generated.h"

UCLASS(Abstract)
class GPC_10_FPS_API UFPSCharacterAnimation : public UAnimInstance, public IFPSCharacterAnimationInterface
{
	GENERATED_BODY()

public:
	void NativeUpdateAnimation(float const DeltaSeconds) override;

	void SetCharacterPose(EFPSCharacterPose const Pose) override;
	void SetAiming(bool const Aiming) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Pitch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		EFPSCharacterPose CharacterPose;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bAiming;
};