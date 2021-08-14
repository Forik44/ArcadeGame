// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawnComponent.h"
#include "GameHealthComponent.h"
#include "ArcadeTestProjGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARCADETESTPROJ_API AArcadeTestProjGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AArcadeTestProjGameModeBase();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnComponent* EnemySpawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
	UGameHealthComponent* HealtsComponents;
};
