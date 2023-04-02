#include "CCubes.h"
#include "Kismet/GameplayStatics.h"
#include "CMultiTrigger.h"

ACCubes::ACCubes()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    SetRootComponent(Root);

    ConstructorHelpers::FObjectFinder<UStaticMesh> finder(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

    if (finder.Succeeded() == true)
    {
        for (int32 i = 0; i < sizeof(Cubes) / sizeof(*Cubes); ++i)
        {
            Cubes[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName("Cube" + FString::FromInt(i)));

            Cubes[i]->SetupAttachment(Root);
            Cubes[i]->SetStaticMesh(finder.Object);
            Cubes[i]->SetRelativeLocation(FVector(0, (i - 1) * 150, 0));
        }
    }
}

void ACCubes::BeginPlay()
{
	Super::BeginPlay();

    FString Reference = TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'");

    UMaterial* Material = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), this, *Reference));

    for (int32 i = 0; i < sizeof(Cubes) / sizeof(*Cubes); ++i)
    {
        Cubes[i]->SetMaterial(0, UMaterialInstanceDynamic::Create(Material, this));
    }
	
    TArray<AActor*> actors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACMultiTrigger::StaticClass(), actors);

    if (0 < actors.Num())
    {
        ACMultiTrigger* trigger = Cast<ACMultiTrigger>(actors[0]);

        trigger->OnMulticastBeginOverlap.AddUFunction(this, "OnBroadcast");
    }
}

void ACCubes::OnBroadcast(int32 Index, FLinearColor Color)
{
    for (int32 i = 0; i < sizeof(Cubes) / sizeof(*Cubes); ++i)
    {
        Cubes[i]->SetSimulatePhysics(false);
        Cubes[i]->SetWorldLocation(GetActorLocation() + FVector(0, (i - 1) * 150, 0));
    }

    Cubes[Index]->SetSimulatePhysics(true);
    
    auto MID = Cast<UMaterialInstanceDynamic>(Cubes[Index]->GetMaterial(0));

    MID->SetVectorParameterValue(TEXT("Color"), Color);
}