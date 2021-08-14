#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "ShootComponent.h"
#include "ShootProjectile.h"
#include "PlayerPawnCPP.generated.h"


UCLASS()
class ARCADETESTPROJ_API APlayerPawnCPP : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location);
	void OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location);

	APlayerController* PlayerController;
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Healths")
	bool CanBeDamagedBP();
	bool CanBeDamagedBP_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Healths")
	void ExplodePawn();
	void ExplodePawn_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Healths")	
	void RecoverPawn();
	void RecoverPawn_Implementation();

	FVector2D MoveLimit;

	FTimerHandle RecoverTimer;
private:

	FVector2D TouchLocation;

	bool Touching; 
	
public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*void RecieveAnyDamage(float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* PawnCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UStaticMeshComponent* PawnMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent*  PawnCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	UShootComponent* ShootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
	float TouchMoveSensability;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Controls")
	float RecoverTime;

	void IgnoreProjectile(AShootProjectile* Projectile);

};
