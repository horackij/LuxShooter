// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ALuxCharacterBase::ALuxCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(GetRootComponent());

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

}

