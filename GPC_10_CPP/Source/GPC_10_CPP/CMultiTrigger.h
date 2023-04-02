#pragma once

#include "CoreMinimal.h"
#include "CBoxCollisionActor.h"
#include "CMultiTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastBeginOverlap, int32, FLinearColor)

UCLASS()
class GPC_10_CPP_API ACMultiTrigger : public ACBoxCollisionActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
    FMulticastBeginOverlap OnMulticastBeginOverlap;

private:
    UFUNCTION()
        void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};