// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGun.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

AFPSGun::AFPSGun()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponType = EFPSWeaponType::Gun;

	MuzzleFlash = CreateDefaultSubobject<UParticleSystemComponent>("MuzzleFlash");
	MuzzleFlash->SetupAttachment(Mesh);

	GunShotSound = CreateDefaultSubobject<UAudioComponent>("GunShotSound");
	GunShotSound->SetupAttachment(Mesh);
}

void AFPSGun::BeginPlay()
{
	Super::BeginPlay();

	FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, true);

	MuzzleFlash->AttachToComponent(Mesh, Rules, MuzzleSocket);
	GunShotSound->AttachToComponent(Mesh, Rules, MuzzleSocket);
	
}

void AFPSGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EFPSGunType AFPSGun::GetGunType() const
{
	return GunType;
}

void AFPSGun::BeginActionA()
{
	Fire();
}

void AFPSGun::BeginActionB()
{
	ZoomIn();
}

void AFPSGun::BeginActionC()
{
	Reload();
}

void AFPSGun::EndActionA()
{
}

void AFPSGun::EndActionB()
{
	ZoomOut();
}

void AFPSGun::EndActionC()
{
}

void AFPSGun::ZoomIn()
{
}

void AFPSGun::ZoomOut()
{
}