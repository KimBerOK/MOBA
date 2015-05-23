// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MOBACharacter.generated.h"

UCLASS()
class MOBA_API AMOBACharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

public:
	// Sets default values for this character's properties
	AMOBACharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// First Person camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* CameraComp;

	// Constructor for AMOBACharacter
	AMOBACharacter(const FObjectInitializer& ObjectInitializer);

	/******************************
	***         MOVEMENT        ***
	*******************************/

	// handles moving forward/backward
	virtual void MoveForward(float Val);

	// handles strafing
	virtual void MoveRight(float Val);

	/* Client mapped to Input */

	void OnCrouchToggle();
	// sets jump flag when key is pressed
	void OnStartJump();
	// clears jump flag when key is released
	void OnStopJump();
	void OnStartSprinting();
	void OnStopSprinting();

	/* Character wants to run, checked during Tick to see if allowed */

	UPROPERTY(Transient, Replicated)
		bool bWantsToRun;

	/* Is character currently perfoming a jump action. Reset on landed. */

	UPROPERTY(Transient, Replicated)
		bool bIsJumping;
	UFUNCTION(BlueprintCallable, Category = "Movement")
		bool IsInitiatedJump() const;
		
		void SetIsJumping(bool NewJumping);

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerSetIsJumping(bool NewJumping);

		void OnLanded(const FHitResult& Hit) override;

	/* Client/local call to update sprint state */
		void SetSprinting(bool NewSprinting);

	/* Server side call to update actual sprint state */
		UFUNCTION(Server, Reliable, WithValidation)
			void ServerSetSprinting(bool NewSprinting);

		UFUNCTION(BlueprintCallable, Category = "Movement")
			bool IsSprinting() const;

			float GetSprintingSpeedModifier() const;

		UPROPERTY(EditDefaultsOnly, Category = "Movement")
			float SprintingSpeedModifier;


	/******************************
	***        TARGETING       ****
	******************************/

	/* Is player aiming down sights */
	UFUNCTION(BlueprintCallable, Category = "Targeting")
		bool IsTargeting() const;

		float GetTargetingSpeedModifier() const;

	/* ???For what???*/
	UPROPERTY(Transient, Replicated)
		bool bIsTargeting;

};
