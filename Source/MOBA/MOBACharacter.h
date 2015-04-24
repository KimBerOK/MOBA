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
		//handles moving forward/backward
	UFUNCTION()
		void MoveForward(float Val);
		//handles strafing
	UFUNCTION()
		void MoveRight(float Val);

public:
	// Sets default values for this character's properties
	AMOBACharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


};
