#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPointLight.generated.h"

UCLASS()
class GPC_10_CPP_API ACPointLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPointLight();

protected:
	virtual void BeginPlay() override;

private:
    UFUNCTION()
        void OffLight();

private:
    class UPointLightComponent* Light;
};