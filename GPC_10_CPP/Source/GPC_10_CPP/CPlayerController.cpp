// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"
#include "IPlayer.h"

ACPlayerController::ACPlayerController()
{
}

void ACPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->bBlockInput = true;

    InputComponent->BindAxis("MoveFB",  this, &ThisClass::MoveFB);
    InputComponent->BindAxis("MoveLR",  this, &ThisClass::MoveLR);
    InputComponent->BindAxis("LookLR",  this, &ThisClass::LookLR);
    InputComponent->BindAxis("LookUD",  this, &ThisClass::LookUD);
    
	InputComponent->BindAction("Parkour", IE_Pressed , this, &ThisClass::Parkour);
}

void ACPlayerController::MoveFB(float const Value)
{
    GetPawn()->AddMovementInput(FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetForwardVector(), Value);
}

void ACPlayerController::MoveLR(float const Value)
{
    GetPawn()->AddMovementInput(FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetRightVector(), Value);
}

void ACPlayerController::LookLR(float const Value)
{
    AddYawInput(Value);
}

void ACPlayerController::LookUD(float const Value)
{
    AddPitchInput(Value);
}

void ACPlayerController::Parkour()
{
	if (IIPlayer* const IPlayer = Cast<IIPlayer>(GetPawn()))
	{
		IPlayer->Parkour();

		//IIPlayer::Execute_Test(GetPawn());
	}
}