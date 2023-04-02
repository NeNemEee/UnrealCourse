#include "CExplosion.h"
#include "Particles/ParticleSystem.h"
#include "CEvent.h"
#include "Kismet/GameplayStatics.h"

ACExplosion::ACExplosion()
{
    ConstructorHelpers::FObjectFinder<UParticleSystem> finder(TEXT("ParticleSystem'/Game/Particles/P_Hit_Fire.P_Hit_Fire'"));

    if (finder.Succeeded() == true)
    {
        Particle = finder.Object;
    }
}

void ACExplosion::BeginPlay()
{
	Super::BeginPlay();
	
    ACEvent* trigger;

    TArray<AActor*> actors;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACEvent::StaticClass(), actors);

    if (0 < actors.Num())
    {
        trigger = Cast<ACEvent>(actors[0]);

        trigger->OnExplosion.AddUFunction(this, "OnExplosion");
    }
}

void ACExplosion::OnExplosion()
{
    UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
}

