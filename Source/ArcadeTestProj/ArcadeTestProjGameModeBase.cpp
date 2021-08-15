// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeTestProjGameModeBase.h"
#include "PlayerPawnCPP.h"

AArcadeTestProjGameModeBase::AArcadeTestProjGameModeBase()
	:
	PlayerRecoverTime(2)
{
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	HealtsComponents = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeTestProjGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealtsComponents->OnHealthsEnded.AddDynamic(this, &AArcadeTestProjGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawnCPP>(UGameplayStatics::GetPlayerPawn(this, 0));

	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadeTestProjGameModeBase::ExplodePawn);
}

void AArcadeTestProjGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealtsComponents->ChangeHealths(-1);

	GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeTestProjGameModeBase::RecoverPawn, PlayerRecoverTime, false);
}

void AArcadeTestProjGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AArcadeTestProjGameModeBase::EndGame()
{
	GameOver.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Game Over"));
}

