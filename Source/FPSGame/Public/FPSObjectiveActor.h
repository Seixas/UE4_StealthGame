// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent; //forward declaration to not include another headerfile, just pass de compilation for our USphereComponent and minimize compilation time

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	//just a static mesh to represent the actor
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent * MeshComp;
	
	//UE4 macro to expose to BPs
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* SphereComp; //we are going to use that for collision

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override; //dive into Actor class and got this for us override
	
};
