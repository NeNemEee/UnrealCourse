#include "CParkourComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Logger.h"



UCParkourComponent::UCParkourComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	for (int32 i = 0; i < int32(EArrowType::Max); ++i)
	{
		Arrows[i] = CreateDefaultSubobject<UArrowComponent>(FName("Arrow" + FString::FromInt(i)));
	}

	Arrows[int32(EArrowType::Ceil)]->SetRelativeLocation(FVector(0, 0, 80));
	Arrows[int32(EArrowType::Floor)]->SetRelativeLocation(FVector(0, 0, -80));
	Arrows[int32(EArrowType::Left)]->SetRelativeLocation(FVector(0, 30, 0));
	Arrows[int32(EArrowType::Right)]->SetRelativeLocation(FVector(0, -30, 0));
	Arrows[int32(EArrowType::Land)]->SetRelativeLocation(FVector(200, 0, 100));
	Arrows[int32(EArrowType::Land)]->SetRelativeRotation(FRotator(-90, 0, 0));

	

}

/*
CallbackProxy
- BlendingOutDelegate(UAnimMontage*, bool) (OnMontageBlendingOut 가 갖고있음<animinstance 의 OnMontageBlendingOut>)
- OnMontageBlendingOut(UAnimMontage*, bool) {OnBlendOut.BroadCast(NAME_None);}(BlendingOutDelegate 가 갖고 있음)
- OnBlendOut(FName)(OnMontageBlendingOut에게 호출당함)

Animainstance			
- OnMontageBlendingOut(UAnimMontage*, bool)

UserFunction(FName){} (OnBlendOut 에 바인된 함수)
*/

void UCParkourComponent::BeginPlay()
{
	Super::BeginPlay();

	Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance()->OnMontageBlendingOut.AddDynamic(this, &ThisClass::EndParkour);

	for (int32 i = 0; i < int32(EArrowType::Max); ++i)
	{
		FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, true);

		Arrows[i]->AttachToComponent(GetOwner()->GetRootComponent(), Rules);
	}

	if (DataTable != nullptr)
	{
		TArray<FParkourData*> Rows;

		DataTable->GetAllRows("", Rows);

		for (int32 Key = int32(EParkourType::Climb); Key < int32(EParkourType::Max); ++Key)
		{
			TArray<FParkourData> Value;

			for (auto& Row : Rows)
			{
				if (Row->Type == EParkourType(Key))
				{
					Value.Add(*Row);
				}

				DataMap.Add(EParkourType(Key), Value);
			}
		}
	}
}

void UCParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceCenter();

	if (HitObtacle != nullptr)
	{
		TraceCeil();
		TraceFloor();
		TraceSide();
	}

	TraceLand();
}

void UCParkourComponent::BeginParkour()
{
	if (ParkourType == EParkourType::None)
	{
		if (CheckObstacles() == true)
		{
			if (CheckClimb() == true)
			{
				BeginClimb();
			}
			else if (CheckSlide() == true)
			{
				BeginSlide();
			}
			else
			{
				if (Results[int32(EArrowType::Ceil)].bBlockingHit == false)
				{
					float Dot = FVector::DotProduct(Results[int32(EArrowType::Center)].Normal, HitObtacle->GetActorForwardVector());

					if (FMath::IsNearlyZero(Dot, 0.1f) == true)
					{
						for (int32 i = int32(EParkourType::Normal); i < int32(EParkourType::Max); ++i)
						{
							FParkourData Data;

							if (CheckOthers(EParkourType(i), Data) == true)
							{
								BeginOthers(EParkourType(i), Data);
							}
						}
					}
				}
			}
		}
		else if (CheckFall() == true)
		{
			BeginFall();
		}
	}
}

void UCParkourComponent::EndParkour(UAnimMontage* Montage, bool bInterrupted)
{
	switch (ParkourType)
	{
		case EParkourType::Climb:	EndClimb();	 break;
		case EParkourType::Fall:	EndFall();	 break;
		case EParkourType::Slide:	EndSlide();	 break;
		case EParkourType::Normal:
		case EParkourType::Short:
		case EParkourType::Wall:	EndOthers(); break;
	}

	ParkourType = EParkourType::None;
}

