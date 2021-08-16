// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AShootProjectile::AShootProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpeed = 1000.f;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	SetRootComponent(Collision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetCollisionProfileName("NoCollision");

}

// Called when the game starts or when spawned
void AShootProjectile::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AShootProjectile::OnProjectileOverlap);
	if (GetOwner())
	{
		Collision->IgnoreActorWhenMoving(GetOwner(), true);
		
	}
}

void AShootProjectile::OnProjectileOverlap(UPrimitiveComponent* OpelappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool Sweep, const FHitResult& Hit)
{
	if (OtherActor && !Cast<APawn>(OtherActor))//if no overlapped actor ot it is not pawn
	{
		return;
	}
	if (!GetOwner())
	{
		return;
	}
	APawn* PawnOwner = Cast<APawn>(GetOwner());

	if (!PawnOwner)
	{
		return;
	}
	AController* InstigatorOwn = PawnOwner->GetController();
	
	UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorOwn, this, UDamageType::StaticClass());
	
	Destroy();
}
// Called every frame
void AShootProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorLocalOffset(FVector(ProjectileSpeed*DeltaTime,0.f,0.f));
}

