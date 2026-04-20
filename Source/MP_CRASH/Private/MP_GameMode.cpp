// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Gamemode/MP_GameMode.h"


AMP_GameMode::AMP_GameMode()
{
	bDelayedStart = true;
	StartMatchDelay = 5.f;
}

void AMP_GameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(StartGameTimerHandle, this, &ThisClass::StartMatch, StartMatchDelay, false);
}

void AMP_GameMode::StartMatch()
{
	Super::StartMatch();

	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Green,
		TEXT("Start Match")
		);
}
