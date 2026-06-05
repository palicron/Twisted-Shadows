// Twisted Shadow make by JSP


#include "Character/Player/TS_ShadowCharacter.h"

#include "Character/Player/TS_CasterCharacter.h"

ATS_ShadowCharacter::ATS_ShadowCharacter()
{
	ShadowLifeTime = 30.f;
	ShadowMaxRange = 1000.f;
	ShadowMinRange = 100.f;
	CheckTickRate = 0.1f;
	
	CurrentShadowLifeTime = 0.f;
}

void ATS_ShadowCharacter::SetUpShadowInfo(ATS_PlayerCharacter* Caster, const FVector& ShadowLocation)
{
	CasterPtr = Caster;
	GetWorld()->GetTimerManager().SetTimer(ShadowLifeTimerHandle,this,&ATS_ShadowCharacter::CheckShadowLife, CheckTickRate,{.bLoop = true,.bMaxOncePerFrame = true});
	ShadowStartingLocation = ShadowLocation;
}

void ATS_ShadowCharacter::DestroyShadow()
{
	OnShadowDestroyDelegate.Broadcast();
	GetWorld()->GetTimerManager().ClearTimer(ShadowLifeTimerHandle);
	Destroy();
}

void ATS_ShadowCharacter::CheckShadowLife()
{
	//@TODO create UI controller and update it 
	CurrentShadowLifeTime += CheckTickRate;
	if (CurrentShadowLifeTime >= ShadowLifeTime || !CasterPtr.IsValid())
	{
		DestroyShadow();
	}
	
	float DistanceToCaster = (CasterPtr->GetActorLocation() - GetActorLocation()).Size();
	if (FMath::Abs(DistanceToCaster) > ShadowMaxRange || FMath::Abs(DistanceToCaster) < ShadowMinRange)
	{
		DestroyShadow();
	}
}
