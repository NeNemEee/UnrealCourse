// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CParkourComponent.h"

//#define CreateSubobject(Type, Variable) (Variable = CreateDefaultSubobject<Type>(#Variable))
//#define DefineClass(Typename) class A##Typename { int Variable; }

ACPlayer::ACPlayer()
{
	//DefineClass(Test);

    ConstructorHelpers::FObjectFinder<USkeletalMesh> finder(TEXT("SkeletalMesh'/Game/Meshes/Mannequin/SK_Mannequin.SK_Mannequin'"));

    if (finder.Succeeded() == true)
    {
        GetMesh()->SetSkeletalMesh(finder.Object);
    }

	//CreateSubobject(USpringArmComponent, SpringArm);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->TargetOffset = FVector(0, 0, 75);

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);

	ParkourComponent = CreateDefaultSubobject<UCParkourComponent>("ParkourComponent");
}

void ACPlayer::Parkour()
{
	ParkourComponent->BeginParkour();
}