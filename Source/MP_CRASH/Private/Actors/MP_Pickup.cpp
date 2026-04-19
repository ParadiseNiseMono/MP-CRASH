// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Actors/MP_Pickup.h"

#include "Components/SphereComponent.h"
#include "Public/Interaction/MP_Player.h"


AMP_Pickup::AMP_Pickup()
{
	PrimaryActorTick.bCanEverTick = false;

	bNetLoadOnClient = true;
	bReplicates = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetIsReplicated(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
}

void AMP_Pickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMP_Pickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!OtherActor->HasAuthority()) return;

	if (OtherActor->Implements<UMP_Player>())
	{
		IMP_Player::Execute_PickUpItem(OtherActor);
		Destroy();
	}
}

