// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

UCLASS()
class GPC_10_FPS_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void SetupInputComponent() override;

private:
	void MoveFB(float const Value);
	void MoveLR(float const Value);
	void LookLR(float const Value);
	void LookUD(float const Value);

	void Crouch();
	void LieProne();
	
	void ActionAOnPressed();
	void ActionBOnPressed();
	void ActionCOnPressed();
	
	void ActionAOnReleased();
	void ActionBOnReleased();
	void ActionCOnReleased();
};