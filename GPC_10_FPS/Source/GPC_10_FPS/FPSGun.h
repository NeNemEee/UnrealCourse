// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSWeapon.h"
#include "FPSGunInterface.h"
#include "FPSGun.generated.h"

UCLASS(Abstract)
class GPC_10_FPS_API AFPSGun : public AFPSWeapon, public IFPSGunInterface
{
	GENERATED_BODY()
	
public:	
	AFPSGun();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	EFPSGunType GetGunType() const final override;

	void BeginActionA() final override;
	void BeginActionB() final override;
	void BeginActionC() final override;

	void EndActionA() final override;
	void EndActionB() final override;
	void EndActionC() final override;

	void ZoomIn()  final override;
	void ZoomOut() final override;

protected:
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* MuzzleFlash;

	UPROPERTY(VisibleAnywhere)
		class UAudioComponent* GunShotSound;

	UPROPERTY(EditDefaultsOnly)
		FName MuzzleSocket;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMatineeCameraShake> RecoilClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFPSBullet> AmmoClass;

	UPROPERTY(VisibleDefaultsOnly)
		EFPSGunType GunType;

	//TODO: AmmoMax가 아닌 재장전 단위가 필요.
	int32 AmmoNow;
	int32 AmmoMax;
};