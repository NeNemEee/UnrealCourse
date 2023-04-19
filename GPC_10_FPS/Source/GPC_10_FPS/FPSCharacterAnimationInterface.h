// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSCharacterPose.h"
#include "FPSCharacterAnimationInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSCharacterAnimationInterface : public UInterface
{
	GENERATED_BODY()
};

class GPC_10_FPS_API IFPSCharacterAnimationInterface
{
	GENERATED_BODY()

public:
	virtual void SetCharacterPose(EFPSCharacterPose const Pose) PURE_VIRTUAL(IFPSCharacterAnimationInterface::SetCharacterPose, return;)
	virtual void SetAiming(bool const Aiming) PURE_VIRTUAL(IFPSCharacterAnimationInterface::SetAiming, return;)
};