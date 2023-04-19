// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayerController.h"
#include "FPSControlledOneInterface.h"

void AFPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->bBlockInput = true;
	
	InputComponent->BindAxis("MoveFB", this, &ThisClass::MoveFB);
	InputComponent->BindAxis("MoveLR", this, &ThisClass::MoveLR);
	InputComponent->BindAxis("LookLR", this, &ThisClass::LookLR);
	InputComponent->BindAxis("LookUD", this, &ThisClass::LookUD);

	InputComponent->BindAction("Crouch",   EInputEvent::IE_Pressed, this, &ThisClass::Crouch);
	InputComponent->BindAction("LieProne", EInputEvent::IE_Pressed, this, &ThisClass::LieProne);

	InputComponent->BindAction("ActionA", EInputEvent::IE_Pressed, this, &ThisClass::ActionAOnPressed);
	InputComponent->BindAction("ActionB", EInputEvent::IE_Pressed, this, &ThisClass::ActionBOnPressed);
	InputComponent->BindAction("ActionC", EInputEvent::IE_Pressed, this, &ThisClass::ActionCOnPressed);
	
	InputComponent->BindAction("ActionA", EInputEvent::IE_Released, this, &ThisClass::ActionAOnReleased);
	InputComponent->BindAction("ActionB", EInputEvent::IE_Released, this, &ThisClass::ActionBOnReleased);
	InputComponent->BindAction("ActionC", EInputEvent::IE_Released, this, &ThisClass::ActionCOnReleased);
}

void AFPSPlayerController::MoveFB(float const Value)
{
	if (APawn* const ControlledPawn = GetPawn())
	{
		FVector const Direction = FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetForwardVector();

		ControlledPawn->AddMovementInput(Direction, Value);
	}
}

void AFPSPlayerController::MoveLR(float const Value)
{
	if (APawn* const ControlledPawn = GetPawn())
	{
		FVector const Direction = FRotator(0, GetControlRotation().Yaw, 0).Quaternion().GetRightVector();

		ControlledPawn->AddMovementInput(Direction, Value);
	}
}

void AFPSPlayerController::LookLR(float const Value)
{
	AddYawInput(Value);
}

void AFPSPlayerController::LookUD(float const Value)
{
	AddPitchInput(Value);
}

void AFPSPlayerController::Crouch()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->Crouch();
	}
}

void AFPSPlayerController::LieProne()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->LieProne();
	}
}

void AFPSPlayerController::ActionAOnPressed()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->BeginActionA();
	}
}

void AFPSPlayerController::ActionBOnPressed()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->BeginActionB();
	}
}

void AFPSPlayerController::ActionCOnPressed()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->BeginActionC();
	}
}

void AFPSPlayerController::ActionAOnReleased()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->EndActionA();
	}
}

void AFPSPlayerController::ActionBOnReleased()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->EndActionB();
	}
}

void AFPSPlayerController::ActionCOnReleased()
{
	if (auto* const ControlledOne = Cast<IFPSControlledOneInterface>(GetPawn()))
	{
		ControlledOne->EndActionC();
	}
}