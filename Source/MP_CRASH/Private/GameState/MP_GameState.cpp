// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/MP_GameState.h"

#include "Net/UnrealNetwork.h"

void AMP_GameState::AddPlayerControllerToTeams(APlayerController* InPlayerController)
{
	if (!IsValid(InPlayerController)) return;
	
	if (TeamOne.Num() <= TeamTwo.Num())
	{
		TeamOne.Add(InPlayerController);
	}
	else
	{
		TeamTwo.Add(InPlayerController);
	}
}

void AMP_GameState::CheckPlayerTeam(APlayerController* PlayerControllerToCheck)
{
	if (!IsValid(PlayerControllerToCheck)) return;
	
	if (TeamOne.Contains(PlayerControllerToCheck))
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Green,
		TEXT("Team1")
		);
	}
	else if (TeamTwo.Contains(PlayerControllerToCheck))
	{
		GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Red,
		TEXT("Team2")
		);
	}
}

void AMP_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, TeamOne);
	DOREPLIFETIME(ThisClass, TeamTwo);
}
