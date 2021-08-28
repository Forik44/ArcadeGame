// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PlayerPawnCPP.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABonus::ABonus()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("BonusCollision"));
	SetRootComponent(Collision);

	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Collision->SetSphereRadius(50);

}

void ABonus::BonusCollected_Implementation()
{
	if (CollectParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), CollectParticle, GetActorTransform(), true);
	}
	Destroy();
}

void ABonus::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor)
	{
		return;
	}
	if (!Cast<APlayerPawnCPP>(OtherActor))
	{
		return;
	}

	BonusCollected();

}

void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -200.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}



