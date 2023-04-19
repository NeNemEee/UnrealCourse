// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "FPSCharacterAnimation.h"

AFPSPlayer::AFPSPlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = { 0, 50, 100 };
		
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(80);

	ZoomTimeline = CreateDefaultSubobject<UTimelineComponent>("ZoomTimeline");

	BlendTimeOnZoomIn = 0.125f;
}

void AFPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	TargetArmLength = SpringArm->TargetArmLength;
	SocketOffset = SpringArm->SocketOffset;
	FieldOfView = Camera->FieldOfView;

	if (BlendCurveOnZoomIn != nullptr)
	{
		FOnTimelineFloat OnZoom;
		OnZoom.BindDynamic(this, &ThisClass::Zoom);
		ZoomTimeline->AddInterpFloat(BlendCurveOnZoomIn, OnZoom);
	}

	ZoomTimeline->SetPlayRate(1 / BlendTimeOnZoomIn);
}

void AFPSPlayer::BeginActionB()
{
	ZoomTimeline->Play();

	Cast<IFPSCharacterAnimationInterface>(GetMesh()->GetAnimInstance())->SetAiming(true);
}

void AFPSPlayer::EndActionB()
{
	ZoomTimeline->Reverse();

	Cast<IFPSCharacterAnimationInterface>(GetMesh()->GetAnimInstance())->SetAiming(false);
}

void AFPSPlayer::Zoom(float const Alpha)
{
	SpringArm->TargetArmLength = FMath::Lerp(TargetArmLength, TargetArmLengthOnZoomIn, Alpha);
	SpringArm->SocketOffset = FMath::Lerp(SocketOffset, SocketOffsetOnZoomIn, Alpha);

	Camera->SetFieldOfView(FMath::Lerp(FieldOfView, FieldOfViewOnZoomIn, Alpha));
}