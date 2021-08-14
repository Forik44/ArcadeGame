// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawnComponent.h"
#include "GameHealthComponent.h"
#include "ArcadeTestProjGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

UCLASS()
class ARCADETESTPROJ_API AArcadeTestProjGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AArcadeTestProjGameModeBase();

	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnComponent* EnemySpawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
	UGameHealthComponent* HealtsComponents;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();
};
