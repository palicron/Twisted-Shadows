// Twisted Shadow make by JSP


#include "Character/Player/TS_CasterCharacter.h"

#include "GameFramework/PawnMovementComponent.h"

ATS_CasterCharacter::ATS_CasterCharacter()
{
}

void ATS_CasterCharacter::SetCasterShadow(const bool bActiveShadow)
{
	if (GetMesh())
	{
		GetMesh()->SetCastShadow(bActiveShadow);
	}
}

void ATS_CasterCharacter::OnGoalTouch()
{
	GetMovementComponent()->StopMovementImmediately();
}
