// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MOBAGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOBA_API AMOBAGameMode : public AGameMode
{
	GENERATED_BODY()

	AMOBAGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void StartPlay() override;
	
	
	
	
};
