#include "CPointLight.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CDelegate.h"

ACPointLight::ACPointLight()
{
	PrimaryActorTick.bCanEverTick = true;

    Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));

    Light->SetLightColor(FLinearColor::Red);
    Light->SetIntensity(1e6f);
    Light->SetAttenuationRadius(200);
}

void ACPointLight::BeginPlay()
{
	Super::BeginPlay();
	
    OffLight();

    TArray<AActor*> actors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACDelegate::StaticClass(), actors);

    if (0 < actors.Num())
    {
        ACDelegate* trigger = Cast<ACDelegate>(actors[0]);

        trigger->OnTriggerBeginOverlap.BindLambda
        (
            [this]()
            {
                Light->SetVisibility(true);
            }
        );

        trigger->OnTriggerEndOverlap.BindUFunction(this, "OffLight");
    }
}

void ACPointLight::OffLight()
{
    Light->SetVisibility(false);
}