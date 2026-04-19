// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MP_MultiplayerUtils.generated.h"

/**
 * 
 */
UCLASS()
class MP_CRASH_API UMP_MultiplayerUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Multiplayer Utils")
	static void PrintLocalNetRole(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Multiplayer Utils")
	static void PrintRemoteNetRole(AActor* Actor);
};

