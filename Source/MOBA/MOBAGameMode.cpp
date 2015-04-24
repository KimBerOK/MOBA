// Fill out your copyright notice in the Description page of Project Settings.

#include "MOBA.h"
#include "MOBAGameMode.h"
#include "Engine.h"

AMOBAGameMode::AMOBAGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AMOBAGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("HELLO WORLD"));
	}
}