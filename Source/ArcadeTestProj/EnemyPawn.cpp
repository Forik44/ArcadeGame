// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeTestProjGameModeBase.h"
#include "Engine/World.h"
// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollition"));
	SetRootComponent(PawnCollision);
	PawnCollision->SetCollisionProfileName("Pawn");

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(GetRootComponent());
	PawnMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent")); 
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	Random.GenerateNewSeed();
	HealthComponent->OnHealthEnded.AddDynamic(this, &AEnemyPawn::KillPawn);
	OnActorBeginOverlap.AddDynamic(this, &AEnemyPawn::OnEnemyOverlap);
}

void AEnemyPawn::KillPawn()
{
	AArcadeTestProjGameModeBase* Gamemode = Cast<AArcadeTestProjGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode)
	{
		Gamemode->AddPoints(DestroyPoints);
	}
	SpawnBonuses();

	DestroyPawn();
}

void AEnemyPawn::DestroyPawn()
{
	if (DestroyParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	}
	Destroy();
}

void AEnemyPawn::OnEnemyOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(this, 0))
	{
		return; 
	}
	if (!OtherActor->CanBeDamaged())
	{
		return;
	}

	UGameplayStatics::ApplyDamage(OtherActor, 100.f, GetController(), this, UDamageType::StaticClass());

	DestroyPawn(); 
}

void AEnemyPawn::SpawnBonuses()
{
	FActorSpawnParameters SpawnParametrs;
	SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Random.GenerateNewSeed();
	bool IsBonusSpawned = true;
	for (auto Bonus : PossibleBonuses)
	{
		if (Random.RandRange(0.f, 100.f) < Bonus.Chance && !IsBonusSpawned)
		{
			GetWorld()->SpawnActor<ABonus>(Bonus.BonusClass, GetActorLocation(), FRotator(0,0,0), SpawnParametrs);
			IsBonusSpawned = false;
		}
	}
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float WorldMoveOffset = -100.f * DeltaTime;
	AddActorWorldOffset(FVector(WorldMoveOffset, 0.f, 0.f));

}


void AEnemyPawn::IgnoreProjectile(AShootProjectile* Projectile, AActor* PawnOwner)
{
	if (this == PawnOwner)
	{
		PawnCollision->IgnoreActorWhenMoving(Projectile, true);
	}
}

