#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "CParkourComponent.generated.h"

UENUM(BlueprintType)
enum class EParkourType : uint8
{
	None,
	Climb,
	Fall,
	Slide,
	Normal,
	Short,
	Wall,
	Max
};

UENUM(BlueprintType)
enum class EArrowType : uint8
{
	Center,
	Ceil,
	Floor,
	Left,
	Right,
	Land,
	Max
};

USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EParkourType Type;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
		float PlayRate = 1.0f;

	UPROPERTY(EditAnywhere)
		FName Section;

	UPROPERTY(EditAnywhere)
		float DistMin;

	UPROPERTY(EditAnywhere)
		float DistMax;

	UPROPERTY(EditAnywhere)
		float Extent;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GPC_10_CPP_API UCParkourComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCParkourComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BeginParkour();
	void EndParkour();

private:
	void TraceArrow(EArrowType Type);
	void TraceCenter();
	void TraceCeil();
	void TraceFloor();
	void TraceSide();
	void TraceLand();

	bool CheckObstacles();
	bool CheckClimb();
	bool CheckFall();
	bool CheckSlide();
	bool CheckOthers(EParkourType Type, FParkourData& Data);

	void BeginClimb();
	void BeginFall();
	void BeginSlide();
	void BeginOthers(EParkourType Type, FParkourData& Data);

	void EndClimb();
	void EndFall();
	void EndSlide();
	void EndOthers();

private:
	UPROPERTY(EditAnywhere)
		class UDataTable* DataTable;

	TMap<EParkourType, TArray<FParkourData>> DataMap;

	class UArrowComponent* Arrows[int32(EArrowType::Max)];

	FHitResult Results[int32(EArrowType::Max)];

	float TraceDistance   = 500;
	float AcceptableAngle = 30;

	AActor* HitObtacle;
	FVector HitObtacleExtent;
	float   HitDistance;
	float   ToFrontYaw;

	bool bFalling;

	EParkourType ParkourType = EParkourType::None;
};
