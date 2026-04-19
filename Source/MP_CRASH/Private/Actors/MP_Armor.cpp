// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Actors/MP_Armor.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"


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

	ACharacter* OverlappedCharacter = Cast<ACharacter>(OtherActor);

	if (HasAuthority() && IsValid(OverlappedCharacter))
	{
		SphereMesh->AttachToComponent(OverlappedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Head");
		CubeMesh->AttachToComponent(OverlappedCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "S_Breast");
	}	
}

