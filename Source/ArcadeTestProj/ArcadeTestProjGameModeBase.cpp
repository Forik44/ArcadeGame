// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeTestProjGameModeBase.h"
#include "PlayerPawnCPP.h"
#include "Save.h"

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

	if (!UGameplayStatics::DoesSaveGameExist(FString::FromInt(1), 0))
	{
		USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(USave::StaticClass());
		USave* Save = Cast<USave>(SaveGame);
		if (GamePoints > Save->RecordScore)
		{
			Save->RecordScore = GamePoints;
			UGameplayStatics::SaveGameToSlot(Save, FString::FromInt(1), 0);
		}
	}

	GameOver.Broadcast();

	UGameplayStatics::GetPlayerPawn(this, 0)->Destroy();

	SetPause(UGameplayStatics::GetPlayerController(this, 0)); 
}

void AArcadeTestProjGameModeBase::IncreaseDifficult()
{
	if (GamePoints >= PastGamePointsStage + PointToNewDifficult)
	{
		EnemySpawnComponent->ChangeStageTimeMultiplier *= DifficultMultiplier;
		PastGamePointsStage = PastGamePointsStage + PointToNewDifficult;
	}
}

void AArcadeTestProjGameModeBase::AddPoints(int Points)
{
	GamePoints += Points;
	IncreaseDifficult();
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