void UCParkourComponent::TraceArrow(EArrowType Type)
{
	UArrowComponent* Arrow     = Arrows[int32(Type)];
	FTransform       Transform = Arrow->GetComponentToWorld();
	FVector          Start     = Transform.GetLocation();
	FVector          End       = Start + GetOwner()->GetActorForwardVector() * TraceDistance;

	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		Start,
		End,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{ GetOwner() },
		EDrawDebugTrace::Type::ForOneFrame,
		Results[int32(Type)],
		true
	);
}

void UCParkourComponent::TraceCenter()
{
	HitObtacle       = nullptr;
	HitObtacleExtent = FVector::ZeroVector;
	HitDistance      = 0;
	ToFrontYaw       = 0;

	TraceArrow(EArrowType::Center);

	FHitResult& Result = Results[int32(EArrowType::Center)];

	if (Result.bBlockingHit == true && Result.Actor != nullptr)
	{

		typedef UStaticMeshComponent MeshType;

		if (MeshType* Mesh = Cast<MeshType>(Result.Actor->GetComponentByClass(MeshType::StaticClass())))
		{
			HitObtacle = Result.GetActor();

			FVector Min, Max;

			Mesh->GetLocalBounds(Min, Max);

			HitObtacleExtent = FVector(Max.X - Min.X, Max.Y - Min.Y, Max.Z - Min.Z) * HitObtacle->GetActorScale3D();
			HitDistance      = Result.Distance;
			ToFrontYaw       = UKismetMathLibrary::MakeRotFromX(-Result.Normal).Yaw;
		}
	}
}

void UCParkourComponent::TraceCeil()
{
	TraceArrow(EArrowType::Ceil);
}

void UCParkourComponent::TraceFloor()
{
	TraceArrow(EArrowType::Floor);
}

void UCParkourComponent::TraceSide()
{
	TraceArrow(EArrowType::Left);
	TraceArrow(EArrowType::Right);
}

void UCParkourComponent::TraceLand()
{
	if (bFalling == false && Cast<APawn>(GetOwner())->GetMovementComponent()->IsFalling() == true)
	{
		bFalling = true;

		UArrowComponent* Arrow = Arrows[int32(EArrowType::Land)];
		FTransform Transform = Arrow->GetComponentToWorld();
		FVector Start = Transform.GetLocation();
		FVector End = Start + Transform.GetRotation().GetForwardVector() * DataMap[EParkourType::Fall][0].Extent;

		GetWorld()->LineTraceSingleByObjectType
		(
			Results[0],
			Start,
			End,
			FCollisionObjectQueryParams({ ObjectTypeQuery1, ObjectTypeQuery2 })
		);

		UKismetSystemLibrary::LineTraceSingle
		(
			GetWorld(),
			Start,
			End,
			TraceTypeQuery1,
			false,
			{ GetOwner() },
			EDrawDebugTrace::ForOneFrame,
			Results[int32(EArrowType::Land)],
			true
		);
	}
}

bool UCParkourComponent::CheckObstacles()
{
	bool Result = true;

	Result &= Results[int32(EArrowType::Center)].bBlockingHit;
	Result &= Results[int32(EArrowType::Left)].bBlockingHit;
	Result &= Results[int32(EArrowType::Right)].bBlockingHit;

	if (Result == true)
	{
		FVector Center = Results[int32(EArrowType::Center)].Normal;
		FVector Left   = Results[int32(EArrowType::Left)].Normal;
		FVector Right  = Results[int32(EArrowType::Right)].Normal;

		if (Center.Equals(Left) == false || Center.Equals(Right) == false)
		{
			return false;
		}

		FVector Start = Results[int32(EArrowType::Center)].Location;
		FVector End   = GetOwner()->GetActorLocation();

		float LookAtYaw = UKismetMathLibrary::FindLookAtRotation(Start, End).Yaw;
		float NormalYaw = UKismetMathLibrary::MakeRotFromX(Center).Yaw;

		if (abs(abs(LookAtYaw) - abs(NormalYaw)) <= AcceptableAngle)
		{
			return true;
		}
	}

	return false;
}

