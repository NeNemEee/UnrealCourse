// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSControlledOneInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSControlledOneInterface : public UInterface
{
	GENERATED_BODY()
};

class GPC_10_FPS_API IFPSControlledOneInterface
{
	GENERATED_BODY()

public:
	virtual void Crouch()   PURE_VIRTUAL(IFPSControlledOneInterface::Crouch,   return;)
	virtual void LieProne() PURE_VIRTUAL(IFPSControlledOneInterface::LieProne, return;)

	virtual void BeginActionA() PURE_VIRTUAL(IFPSControlledOneInterface::BeginActionA, return;)
	virtual void BeginActionB() PURE_VIRTUAL(IFPSControlledOneInterface::BeginActionB, return;)
	virtual void BeginActionC() PURE_VIRTUAL(IFPSControlledOneInterface::BeginActionC, return;)

	virtual void EndActionA() PURE_VIRTUAL(IFPSControlledOneInterface::EndActionA, return;)
	virtual void EndActionB() PURE_VIRTUAL(IFPSControlledOneInterface::EndActionB, return;)
	virtual void EndActionC() PURE_VIRTUAL(IFPSControlledOneInterface::EndActionC, return;)
};