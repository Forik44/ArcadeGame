// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArcadeTestProjGameModeBase.h"

AArcadeTestProjGameModeBase::AArcadeTestProjGameModeBase()
{
	EnemySpawnComponent = CreateDefaultSubobject<UEnemySpawnComponent>(TEXT("EnemySpawnComponent"));

	HealtsComponents = CreateDefaultSubobject<UGameHealthComponent>(TEXT("HealthsComponent"));
}
