// Twisted Shadow make by JSP


#include "Actors/Movable/TS_MovableActor.h"

// Sets default values
ATS_MovableActor::ATS_MovableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	SetRootComponent(StaticMeshComponent);

}

// Called when the game starts or when spawned
void ATS_MovableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATS_MovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

