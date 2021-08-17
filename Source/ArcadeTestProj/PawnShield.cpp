#include "PawnShield.h"
#include "PlayerPawnCPP.h"
#include "Engine/World.h"
#include "TimerManager.h"

APawnShield::APawnShield()
	:
	ShieldPeriod(4)
{
 

}

void APawnShield::ActivateShield(APlayerPawnCPP* PlayerPawn)
{
	if (!PlayerPawn)
	{
		Destroy();
		return;
	}
	PawnForShield = PlayerPawn;
	PawnForShield->SetCanBeDamaged(false);
	FAttachmentTransformRules AttachRules = FAttachmentTransformRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false);
	AttachToActor(PlayerPawn, AttachRules);

	GetWorld()->GetTimerManager().SetTimer(ShieldTimer, this, &APawnShield::DeactivateShield, ShieldPeriod, false);
}

void APawnShield::DeactivateShield()
{
	if (!PawnForShield)
	{
		return;
	}

	PawnForShield->SetCanBeDamaged(true);

	Destroy();
}
