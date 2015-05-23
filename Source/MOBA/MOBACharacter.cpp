// Fill out your copyright notice in the Description page of Project Settings.

#include "MOBA.h"
#include "MOBACharacter.h"
#include "MOBACharacterMovementComponent.h"


// Sets default values
// CameraComponent create and attach it to the CapsuleComponent
AMOBACharacter::AMOBACharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UMOBACharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();

	// Adjust jump to make it less floaty
	MoveComp->GravityScale = 1.5f;
	MoveComp->JumpZVelocity = 620;
	MoveComp->bCanWalkOffLedgesWhenCrouching = true;
	MoveComp->MaxWalkSpeedCrouched = 200;

	// Enable crouching
	MoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;

	// Create a CameraComponent
	CameraComp = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	CameraComp->AttachParent = GetCapsuleComponent();

	// Position the camera a bit above eyes
	CameraComp->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	// Allow the pawn to control rotation.
	CameraComp->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMOBACharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using MOBACharacter!"));
	}
}

// Called every frame
void AMOBACharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bWantsToRun && !IsSprinting())
	{
		SetSprinting(true);
	}
}

// Called to bind functionality to input
void AMOBACharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Movement
	InputComponent->BindAxis("MoveForward", this, &AMOBACharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMOBACharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	InputComponent->BindAction("SprintHold", IE_Pressed, this, &AMOBACharacter::OnStartSprinting);
	InputComponent->BindAction("SprintHold", IE_Released, this, &AMOBACharacter::OnStopSprinting);

	InputComponent->BindAction("CrouchToggle", IE_Released, this, &AMOBACharacter::OnCrouchToggle);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMOBACharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMOBACharacter::OnStopJump);

	/* Interaction
	InputComponent->BindAction("Use", IE_Pressed, this, &AMOBACharacter::Use);
	InputComponent->BindAction("DropWeapon", IE_Pressed, this, &AMOBACharacter::DropWeapon);
	
	// Weapons
	InputComponent->BindAction("Targeting", IE_Pressed, this, &AMOBACharacter::OnStartTargeting);
	InputComponent->BindAction("Targeting", IE_Released, this, &AMOBACharacter::OnEndTargeting);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AMOBACharacter::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &AMOBACharacter::OnStopFire);

	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &AMOBACharacter::OnNextWeapon);
	InputComponent->BindAction("PrevWeapon", IE_Pressed, this, &AMOBACharacter::OnPrevWeapon);

	InputComponent->BindAction("EquipPrimaryWeapon", IE_Pressed, this, &AMOBACharacter::OnEquipPrimaryWeapon);
	InputComponent->BindAction("EquipSecondaryWeapon", IE_Pressed, this, &AMOBACharacter::OnEquipSecondaryWeapon);
	*/
}

void AMOBACharacter::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AMOBACharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		const FRotator Rotation = GetActorRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMOBACharacter::OnStartJump()
{
	bPressedJump = true;

	SetIsJumping(true);
}

void AMOBACharacter::OnStopJump()
{
	bPressedJump = false;
}

/**********************
***    TARGETING    ***
**********************/

bool AMOBACharacter::IsTargeting() const
{
	return bIsTargeting;
}

float AMOBACharacter::GetTargetingSpeedModifier() const
{
	return TargetingSpeedModifier;
}

