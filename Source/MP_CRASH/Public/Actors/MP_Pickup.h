// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_Pickup.generated.h"

class USphereComponent;

UCLASS()
class MP_CRASH_API AMP_Pickup : public AActor
{
	GENERATED_BODY()

public:
	AMP_Pickup();

protected:
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> SphereMesh;

	UPROPERTY(VisibleDefaultsOnly)
	TObjectPtr<USphereComponent> SphereCollision;
};
