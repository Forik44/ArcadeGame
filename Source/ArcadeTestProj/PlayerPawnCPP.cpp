#include "PlayerPawnCPP.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"


APlayerPawnCPP::APlayerPawnCPP()
{
	TouchMoveSensability = 1.f;
	MoveLimit.X = 500.f; MoveLimit.Y = 600.f;
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

void APlayerPawnCPP::BeginPlay()
{
	Super::BeginPlay();
	
	
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
	NewLocation.X = FMath::Clamp(NewLocation.X + TouchDeltaMove.Y, -MoveLimit.Y, MoveLimit.Y);
	NewLocation.Y = FMath::Clamp(NewLocation.Y + TouchDeltaMove.X * -1.0f, -MoveLimit.X, MoveLimit.X);

	SetActorLocation(NewLocation);

	TouchLocation = FVector2D(Location.X, Location.Y);
}



