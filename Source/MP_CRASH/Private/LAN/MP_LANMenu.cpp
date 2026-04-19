// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/LAN/MP_LANMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void UMP_LANMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FInputModeUIOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = true;

	Button_Host->OnClicked.AddDynamic(this, &ThisClass::OnHostButtonClicked);
	Button_Join->OnClicked.AddDynamic(this, &ThisClass::OnJoinButtonClicked);
}

void UMP_LANMenu::OnHostButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = false;

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostingLevel, true, TEXT("Listen"));
}

void UMP_LANMenu::OnJoinButtonClicked()
{
	FInputModeGameOnly InputMode;
	GetOwningPlayer()->SetInputMode(InputMode);
	GetOwningPlayer()->bShowMouseCursor = false;

	const FString Address = TextBox_IpAddress->GetText().ToString();
	UGameplayStatics::OpenLevel(this, *Address);
}
