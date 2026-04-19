// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Actors/MP_Armor.h"

#include "Components/SphereComponent.h"
#include "Public/Interaction/MP_Player.h"


AMP_Armor::AMP_Armor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SphereMesh->SetupAttachment(RootComponent);
	SphereMesh->SetIsReplicated(true);

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	CubeMesh->SetupAttachment(RootComponent);
	CubeMesh->SetIsReplicated(true);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
}

void AMP_Armor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMP_Armor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor->HasAuthority()) return;

	if (OtherActor->Implements<UMP_Player>())
	{
		USkeletalMeshComponent* Mesh = IMP_Player::Execute_GetSkeletalMesh(OtherActor);

		SphereMesh->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Head");
		CubeMesh->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Breast");

		IMP_Player::Execute_GrantArmor(OtherActor, ArmorValue);
	}
}

