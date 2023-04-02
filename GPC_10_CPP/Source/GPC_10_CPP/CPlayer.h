// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCharacter.h"
#include "IPlayer.h"
#include "CPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GPC_10_CPP_API ACPlayer : public ACCharacter, public IIPlayer
{
	GENERATED_BODY()
	
public:
    ACPlayer();

	void Parkour() override;

protected:
    class USpringArmComponent* SpringArm;
    class UCameraComponent*    Camera;

	UPROPERTY(VisibleAnywhere)
		class UCParkourComponent* ParkourComponent;
};
