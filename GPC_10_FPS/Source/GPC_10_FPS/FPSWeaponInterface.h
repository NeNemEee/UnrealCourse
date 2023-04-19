// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSWeaponInterface.generated.h"

UENUM(BlueprintType)
enum class EFPSWeaponType : uint8
{
	None,
	Gun,
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

class GPC_10_FPS_API IFPSWeaponInterface
{
	GENERATED_BODY()

public:
	virtual EFPSWeaponType GetWeaponType() const PURE_VIRTUAL(IFPSWeaponInterface::GetWeaponType, return EFPSWeaponType::None;)

	virtual void BeginActionA() PURE_VIRTUAL(IFPSWeaponInterface::BeginActionA, return;)
	virtual void BeginActionB() PURE_VIRTUAL(IFPSWeaponInterface::BeginActionB, return;)
	virtual void BeginActionC() PURE_VIRTUAL(IFPSWeaponInterface::BeginActionC, return;)

	virtual void EndActionA() PURE_VIRTUAL(IFPSWeaponInterface::EndActionA, return;)
	virtual void EndActionB() PURE_VIRTUAL(IFPSWeaponInterface::EndActionB, return;)
	virtual void EndActionC() PURE_VIRTUAL(IFPSWeaponInterface::EndActionC, return;)
};