// Copyright Epic Games, Inc. All Rights Reserved.


#include "MP_CRASHPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "MP_CRASH.h"
#include "PlayerState/MP_PlayerState.h"
#include "Widgets/MP_PickupWidget.h"
#include "Widgets/Input/SVirtualJoystick.h"

void AMP_CRASHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogMP_CRASH, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AMP_CRASHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

void AMP_CRASHPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AMP_PlayerState* MP_PlayerState = Cast<AMP_PlayerState>(PlayerState))
	{
		if (PickupWidgetClass != nullptr)
		{
			PickupWidget = CreateWidget<UMP_PickupWidget>(this, PickupWidgetClass);
			
			if (PickupWidget != nullptr)
			{
				PickupWidget->AddToViewport();
				MP_PlayerState->OnPickupCountChanged.AddDynamic(this, &ThisClass::OnPickupCountChanged);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PickupWidgetClass is null! Please set it in the Blueprint."));
		}
	}
}

void AMP_CRASHPlayerController::OnPickupCountChanged(int32 NewPickupCount)
{
	if (IsValid(PickupWidget))
	{
		PickupWidget->SetPickupCountText(FText::FromString(FString::FromInt(NewPickupCount)));
	}
}
