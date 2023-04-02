#pragma once

#include "CoreMinimal.h"
#include "CBoxCollisionActor.h"
#include "CDelegate.generated.h"

//FUNC_DECLARE_DELEGATE(��������Ʈ��, ��ȯ ����, ���� ����, ...)
FUNC_DECLARE_DELEGATE(FTest, void)

DECLARE_DELEGATE(FTriggerOverlap)

UCLASS()
class GPC_10_CPP_API ACDelegate : public ACBoxCollisionActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
    FTriggerOverlap OnTriggerBeginOverlap;
    FTriggerOverlap OnTriggerEndOverlap;

private:
    UFUNCTION()
        void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

    UFUNCTION()
        void OnEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