bool UCParkourComponent::CheckClimb()
{
	if (Results[int32(EArrowType::Ceil)].bBlockingHit == true)
	{
		TArray<FParkourData>& Data = DataMap[EParkourType::Climb];

		if (Data[0].DistMin <= HitDistance && HitDistance <= Data[0].DistMax)
		{
			if (FMath::IsNearlyEqual(Data[0].Extent, HitObtacleExtent.Z, 10) == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool UCParkourComponent::CheckFall()
{
	if (bFalling == true)
	{
		float Distance = Results[int32(EArrowType::Land)].Distance;

		TArray<FParkourData>& Data = DataMap[EParkourType::Fall];

		if (Data[0].DistMin <= Distance && Distance <= Data[0].DistMax)
		{
			return true;
		}
	}

	return false;
}

bool UCParkourComponent::CheckSlide()
{
	if (Results[int32(EArrowType::Floor)].bBlockingHit == false)
	{
		TArray<FParkourData>& Data = DataMap[EParkourType::Slide];

		if (Data[0].DistMin <= HitDistance && HitDistance <= Data[0].DistMax)
		{
			UArrowComponent* Arrow = Arrows[int32(EArrowType::Floor)];
			FVector          Start = Arrow->GetComponentToWorld().GetLocation() + FVector(0, 0, Data[0].Extent);
			FVector          End   = Start + GetOwner()->GetActorForwardVector().GetSafeNormal2D() * TraceDistance;

			bool Result = UKismetSystemLibrary::BoxTraceSingle
			(
				GetWorld(),
				Start,
				End,
				FVector(0, Data[0].Extent, Data[0].Extent),
				GetOwner()->GetActorRotation(),
				TraceTypeQuery1,
				false,
				{ GetOwner() },
				EDrawDebugTrace::ForDuration,
				Results[int32(EArrowType::Floor)],
				true
			);

			if (Result == false && 500 <= Cast<APawn>(GetOwner())->GetMovementComponent()->Velocity.Size())
			{
				return true;
			}
		}
	}

	return false;
}

bool UCParkourComponent::CheckOthers(EParkourType Type, FParkourData& Data)
{
	TArray<FParkourData>& DataArray = DataMap[Type];

	for (int32 i = 0; i < DataArray.Num(); ++i)
	{
		if (FMath::IsNearlyEqual(DataArray[i].Extent, HitObtacleExtent.Y, 10) == true)
		{
			if (HitDistance < DataArray[i].DistMin || DataArray[i].DistMax < HitDistance)
			{
				continue;
			}
			else
			{
				Data = DataArray[i];

				return true;
			}
		}
	}

	return false;
}

void UCParkourComponent::BeginClimb()
{
	ParkourType = EParkourType::Climb;

	ACharacter* Owner = Cast<ACharacter>(GetOwner());

	Owner->SetActorLocation(Results[int32(EArrowType::Center)].Location);
	Owner->SetActorRotation(FRotator(0, ToFrontYaw, 0));

	TArray<FParkourData>& Data = DataMap[EParkourType::Climb];

	Owner->PlayAnimMontage(Data[0].Montage, Data[0].PlayRate, Data[0].Section);
	Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UCParkourComponent::BeginFall()
{
}

void UCParkourComponent::BeginSlide()
{
	ParkourType = EParkourType::Slide;

	TArray<FParkourData>& Data = DataMap[ParkourType];

	Cast<ACharacter>(GetOwner())->PlayAnimMontage(Data[0].Montage, Data[0].PlayRate, Data[0].Section);

	(Target = HitObtacle)->SetActorEnableCollision(false);
}

void UCParkourComponent::BeginOthers(EParkourType Type, FParkourData & Data)
{
	ParkourType = Type;

	AActor* Owner = GetOwner();

	Owner->SetActorRotation(FRotator(0, ToFrontYaw, 0));

	Cast<ACharacter>(Owner)->PlayAnimMontage(Data.Montage, Data.PlayRate, Data.Section);

	Owner->SetActorEnableCollision(false);
}

void UCParkourComponent::EndClimb()
{
	Cast<ACharacter>(GetOwner())->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UCParkourComponent::EndFall()
{
}

void UCParkourComponent::EndSlide()
{
	Target->SetActorEnableCollision(true);
	Target = nullptr;
}

void UCParkourComponent::EndOthers()
{
	GetOwner()->SetActorEnableCollision(true);
}
