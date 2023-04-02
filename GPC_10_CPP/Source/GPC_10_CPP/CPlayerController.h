// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GPC_10_CPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ACPlayerController();

    virtual void SetupInputComponent() override;

private:
    void MoveFB(float const Value);
    void MoveLR(float const Value);
    void LookLR(float const Value);
    void LookUD(float const Value);

	void Parkour();
};
