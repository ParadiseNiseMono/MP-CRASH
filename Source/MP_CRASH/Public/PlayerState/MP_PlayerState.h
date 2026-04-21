// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MP_PlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickupCountChanged, int32, PickupCount);

/**
 * 
 */
UCLASS()
class MP_CRASH_API AMP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void SetNumPickups(float Amount);

	int32 GetNumPickups() const {return NumPickups;}

	UPROPERTY(BlueprintAssignable)
	FOnPickupCountChanged OnPickupCountChanged;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_NumPickups)
	int32 NumPickups;

	UFUNCTION()
	void OnRep_NumPickups();
};
