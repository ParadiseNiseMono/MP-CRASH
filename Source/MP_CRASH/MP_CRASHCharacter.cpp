// Copyright Epic Games, Inc. All Rights Reserved.

#include "MP_CRASHCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MP_CRASH.h"
#include "Components/MP_HealthComponent.h"
#include "Net/UnrealNetwork.h"

AMP_CRASHCharacter::AMP_CRASHCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UMP_HealthComponent>("HealthComponent");

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

USkeletalMeshComponent* AMP_CRASHCharacter::GetSkeletalMesh_Implementation() const
{
	return GetMesh();
}

void AMP_CRASHCharacter::GrantArmor_Implementation(float ArmorAmount)
{
	Armor = ArmorAmount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("ArmorAmount = %f"), Armor));
}

void AMP_CRASHCharacter::PickUpItem_Implementation()
{
	PickupCount++;

	if (!IsValid(HealthComponent)) return;
	HealthComponent->IncreaseHealth();
}

void AMP_CRASHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMP_CRASHCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMP_CRASHCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMP_CRASHCharacter::Look);

		EnhancedInputComponent->BindAction(GenericAction, ETriggerEvent::Started, this, &AMP_CRASHCharacter::OnGeneric);
	}
	else
	{
		UE_LOG(LogMP_CRASH, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMP_CRASHCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetWorldTimerManager().SetTimer(RpcDelayTimer, this, &ThisClass::OnRpcDelayTimer, 4.0f, false);
}


void AMP_CRASHCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMP_CRASHCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMP_CRASHCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMP_CRASHCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMP_CRASHCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AMP_CRASHCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AMP_CRASHCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//3. DOREPLIFETIME
	DOREPLIFETIME_CONDITION(ThisClass, Armor, COND_AutonomousOnly);
	DOREPLIFETIME_CONDITION(ThisClass, PickupCount, COND_Custom);
}

void AMP_CRASHCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);
	
	//如果 bReplicatePickupCount 改變數值，PickupCount 的同步狀態也會跟著改變。注意：該布林值只看伺服器端的狀態。
	DOREPLIFETIME_ACTIVE_OVERRIDE(ThisClass, PickupCount, bReplicatePickupCount);
}

float AMP_CRASHCharacter::GetArmorValue()
{
	return Armor;
}

void AMP_CRASHCharacter::OnRep_Armor()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("OnRep ArmorAmount = %f"), Armor));
}

void AMP_CRASHCharacter::OnRep_ItemCount(int32 PreviousValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OnRep PreviousValue ItemCount = %d"), PreviousValue));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OnRep ItemCount = %d"), PickupCount));
}

void AMP_CRASHCharacter::OnGeneric()
{
	/*bReplicatePickupCount = !bReplicatePickupCount;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("bReplicatePickupCount = %d"), bReplicatePickupCount));*/

	if (!IsValid(HealthComponent)) return;
	HealthComponent->SetRepNotifyHealth(!HealthComponent->GetRepNotifyHealth());

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("bRepNotifyHealth = %d"), HealthComponent->GetRepNotifyHealth()));
}

void AMP_CRASHCharacter::OnRpcDelayTimer()
{
	if (HasAuthority())
	{
		NetMulticast_PrintMessage("NetMulticast");
	}
}

void AMP_CRASHCharacter::NetMulticast_PrintMessage_Implementation(const FString& Message)
{
	FString PrintMessage = HasAuthority() ? TEXT("Server: ") : TEXT("Client: ");

	PrintMessage += Message;
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Green,
		PrintMessage
		);
}

void AMP_CRASHCharacter::Client_PrintMessage_Implementation(const FString& Message)
{
	FString PrintMessage = HasAuthority() ? TEXT("Server: ") : TEXT("Client: ");

	PrintMessage += Message;
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Yellow,
		PrintMessage
		);
}
