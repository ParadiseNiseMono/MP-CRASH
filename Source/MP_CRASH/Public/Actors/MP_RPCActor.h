// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_RPCActor.generated.h"

UCLASS()
class MP_CRASH_API AMP_RPCActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMP_RPCActor();

	UFUNCTION(Client, Reliable)
	void Client_PrintMessage(const FString& Message);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
