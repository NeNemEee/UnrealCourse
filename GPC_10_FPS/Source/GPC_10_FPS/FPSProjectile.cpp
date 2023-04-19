// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFPSProjectile::AFPSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
}

void AFPSProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

