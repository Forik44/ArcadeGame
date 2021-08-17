// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusPoints.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeTestProjGameModeBase.h"

void ABonusPoints::BonusCollected_Implementation()
{
	AArcadeTestProjGameModeBase* Gamemode = Cast<AArcadeTestProjGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (Gamemode)
	{
		Gamemode->AddPoints(Points);
	}

	Super::BonusCollected_Implementation();
}