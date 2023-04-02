#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCubes.generated.h"

UCLASS()
class GPC_10_CPP_API ACCubes : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCubes();

protected:
	virtual void BeginPlay() override;

private:
    UFUNCTION()
        void OnBroadcast(int32 Index, FLinearColor Color);

private:
    class USceneComponent* Root;
    class UStaticMeshComponent* Cubes[3];
};