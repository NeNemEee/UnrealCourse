#include "CDelegate.h"

void ACDelegate::BeginPlay()
{
	Super::BeginPlay();
	
    OnActorBeginOverlap.AddDynamic(this, &ACDelegate::OnBeginOverlap);
    OnActorEndOverlap.AddDynamic(this, &ACDelegate::OnEndOverlap);
}

void ACDelegate::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OnTriggerBeginOverlap.IsBound() == true)
    {
        OnTriggerBeginOverlap.Execute();
    }
}

void ACDelegate::OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OnTriggerEndOverlap.IsBound() == true)
    {
        OnTriggerEndOverlap.Execute();
    }
}