// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHealthComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGameHealthComponent::UGameHealthComponent()
	:
	Healths(3)
{ 
	
}


// Called when the game starts
void UGameHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Log, TEXT("NoPlayerPawn"));
	}
}

void UGameHealthComponent::ChangeHealths(int ByValue)
{
	Healths += ByValue;

	OnHealthsChanged.Broadcast(ByValue);
	if (Healths <= 0)
	{
		OnHealthsEnded.Broadcast();
	}
}

int UGameHealthComponent::GetHealths()
{
	return Healths;
}




