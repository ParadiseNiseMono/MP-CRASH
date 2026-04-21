// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MP_PickupWidget.h"

#include "Components/TextBlock.h"

void UMP_PickupWidget::SetPickupCountText(const FText& Text) const
{
	Text_PickupCount->SetText(Text);
}
