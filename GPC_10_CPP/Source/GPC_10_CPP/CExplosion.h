#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CExplosion.generated.h"

UCLASS()
class GPC_10_CPP_API ACExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	ACExplosion();

protected:
	virtual void BeginPlay() override;

private:
    class UParticleSystem* Particle;

private:
    UFUNCTION()
        void OnExplosion();
};
