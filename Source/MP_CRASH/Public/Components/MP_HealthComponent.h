// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MP_HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MP_CRASH_API UMP_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMP_HealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	bool GetRepNotifyHealth() const {return bRepNotifyHealth;}
	void SetRepNotifyHealth(bool bNewRepNotifyHealth) {bRepNotifyHealth = bNewRepNotifyHealth;}

	void IncreaseHealth() {Health++;};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float Health;

	UFUNCTION()
	void OnRep_Health();

	bool bRepNotifyHealth = false;
};
