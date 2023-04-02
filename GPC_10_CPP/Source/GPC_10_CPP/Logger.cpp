// Fill out your copyright notice in the Description page of Project Settings.

#include "Logger.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(GPC, Display, All)

int32  const Logger::DefaultKey = INDEX_NONE;
float  const Logger::DefaultDuration = 10.0f;
FColor const Logger::DefaultColor = FColor::Red;

void Logger::Log(int32 const& Data)
{
    UE_LOG(GPC, Display, TEXT("%i"), Data);
}

void Logger::Log(float const& Data)
{
    UE_LOG(GPC, Display, TEXT("%f"), Data);
}

void Logger::Log(FString const& Data)
{
    UE_LOG(GPC, Display, TEXT("%s"), *Data);
}

void Logger::Log(FVector const& Data)
{
    UE_LOG(GPC, Display, TEXT("%s"), *Data.ToString());
}

void Logger::Log(FRotator const& Data)
{
    UE_LOG(GPC, Display, TEXT("%s"), *Data.ToString());
}

void Logger::Print(int32 const& Data, int32 const Key, float const Duration, FColor const Color)
{
    GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::FromInt(Data));
}

void Logger::Print(float const& Data, int32 const Key, float const Duration, FColor const Color)
{
    GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::SanitizeFloat(Data));
}

void Logger::Print(FString const& Data, int32 const Key, float const Duration, FColor const Color)
{
    GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data);
}

void Logger::Print(FVector const& Data, int32 const Key, float const Duration, FColor const Color)
{
    GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data.ToString());
}

void Logger::Print(FRotator const& Data, int32 const Key, float const Duration, FColor const Color)
{
    GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Data.ToString());
}

