// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Goal/TS_GoalActor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "GameFrameWork/TS_GameMode_Base.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/TS_LevelFlowSubsystem.h"


ATS_GoalActor::ATS_GoalActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	PlayerDetectionSphere = CreateDefaultSubobject<USphereComponent>("Player Detector");
	PlayerDetectionSphere->SetupAttachment(MeshComponent);
	
	PlayerDetectionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	PlayerDetectionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	bCanBeActivate = true;
}

void ATS_GoalActor::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerDetectionSphere->OnComponentBeginOverlap.AddDynamic(this,&ATS_GoalActor::OnDetectorBeginOverlap);
	FlowSubsystem = GetGameInstance()->GetSubsystem<UTS_LevelFlowSubsystem>();
	
	GameModePtr = Cast<ATS_GameMode_Base>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

void ATS_GoalActor::OnDetectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bCanBeActivate || !FlowSubsystem.IsValid() || !GameModePtr.IsValid())
	{
		return;
	}
	
	GameModePtr->EndLevel(Cast<ACharacter>(OtherActor));
	
	//FlowSubsystem->LoadNextLevel();
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Goal ACtor"));
	
	
	
}



