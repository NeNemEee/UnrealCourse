// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CBoxCollisionActor.h"
#include "CEvent.generated.h"

FUNC_DECLARE_EVENT(ACEvent, FExplosion, void)

UCLASS()
class GPC_10_CPP_API ACEvent : public ACBoxCollisionActor
{
	GENERATED_BODY()
	
public:	
    FExplosion OnExplosion;

protected:
	virtual void BeginPlay() override;

    TMulticastDelegate<void(int, float)> asdas;

public:	
    UFUNCTION()
    void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
