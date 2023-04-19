// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSGunInterface.generated.h"

UENUM(BlueprintType)
enum class EFPSGunType : uint8
{
	None,
	AssaultRifle,
	Shotgun,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSGunInterface : public UInterface
{
	GENERATED_BODY()
};

class GPC_10_FPS_API IFPSGunInterface
{
	GENERATED_BODY()

protected:
	virtual EFPSGunType GetGunType() const PURE_VIRTUAL(IFPSGunInterface::GetGunType, return EFPSGunType::None;)

	virtual bool Fire()	  PURE_VIRTUAL(IFPSGunInterface::Fire,   return false;)
	virtual bool Reload() PURE_VIRTUAL(IFPSGunInterface::Reload, return false;)
	
	virtual void ZoomIn()  PURE_VIRTUAL(IFPSGunInterface::ZoomIn,  return;)
	virtual void ZoomOut() PURE_VIRTUAL(IFPSGunInterface::ZoomOut, return;)
};