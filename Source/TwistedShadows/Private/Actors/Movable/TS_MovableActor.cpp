// Twisted Shadow make by JSP


#include "Actors/Movable/TS_MovableActor.h"

#include "Character/Player/TS_PlayerCharacter.h"

// Sets default values
ATS_MovableActor::ATS_MovableActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	SetRootComponent(StaticMeshComponent);
	
	USceneComponent* SnapComponent = CreateDefaultSubobject<USceneComponent>("Snap Component 1");
	SnapComponent->SetupAttachment(RootComponent);
	SnapComponents.Add(SnapComponent);
	
	USceneComponent* SnapComponent1 = CreateDefaultSubobject<USceneComponent>("Snap Component 2");
	SnapComponent1->SetupAttachment(RootComponent);
	SnapComponents.Add(SnapComponent1);
	
	USceneComponent* SnapComponent2 = CreateDefaultSubobject<USceneComponent>("Snap Component 3");
	SnapComponent2->SetupAttachment(RootComponent);
	SnapComponents.Add(SnapComponent2);
	
	USceneComponent* SnapComponent3 = CreateDefaultSubobject<USceneComponent>("Snap Component 4");
	SnapComponent3->SetupAttachment(RootComponent);
	SnapComponents.Add(SnapComponent3);

	MovementType = ETS_MovementType::Forward;
}

// Called when the game starts or when spawned
void ATS_MovableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATS_MovableActor::ActivateInteractable_Implementation(const FInteractPayload Payload)
{
	if (Payload.Type == ETS_InteractionType::Started)
	{
		if (ATS_PlayerCharacter* Player = Cast<ATS_PlayerCharacter>(Payload.InstigatorCharacter))
		{
			if (USceneComponent* Nearest = GetNearestSnapComponent(Player->GetActorLocation()))
			{
				DrawDebugSphere(GetWorld(), Nearest->GetComponentLocation(), 100.0f, 10, FColor::Green, false, 10.0f);
				
				//TODO check for the movment tipe
				Player->StartGrabbingActor(this,Nearest,MovementType);
			}
			
		}
		return;
	}
	if (Payload.Type == ETS_InteractionType::Ended)
	{
		if (ATS_PlayerCharacter* Player = Cast<ATS_PlayerCharacter>(Payload.InstigatorCharacter))
		{
			Player->EndeGrabbingActor();
		}
	}
	
}

USceneComponent* ATS_MovableActor::GetNearestSnapComponent(const FVector Location)
{
	USceneComponent* Nearest = nullptr;
	float BestDistSq = TNumericLimits<float>::Max();

	for (USceneComponent* SceneComp : SnapComponents)
	{
		if (!SceneComp)
		{
			continue;
		}
		
		const float DistSq = FVector::DistSquared2D(Location, SceneComp->GetComponentLocation());
		if (DistSq < BestDistSq )
		{
			BestDistSq = DistSq;
			Nearest = SceneComp;
		}
	}
	
	return Nearest;
}

// Called every frame
void ATS_MovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

