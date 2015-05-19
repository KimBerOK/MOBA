// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "MOBACharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API UMOBACharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	virtual float GetMaxSpeed() const override;
	
	
};
