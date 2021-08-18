// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeTestProjGameModeBase.h"
#include "PlayerPawnCPP.h"

AArcadeTestProjGameModeBase::AArcadeTestProjGameModeBase()
	:
	PlayerRecoverTime(2),
	CurrentShootLevel(-1)
{
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	HealtsComponents = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeTestProjGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealtsComponents->OnHealthsEnded.AddDynamic(this, &AArcadeTestProjGameModeBase::EndGame);

	PlayerPawn = Cast<APlayerPawnCPP>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn)
	{
		return;
	}

	ChangeShootLevel(true);

	PlayerPawn->PawnDamaged.AddDynamic(this, &AArcadeTestProjGameModeBase::ExplodePawn);
}

void AArcadeTestProjGameModeBase::ExplodePawn_Implementation()
{
	PlayerPawn->ExplodePawn();

	HealtsComponents->ChangeHealths(-1);

	if (!IsGameOver)
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer, this, &AArcadeTestProjGameModeBase::RecoverPawn, PlayerRecoverTime, false);
	}
}

void AArcadeTestProjGameModeBase::RecoverPawn_Implementation()
{
	PlayerPawn->RecoverPawn();
}

void AArcadeTestProjGameModeBase::EndGame()
{
	IsGameOver = true;

	EnemySpawnComponent->SetActive(false);

	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	SetPause(UGameplayStatics::GetPlayerController(this, 0), false); 
}

void AArcadeTestProjGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
}

bool AArcadeTestProjGameModeBase::ChangeShootLevel(bool Up)
{
	PlayerPawn = Cast<APlayerPawnCPP>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (!PlayerPawn)
	{
		return false;
	}

	int NewLevel = FMath::Clamp(CurrentShootLevel + (Up ? 1 : -1), 0, ShootInfoLevels.Num() - 1);

	if (NewLevel == CurrentShootLevel)
	{
		return false;
	}

	CurrentShootLevel = NewLevel;

	PlayerPawn->ShootComponent->ShootInfos = ShootInfoLevels[CurrentShootLevel].ShootInfos;
	PlayerPawn->ShootComponent->ShootPeriod = ShootInfoLevels[CurrentShootLevel].ShootPeriod;

	return true;
} 

