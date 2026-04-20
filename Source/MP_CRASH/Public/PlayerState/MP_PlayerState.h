// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MP_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MP_CRASH_API AMP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void IncreaseNumPickups() {NumPickups++;}

	int32 GetNumPickups() const {return NumPickups;}

protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(Replicated)
	int32 NumPickups;
};
