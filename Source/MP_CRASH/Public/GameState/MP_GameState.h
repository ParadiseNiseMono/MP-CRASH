// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MP_GameState.generated.h"

/**
 * 
 */
UCLASS()
class MP_CRASH_API AMP_GameState : public AGameState
{
	GENERATED_BODY()

public:
	void AddPlayerControllerToTeams(APlayerController* InPlayerController);

	void CheckPlayerTeam(APlayerController* PlayerControllerToCheck);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated)
	TArray<APlayerController*> TeamOne;

	UPROPERTY(Replicated)
	TArray<APlayerController*> TeamTwo;
};
