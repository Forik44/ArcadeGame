// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealtsEndedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealtsChangedEvent, int, ChangeValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARCADETESTPROJ_API UGameHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Game Health")
	int Healths;
 
public:	
	
	UFUNCTION(BlueprintCallable, Category = "Game Health")
	void ChangeHealths(int ByValue);

	UFUNCTION(BlueprintPure, Category = "Game Health")
	int GetHealths();

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
	FHealtsEndedEvent OnHealthsEnded;

	UPROPERTY(BlueprintAssignable, Category = "Game Health")
	FHealtsChangedEvent OnHealthsChanged;
};
