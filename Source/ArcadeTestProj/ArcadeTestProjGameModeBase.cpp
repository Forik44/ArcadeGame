// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeTestProjGameModeBase.h"


AArcadeTestProjGameModeBase::AArcadeTestProjGameModeBase()
{
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	HealtsComponents = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}

void AArcadeTestProjGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HealtsComponents->OnHealthsEnded.AddDynamic(this, &AArcadeTestProjGameModeBase::EndGame);
}

void AArcadeTestProjGameModeBase::EndGame()
{
	GameOver.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Game Over"));
}
