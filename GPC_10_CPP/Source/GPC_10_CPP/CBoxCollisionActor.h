#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBoxCollisionActor.generated.h"

UCLASS()
class GPC_10_CPP_API ACBoxCollisionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBoxCollisionActor();

private:
    class UBoxComponent* Box;
};
