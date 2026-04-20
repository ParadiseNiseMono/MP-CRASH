// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Public/Interaction/MP_Player.h"
#include "MP_CRASHCharacter.generated.h"

class UMP_HealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AMP_CRASHCharacter : public ACharacter, public IMP_Player
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** GenericAction Action is test only*/
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* GenericAction;

public:

	/** Constructor */
	AMP_CRASHCharacter();

	/** IMP_Player Interface*/
	virtual USkeletalMeshComponent* GetSkeletalMesh_Implementation() const override;

	virtual void GrantArmor_Implementation(float ArmorAmount) override;

	virtual void PickUpItem_Implementation() override;

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/////////// Crash Course////////////

public:
	// 1. override GetLifetimeReplicatedProps
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	UFUNCTION(BlueprintPure)
	float GetArmorValue();
private:

	//2. add UPROPERTY Macro with Replicated specifier
	UPROPERTY(ReplicatedUsing = OnRep_Armor)
	float Armor;

	UPROPERTY(ReplicatedUsing = OnRep_ItemCount)
	int32 PickupCount;

	UFUNCTION()
	void OnRep_Armor();

	UFUNCTION()
	void OnRep_ItemCount(int32 PreviousValue);

	bool bReplicatePickupCount = false;

	UFUNCTION()
	void OnGeneric();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMP_HealthComponent> HealthComponent;
};

