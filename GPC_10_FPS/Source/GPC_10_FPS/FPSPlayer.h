// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "FPSPlayer.generated.h"

UCLASS()
class GPC_10_FPS_API AFPSPlayer : public AFPSCharacter
{
	GENERATED_BODY()
	
public:
	AFPSPlayer();

protected:
	void BeginPlay() override;

private:
	void BeginActionB() override;
	void EndActionB() override;

	UFUNCTION()
		void Zoom(float const Alpha);

private:
	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
		class UTimelineComponent* ZoomTimeline;

	UPROPERTY(EditDefaultsOnly)
		class UCurveFloat* BlendCurveOnZoomIn;

	UPROPERTY(EditDefaultsOnly)
		float BlendTimeOnZoomIn;

	UPROPERTY(EditDefaultsOnly)
		float FieldOfViewOnZoomIn;

	UPROPERTY(EditDefaultsOnly)
		float TargetArmLengthOnZoomIn;

	UPROPERTY(EditDefaultsOnly)
		FVector SocketOffsetOnZoomIn;

	float FieldOfView;
	float TargetArmLength;
	FVector SocketOffset;
};