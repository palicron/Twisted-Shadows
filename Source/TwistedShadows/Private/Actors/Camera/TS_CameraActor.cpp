// Twisted Shadow make by JSP


#include "Actors/Camera/TS_CameraActor.h"


void ATS_CameraActor::BeginPlay()
{
	Super::BeginPlay();
}

FVector ATS_CameraActor::GetCameraForwardVector() const
{
	return FVector::CrossProduct(GetActorForwardVector(), FVector::UpVector).GetSafeNormal();
}

