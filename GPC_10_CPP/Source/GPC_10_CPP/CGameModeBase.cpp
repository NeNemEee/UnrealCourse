// Copyright Epic Games, Inc. All Rights Reserved.


#include "CGameModeBase.h"
#include "CPlayerController.h"
#include "CPlayer.h"

ACGameModeBase::ACGameModeBase()
{
    PlayerControllerClass = ACPlayerController::StaticClass();
    DefaultPawnClass = ConstructorHelpers::FClassFinder<APawn>(TEXT("Blueprint'/Game/MyCPlayer.MyCPlayer_C'")).Class;
}