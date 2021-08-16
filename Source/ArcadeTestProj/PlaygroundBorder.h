// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlaygroundBorder.generated.h"

UCLASS()
class ARCADETESTPROJ_API APlaygroundBorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaygroundBorder();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Trigger;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
protected:

	

};
