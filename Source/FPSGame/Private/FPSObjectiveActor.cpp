// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h" // we can use Alt+Shift+O with VisualAssistX to search file path of needed package
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));//now we instantiate the components
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp; //our mesh is the root for our sphare be attached

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore); //we set to ignore all channels/layers first
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); //we set to only response a Pawn, the projectile for ex can pass through
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
	
}

void AFPSObjectiveActor::PlayEffects()
{

	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}


void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarringObjective = true;

		Destroy();
	}
}

