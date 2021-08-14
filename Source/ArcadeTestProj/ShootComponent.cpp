#include "ShootComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawnCPP.h"
#include "EnemyPawn.h"


UShootComponent::UShootComponent()
{
	ShootPeriod = 1.f;

}

void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	StartShooting();

}

void UShootComponent::Shoot()
{
	

	for (FShootInfo ShootInfo : ShootInfos)
	{
		FActorSpawnParameters SpawnParametrs;
		SpawnParametrs.Owner = GetOwner();
		SpawnParametrs.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorRotation().UnrotateVector(ShootInfo.Offset);
		GetOwner()->GetActorRotation().UnrotateVector(ShootInfo.Offset);
		FRotator SpawnRotation = GetOwner()->GetActorRotation();
		SpawnRotation.Add(0.f, ShootInfo.Angle, 0.f);


		AShootProjectile* Projectile = GetWorld()->SpawnActor<AShootProjectile>(ShootInfo.ProjectileClass, SpawnLocation, SpawnRotation, SpawnParametrs);
		if (UGameplayStatics::GetPlayerPawn(this, 0) == GetOwner())
		{
			APlayerPawnCPP* Player = Cast<APlayerPawnCPP>(GetOwner());
			Player->IgnoreProjectile(Projectile);
		}
		else
		{
			AEnemyPawn* Enemy = Cast<AEnemyPawn>(GetOwner());
			Enemy->IgnoreProjectile(Projectile, GetOwner());
		}

		
		if (Projectile)
		{
			Projectile->Damage = ShootInfo.Damage;
		}
	}
}

void UShootComponent::StartShooting()
{
	GetWorld()->GetTimerManager().SetTimer(ShootingTimer, this, &UShootComponent::Shoot, ShootPeriod, true, ShootPeriod);
}

void UShootComponent::StopShooting()
{
	GetWorld()->GetTimerManager().ClearTimer(ShootingTimer);
}

