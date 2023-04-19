// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeaponInterface.h"
#include "FPSWeapon.generated.h"

UCLASS(Abstract)
class GPC_10_FPS_API AFPSWeapon : public AActor, public IFPSWeaponInterface
{
	GENERATED_BODY()
	
public:	
	AFPSWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	EFPSWeaponType GetWeaponType() const final override;

protected:
	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
		EFPSWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly)
		float Damage;
};