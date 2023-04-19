// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSGun.h"
#include "FPSAssaultRifle.generated.h"

UCLASS()
class GPC_10_FPS_API AFPSAssaultRifle : public AFPSGun
{
	GENERATED_BODY()
	
public:
	AFPSAssaultRifle();

protected:
	bool Fire() override;
};
