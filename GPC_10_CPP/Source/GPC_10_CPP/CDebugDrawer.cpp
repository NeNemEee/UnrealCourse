// Fill out your copyright notice in the Description page of Project Settings.

#include "CDebugDrawer.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACDebugDrawer::ACDebugDrawer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Offsets[0] = FVector(0, 0, 0);
    Offsets[1] = FVector(0, 1000, 0);
    Offsets[2] = FVector(0, 500, 0);
    Offsets[3] = FVector(0, 1500, 0);
    Offsets[4] = FVector(500, 1000, 0);

    Box = FBox(FVector(-50, -100, -150), FVector(50, 100, 150));
}

// Called when the game starts or when spawned
void ACDebugDrawer::BeginPlay()
{
	Super::BeginPlay();
	
    for (int32 i = 0; i < sizeof(Offsets) / sizeof(*Offsets); i++)
    {
        Locations[i] = GetActorLocation() + Offsets[i];
    }
}

// Called every frame
void ACDebugDrawer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DrawDebugSolidBox(GetWorld(), Locations[0] + Box.GetCenter(), Box.GetExtent(), FColor::Red);
    DrawDebugPoint(GetWorld(), Locations[1], 100, FColor::Green);
    DrawDebugSphere(GetWorld(), Locations[2], 100, 30, FColor::Blue);
    DrawDebugCircle(GetWorld(), Locations[3], 100, 50, FColor::Cyan);
    DrawDebugLine(GetWorld(), Locations[2], Locations[3], FColor::Magenta);

    FVector Location = Locations[1] + FVector(0, FMath::Sin(GetWorld()->GetTimeSeconds()), 1) * 500;

    DrawDebugCapsule(GetWorld(), Location, 200, 50, FQuat::Identity, FColor::Yellow);
    DrawDebugDirectionalArrow(GetWorld(), Locations[3], Location, 250, FColor::Black);
}

