// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPSGun.h"
#include "FPSCharacterAnimationInterface.h"

AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSCharacter::Crouch()
{
	if (CharacterPose == EFPSCharacterPose::Crouching)
	{
		ACharacter::UnCrouch();

		CharacterPose = EFPSCharacterPose::Standing;
	}
	else
	{
		ACharacter::Crouch();

		CharacterPose = EFPSCharacterPose::Crouching;
	}

	Cast<IFPSCharacterAnimationInterface>(GetMesh()->GetAnimInstance())->SetCharacterPose(CharacterPose);
}

void AFPSCharacter::LieProne()
{
	if (CharacterPose == EFPSCharacterPose::Prone)
	{

		GetController()->SetIgnoreMoveInput(false);
		GetController()->SetIgnoreLookInput(false);

		CharacterPose = EFPSCharacterPose::Standing;
	}
	else
	{
		GetController()->SetIgnoreMoveInput(true);
		GetController()->SetIgnoreLookInput(true);

		CharacterPose = EFPSCharacterPose::Prone;
	}
	Cast<IFPSCharacterAnimationInterface>(GetMesh()->GetAnimInstance())->SetCharacterPose(CharacterPose);
}

void AFPSCharacter::BeginActionA()
{
	if (Weapon != nullptr)
	{
		Weapon->BeginActionA();
	}
}

void AFPSCharacter::BeginActionB()
{
	if (Weapon != nullptr)
	{
		Weapon->BeginActionB();
	}
}

void AFPSCharacter::BeginActionC()
{
	if (Weapon != nullptr)
	{
		Weapon->BeginActionC();
	}
}

void AFPSCharacter::EndActionA()
{
	if (Weapon != nullptr)
	{
		Weapon->EndActionA();
	}
}

void AFPSCharacter::EndActionB()
{
	if (Weapon != nullptr)
	{
		Weapon->EndActionB();
	}
}

void AFPSCharacter::EndActionC()
{
	if (Weapon != nullptr)
	{
		Weapon->EndActionC();
	}
}