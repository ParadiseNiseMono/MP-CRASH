// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MP_PickupWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MP_CRASH_API UMP_PickupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPickupCountText(const FText& Text) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_PickupCount;
};
