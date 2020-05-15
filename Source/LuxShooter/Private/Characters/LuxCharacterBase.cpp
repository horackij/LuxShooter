// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ALuxCharacterBase::ALuxCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(GetRootComponent());
	CameraComp->bUsePawnControlRotation = true; //allows up and down look movement with the mouse/controller

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(CameraComp);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(false);
	Mesh1P->SetCastShadow(false);
	Mesh1P->SetReceivesDecals(false);
	
	GetMesh()->SetOnlyOwnerSee(false);
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void ALuxCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called every frame
void ALuxCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALuxCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ALuxCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ALuxCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &ALuxCharacterBase::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ALuxCharacterBase::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &ALuxCharacterBase::TurnRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ALuxCharacterBase::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ALuxCharacterBase::LookUpRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ALuxCharacterBase::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ALuxCharacterBase::StopJump);

	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &ALuxCharacterBase::StartShoot);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &ALuxCharacterBase::StopShoot);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ALuxCharacterBase::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ALuxCharacterBase::StopSprint);
}

void ALuxCharacterBase::MoveForward(float Value)
{
	if (Value != 0.0)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
	else
	{
		StopSprint();
	}

}

void ALuxCharacterBase::MoveRight(float Value)
{
	if (Value != 0.0)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ALuxCharacterBase::MoveUp(float Value)
{
	if (Value != 0.0)
	{
		AddMovementInput(GetActorUpVector(), Value);
	}
}

void ALuxCharacterBase::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ALuxCharacterBase::TurnRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALuxCharacterBase::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ALuxCharacterBase::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookAtRate * GetWorld()->GetDeltaSeconds());
}

void ALuxCharacterBase::StartJump()
{
	Jump();
}

void ALuxCharacterBase::StopJump()
{
	StopJumping();
}

void ALuxCharacterBase::StartShoot()
{

}

void ALuxCharacterBase::StopShoot()
{

}

void ALuxCharacterBase::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void ALuxCharacterBase::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}


