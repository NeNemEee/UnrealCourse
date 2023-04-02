#include "CBoxCollisionActor.h"
#include "Components/BoxComponent.h"

ACBoxCollisionActor::ACBoxCollisionActor()
{
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

    Box->SetRelativeScale3D(FVector(3));
    Box->bHiddenInGame = false;
}

