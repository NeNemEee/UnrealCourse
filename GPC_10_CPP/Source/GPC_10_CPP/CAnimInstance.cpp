#include "CAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Logger.h"

//#define DEBUG_LEG_IK

void UCAnimInstance::NativeBeginPlay()
{
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    
    if (APawn*const Owner = TryGetPawnOwner())
    {
        Speed = Owner->GetVelocity().Size2D();

		float    DistanceL;
		FRotator RotatorL;

		TraceForIK(BoneL, DistanceL, RotatorL);

		float    DistanceR;
		FRotator RotatorR;

		TraceForIK(BoneR, DistanceR, RotatorR);

		float DistanceP = FMath::Min(DistanceL, DistanceR);

		TranslationP.Z = FMath::FInterpTo(TranslationP.Z, DistanceP, DeltaSeconds, InterpSpeed);
		TranslationL.Z = FMath::FInterpTo(TranslationL.Z, DistanceL - DistanceP, DeltaSeconds, InterpSpeed);
		TranslationR.Z = FMath::FInterpTo(TranslationR.Z, DistanceR - DistanceP, DeltaSeconds, InterpSpeed);

		RotationL = FMath::RInterpTo(RotationL, RotatorL, DeltaSeconds, InterpSpeed);
		RotationR = FMath::RInterpTo(RotationR, RotatorR, DeltaSeconds, InterpSpeed);

#if defined DEBUG_LEG_IK
		Logger::Print(TranslationP, 0);
		Logger::Print(TranslationL, 1);
		Logger::Print(TranslationR, 2);
		Logger::Print(RotationL,    3);
		Logger::Print(RotationR,    4);
#endif
	}
}

void UCAnimInstance::Function2_Implementation()
{
    UE_LOG(LogTemp, Log, TEXT("Function"));
}

void UCAnimInstance::TraceForIK(FName Name, float& Distance, FRotator& Rotator)
{
    FVector Target = GetOwningComponent()->GetSocketLocation(Name);
    FVector Root   = GetOwningComponent()->GetSocketLocation(TEXT("Root"));
    FVector Actor  = TryGetPawnOwner()->GetActorLocation();

    FVector Start = FVector(Target.X, Target.Y, Actor.Z);
    FVector End   = FVector(Target.X, Target.Y, Root.Z - TraceDistance);
    
	FHitResult Result;

	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		ETraceTypeQuery::TraceTypeQuery1,
		true,
		{ TryGetPawnOwner() },
		EDrawDebugTrace::Type::ForOneFrame,
		Result,
		true
	);

	Distance = 0;
	Rotator  = FRotator::ZeroRotator;

	if (Result.bBlockingHit == true)
	{
		Distance = Result.Location.Z - Result.TraceEnd.Z - TraceDistance;

		float Roll  = +UKismetMathLibrary::DegAtan2(Result.Normal.Y, Result.Normal.Z);
		float Pitch = -UKismetMathLibrary::DegAtan2(Result.Normal.X, Result.Normal.Z);

		Rotator = FRotator(Pitch, 0, Roll);
	}
}