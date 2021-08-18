// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusShield.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerPawnCPP.h"
#include "Engine/World.h"
#include "PawnShield.h"

void ABonusShield::BonusCollected_Implementation()
{
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Pawn)
	{
		return;
	}

	APlayerPawnCPP* PlayerPawn = Cast<APlayerPawnCPP>(Pawn);
	if (!PlayerPawn || !PlayerPawn->CanBeDamaged())
	{
		return;
	}
	 

	APawnShield* Shield = GetWorld()->SpawnActor<APawnShield>(ShieldClass);

	Shield->ActivateShield(PlayerPawn);			

	Super::BonusCollected_Implementation();
}