#include "CMultiTrigger.h"
#include "Kismet/KismetMathLibrary.h"

void ACMultiTrigger::BeginPlay()
{
	Super::BeginPlay();
	
    OnActorBeginOverlap.AddDynamic(this, &ACMultiTrigger::OnBeginOverlap);
}

void ACMultiTrigger::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    if (OnMulticastBeginOverlap.IsBound() == true)
    {
        int32 index = UKismetMathLibrary::RandomIntegerInRange(0, 2);
        
        FLinearColor color
        {
            UKismetMathLibrary::RandomFloatInRange(0, 1),
            UKismetMathLibrary::RandomFloatInRange(0, 1),
            UKismetMathLibrary::RandomFloatInRange(0, 1),
            1
        };

        OnMulticastBeginOverlap.Broadcast(index, color);
    }
}