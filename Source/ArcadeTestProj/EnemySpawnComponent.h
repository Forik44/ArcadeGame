// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyPawn.h"
#include "EnemySpawnComponent.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TSubclassOf<AEnemyPawn> EnemyClass = AEnemyPawn::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	int NumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float SpawnDelay;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADETESTPROJ_API UEnemySpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

protected:
	FEnemySpawnInfo SpawnStage;
	int EnemiesSpawned;

	virtual void Deactivate() override;

	FTimerHandle ChangeStageTimer;
	FTimerHandle EnemySpawnTimer;

	virtual void BeginPlay() override;

	void StartSpawnStage();
	void SpawnEnemy();

	FRandomStream Random;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	TArray<FEnemySpawnInfo> SpawnStages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMinDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float StageMaxDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies")
	float ChangeStageTimeMultiplier;


};
