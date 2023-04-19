// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSControlledOneInterface.h"
#include "FPSCharacterPose.h"
#include "FPSCharacter.generated.h"

UCLASS()
class GPC_10_FPS_API AFPSCharacter : public ACharacter, public IFPSControlledOneInterface
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void Crouch()   override;
	void LieProne() override;
	
	void BeginActionA() override;
	void BeginActionB() override;
	void BeginActionC() override;

	void EndActionA() override;
	void EndActionB() override;
	void EndActionC() override;

private:
	class IFPSWeaponInterface* Weapon;

	EFPSCharacterPose CharacterPose;
};