// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save.generated.h"

/**
 * 
 */
UCLASS()
class ARCADETESTPROJ_API USave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Leaderboard")
	int RecordScore;
};
