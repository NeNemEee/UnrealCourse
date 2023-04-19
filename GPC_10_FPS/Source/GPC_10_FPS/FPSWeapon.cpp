// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSWeapon.h"

AFPSWeapon::AFPSWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
}

void AFPSWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EFPSWeaponType AFPSWeapon::GetWeaponType() const
{
	return WeaponType;
}