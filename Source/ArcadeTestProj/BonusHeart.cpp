// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusHeart.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeTestProjGameModeBase.h"

void ABonusHeart::BonusCollected_Implementation()
{
	AGameModeBase* Gamemode = UGameplayStatics::GetGameMode(this);
	AArcadeTestProjGameModeBase* OurGamemode = Cast<AArcadeTestProjGameModeBase>(Gamemode);
	if (!OurGamemode)
	{
		return;
	}
	OurGamemode->HealtsComponents->ChangeHealths(1);
}
