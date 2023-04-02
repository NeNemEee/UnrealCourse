// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACCharacter::ACCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bUseSeparateBrakingFriction = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bOrientRotationToMovement = true;

    GetMesh()->SetRelativeLocation(FVector(0, 0, -85));
    GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
    
    ConstructorHelpers::FClassFinder<UAnimInstance> finder(TEXT("AnimBlueprint'/Game/ABP_Character.ABP_Character_C'"));
    
    if (finder.Succeeded() == true)
    {
        GetMesh()->SetAnimInstanceClass(finder.Class);
    }
}

// Called when the game starts or when spawned
void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

