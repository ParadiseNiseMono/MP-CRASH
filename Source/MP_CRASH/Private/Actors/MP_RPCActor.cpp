// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MP_RPCActor.h"


// Sets default values
AMP_RPCActor::AMP_RPCActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bNetLoadOnClient = true;
}

void AMP_RPCActor::Client_PrintMessage_Implementation(const FString& Message)
{
	FString PrintMessage = HasAuthority() ? TEXT("Server: ") : TEXT("Client: ");

	PrintMessage += Message;
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		PrintMessage
		);
}

// Called when the game starts or when spawned
void AMP_RPCActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Client_PrintMessage(TEXT("This should run on the client(RPCActor)"));
	}
	
}


