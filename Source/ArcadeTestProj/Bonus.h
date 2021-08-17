// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS(Blueprintable)
class ARCADETESTPROJ_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonus();

	UFUNCTION(BlueprintNativeEvent)
	void BonusCollected();
	virtual void BonusCollected_Implementation();

protected:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void Tick(float DeltaTime) override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bonus")
	class USphereComponent* Collision;


};
