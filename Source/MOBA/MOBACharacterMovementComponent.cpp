// Fill out your copyright notice in the Description page of Project Settings.

#include "MOBA.h"
#include "MOBACharacterMovementComponent.h"
#include "MOBACharacter.h"

float UMOBACharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	const AMOBACharacter* CharOwner = Cast<AMOBACharacter>(PawnOwner);
	if (CharOwner)
	{
		// Slow down during targeting, but don't further reduce movement speed while also crouching
		if (CharOwner->IsTargeting() && !CharOwner->GetMovementComponent()->IsCrouching())
		{
			MaxSpeed *= CharOwner->GetTargetingSpeedModifier();
		}
		else if (CharOwner->IsSprinting())
		{
			MaxSpeed *= CharOwner->GetSprintingSpeedModifier();
		}
	}

	return MaxSpeed;
}




