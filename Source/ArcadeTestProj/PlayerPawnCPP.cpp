#include "PlayerPawnCPP.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/GameViewportClient.h"



APlayerPawnCPP::APlayerPawnCPP()
{
	TouchMoveSensability = 1.f;
	MoveLimit.X = 500.f; MoveLimit.Y = 700.f;
	PrimaryActorTick.bCanEverTick = true;

	PawnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PawnCollision"));
	SetRootComponent(PawnCollision);

	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	PawnMesh->SetupAttachment(GetRootComponent());

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));

	ShootComponent = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));

	
}

void APlayerPawnCPP::PossessedBy(AController* NewController)
{
	PlayerController = Cast<APlayerController>(NewController);
}

FVector2D APlayerPawnCPP::GetMoveLimit()
{
	return MoveLimit;
}

void APlayerPawnCPP::SetMoveLimit(FVector2D MoveLimits)
{
	MoveLimit = MoveLimits;
}

bool APlayerPawnCPP::CanBeDamagedBP_Implementation()
{
	return CanBeDamaged();
}

void APlayerPawnCPP::RecoverPawn_Implementation()
{
	ShootComponent->StartShooting();
	SetActorEnableCollision(true);
	PawnMesh->SetMaterial(0, PawnMaterial);

	TArray<UParticleSystemComponent*> Components;
	GetComponents(Components);
	for (UParticleSystemComponent* Component : Components)
	{
		UActorComponent* CastedParticle = Cast<UActorComponent>(Component);
		if (!CastedParticle)
		{
			continue;
		}
		CastedParticle->Activate();
	}
}

void APlayerPawnCPP::ExplodePawn_Implementation()
{
	SetActorEnableCollision(false);

	ShootComponent->StopShooting();

	PawnMesh->SetMaterial(0, RecoverMaterial);

	if (DestroyParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorTransform(), true);
	}

	TArray<UParticleSystemComponent*> Components;
	GetComponents(Components);
	for (UParticleSystemComponent* Component : Components)
	{
		UActorComponent* CastedParticle = Cast<UActorComponent>(Component);
		if (!CastedParticle)
		{
			continue;
		}
		CastedParticle->Deactivate();
	}
}

void APlayerPawnCPP::BeginPlay()
{
	Super::BeginPlay();
	
	PawnMaterial = PawnMesh->GetMaterial(0);
}

float APlayerPawnCPP::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!CanBeDamagedBP())
	{
		return 0.f;
	}

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	PawnDamaged.Broadcast();
	return DamageAmount;
}

void APlayerPawnCPP::IgnoreProjectile(AShootProjectile* Projectile)
{
	PawnCollision->IgnoreActorWhenMoving(Projectile, true);
}

void APlayerPawnCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPawnCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindTouch(IE_Pressed, this, &APlayerPawnCPP::OnTouchPress);
	InputComponent->BindTouch(IE_Repeat, this, &APlayerPawnCPP::OnTouchMove);

}

void APlayerPawnCPP::OnTouchPress(ETouchIndex::Type FingerIndex, FVector Location)
{
	TouchLocation = FVector2D(Location.X, Location.Y);
	Touching = true;
}

void APlayerPawnCPP::OnTouchMove(ETouchIndex::Type FingerIndex, FVector Location)
{
	FVector2D TouchDeltaMove = FVector2D(TouchLocation.X - Location.X, TouchLocation.Y - Location.Y);
	TouchDeltaMove *= TouchMoveSensability;
	FVector NewLocation = GetActorLocation();

	FVector2D ScreenPosition;
	APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(this, 0);
	UGameplayStatics::ProjectWorldToScreen(PlayerController1, NewLocation, ScreenPosition);
	
	FVector2D ViewportSize;
	int SizeX, SizeY;
	PlayerController->GetViewportSize(SizeX, SizeY);
	ViewportSize.X = (float)SizeX;
	ViewportSize.Y = (float)SizeY;
	bool IsAngle = false;

	if (ScreenPosition.X > ViewportSize.X-30)
	{
		UE_LOG(LogTemp, Log, TEXT("1"));
		TouchDeltaMove.X = FMath::Clamp(TouchDeltaMove.X, 0.f, 10000.f);
	}
	if (ScreenPosition.Y > ViewportSize.Y-25)
	{
		UE_LOG(LogTemp, Log, TEXT("2"));
		TouchDeltaMove.Y = FMath::Clamp(TouchDeltaMove.Y, 0.f, 10000.f);
	}
	if (ScreenPosition.X < 25)
	{
		UE_LOG(LogTemp, Log, TEXT("3"));
		TouchDeltaMove.X = FMath::Clamp(TouchDeltaMove.X, -10000.f, 0.f);
	}
	if (ScreenPosition.Y < 30)
	{
		UE_LOG(LogTemp, Log, TEXT("4"));
		TouchDeltaMove.Y = FMath::Clamp(TouchDeltaMove.Y, -10000.f, 0.f);
	
	}


	NewLocation.X = NewLocation.X + TouchDeltaMove.Y;
	NewLocation.Y = NewLocation.Y + TouchDeltaMove.X * -1.0f;
	

	

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}



