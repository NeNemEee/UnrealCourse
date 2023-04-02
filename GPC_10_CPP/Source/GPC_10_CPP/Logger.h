#pragma once

#include "CoreMinimal.h"

class GPC_10_CPP_API Logger
{
public:
    /*
        Log
        Warning
        Error
        Display
        Fatal
    */

    static void Log(int32    const& Data);
    static void Log(float    const& Data);
    static void Log(FString  const& Data);
    static void Log(FVector  const& Data);
    static void Log(FRotator const& Data);

    static void Print(int32    const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
    static void Print(float    const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
    static void Print(FString  const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
    static void Print(FVector  const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);
    static void Print(FRotator const& Data, int32 const Key = DefaultKey, float const Duration = DefaultDuration, FColor const Color = DefaultColor);

private:
    static int32  const DefaultKey;
    static float  const DefaultDuration;
    static FColor const DefaultColor;
};
