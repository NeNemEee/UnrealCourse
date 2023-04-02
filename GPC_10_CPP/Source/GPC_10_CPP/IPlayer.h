// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayer.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIPlayer : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GPC_10_CPP_API IIPlayer
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:
	virtual void Parkour() abstract;

	UFUNCTION(BlueprintNativeEvent)
		void Test();
};