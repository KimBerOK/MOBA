// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "MOBAPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API AMOBAPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_UCLASS_BODY()

	/* Update the FOV */
	virtual void UpdateCamera(float DeltaTime) override;
	
public:

	/* Default, hip fire FOV */
	float NormalFOV;

	/* Aiming down sight / zoomed FOV */
	float TargetingFOV;

};
