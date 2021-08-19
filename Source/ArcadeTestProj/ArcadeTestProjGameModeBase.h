// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemySpawnComponent.h"
#include "GameHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "ShootComponent.h"
#include "ArcadeTestProjGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameOverEvent);

USTRUCT(BlueprintType)
struct FShootInfoLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TArray<FShootInfo> ShootInfos;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float ShootPeriod;
};

UCLASS()
class ARCADETESTPROJ_API AArcadeTestProjGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AArcadeTestProjGameModeBase();

	virtual void BeginPlay() override;
protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Game")
	void RecoverPawn();
	void RecoverPawn_Implementation();

	void IncreaseDifficult();

	FTimerHandle RecoverTimer;

	bool IsGameOver;

	int PastGamePointsStage;
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
	int CurrentShootLevel;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddPoints(int Points);

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool ChangeShootLevel(bool Up);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemies")
	UEnemySpawnComponent* EnemySpawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Health")
	UGameHealthComponent* HealtsComponents;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FGameOverEvent GameOver;

	UPROPERTY(BlueprintReadWrite, Category = "Game")
	float PlayerRecoverTime;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	class APlayerPawnCPP* PlayerPawn;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int GamePoints;

	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TArray<FShootInfoLevel> ShootInfoLevels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficult")
	int PointToNewDifficult;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Difficult")
	float DifficultMultiplier;




};
