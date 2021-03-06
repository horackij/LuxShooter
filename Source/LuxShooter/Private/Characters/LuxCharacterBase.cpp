// Fill out your copyright notice in the Description page of Project Settings.


#include "LuxCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/WeaponBase.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

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

void ALuxCharacterBase::Destroyed()
{
	UnEquipWeapon();

	Super::Destroyed();
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

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ALuxCharacterBase::StartShoot);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ALuxCharacterBase::StopShoot);

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
	if (EquippedWeapon)
	{
		EquippedWeapon->StartFiring();
	}
}

void ALuxCharacterBase::StopShoot()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->StopFiring();
	}
}

void ALuxCharacterBase::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
}

void ALuxCharacterBase::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void ALuxCharacterBase::CycleWeapons(bool bForwards)
{
	if (WeaponInventory.Num() == 0)
	{
		return;
	}

	int CurrentEquippedID = WeaponInventory.Find(EquippedWeapon->GetClass());

	if (CurrentEquippedID == INDEX_NONE)
	{
		CurrentEquippedID = 0;
	}

	int DesiredID;

	int y = WeaponInventory.Num();

	if (bForwards)
	{
		int x = CurrentEquippedID + 1;
		DesiredID = FMath::Fmod(x, y);
	}
	else
	{
		int x = CurrentEquippedID - 1;
		DesiredID = ((x % y) + y) % y;
	}
	if (!WeaponInventory[DesiredID]->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find valid weapon class in %s"), *GetName());
		return;
	}
	EquipWeapon(WeaponInventory[DesiredID]);
}

void ALuxCharacterBase::GrantWeapon(TSubclassOf<AWeaponBase> NewWeapon, bool bEquip)
{
	WeaponInventory.AddUnique(NewWeapon);

	if (bEquip)
	{
		EquipWeapon(NewWeapon);
	}
}

void ALuxCharacterBase::RemoveWeapon(TSubclassOf<AWeaponBase> Weapon)
{
	if (GetEquipppedWeapon()->IsA(Weapon))
	{
		UnEquipWeapon();

	}

	WeaponInventory.Remove(Weapon);
}

AWeaponBase* ALuxCharacterBase::GetEquipppedWeapon()
{
	return EquippedWeapon;
}

AWeaponBase* ALuxCharacterBase::EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon)
{
	if (EquippedWeapon)
	{
		UnEquipWeapon();
	}

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EquippedWeapon = GetWorld()->SpawnActor<AWeaponBase>(NewWeapon, Params);

	if (EquippedWeapon)
	{

		if (UGameplayStatics::GetPlayerCharacter(this, 0) == this)
		{
			EquippedWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocket);
		}
		else
		{
			EquippedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, AttachSocket);
		}
		EquippedWeapon->OnEquipped();
		return EquippedWeapon;
	}
	return nullptr;
}

void ALuxCharacterBase::UnEquipWeapon()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->OnUnequipped();
		EquippedWeapon->Destroy();
	}
}

