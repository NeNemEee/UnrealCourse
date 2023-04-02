#include "CEvent.h"

void ACEvent::BeginPlay()
{
	Super::BeginPlay();
	
    OnActorBeginOverlap.AddDynamic(this, &ACEvent::OnBeginOverlap);
}

void ACEvent::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OnExplosion.IsBound() == true)
    {
        OnExplosion.Broadcast();
    }
}