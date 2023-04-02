// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

USTRUCT(BlueprintType)
struct FTest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int i;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int j;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        int k;
};

/**
 * 
 */
UCLASS()
class GPC_10_CPP_API UCAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    
protected:
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void Function();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void Function2();

    virtual void Function2_Implementation();

private:
    void TraceForIK(FName Name, float& Distance, FRotator& Rotator);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Movement")
        float Speed;

	UPROPERTY(BlueprintReadOnly, Category = "IK")
		FVector TranslationP;

    UPROPERTY(BlueprintReadOnly, Category = "IK")
        FVector TranslationL;

    UPROPERTY(BlueprintReadOnly, Category = "IK")
        FVector TranslationR;

    UPROPERTY(BlueprintReadOnly, Category = "IK")
        FRotator RotationL;

    UPROPERTY(BlueprintReadOnly, Category = "IK")
        FRotator RotationR;

    FName BoneL = "Foot_L";
    FName BoneR = "Foot_R";

    float TraceDistance = 50;
	float InterpSpeed = 50;
};
