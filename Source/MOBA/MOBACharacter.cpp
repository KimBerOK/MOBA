// Fill out your copyright notice in the Description page of Project Settings.

#include "MOBA.h"
#include "MOBACharacter.h"


// Sets default values
AMOBACharacter::AMOBACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// CameraComponent create and attach it to the CapsuleComponent
AMOBACharacter::AMOBACharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create a CameraComponent
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();

	// Position the camera a bit above eyes
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 50.0f + BaseEyeHeight);
	// Allow the pawn to control rotation.
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
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

}

// Called to bind functionality to input
void AMOBACharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &AMOBACharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMOBACharacter::MoveRight);

	// Jump gameplay key bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMOBACharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMOBACharacter::OnStopJump);

	// mouse camera control
	InputComponent->BindAxis("Turn", this, &AMOBACharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMOBACharacter::AddControllerPitchInput);

}

void AMOBACharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		//limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		//add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMOBACharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		//add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AMOBACharacter::OnStartJump()
{
	bPressedJump = true;
}

void AMOBACharacter::OnStopJump()
{
	bPressedJump = false;
}