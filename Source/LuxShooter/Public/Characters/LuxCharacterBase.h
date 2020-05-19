// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LuxCharacterBase.generated.h"

class UCameraComponent;

UCLASS()
class LUXSHOOTER_API ALuxCharacterBase : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta=(AllowPrivateAccess="true"))
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

public:
	// Sets default values for this character's properties
	ALuxCharacterBase();

	UCameraComponent* GetCameraComponent() { return CameraComp; }
	USkeletalMeshComponent* GetMesh1P() { return Mesh1P; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);
	void Turn(float Value); // used for mouse
	void TurnRate(float Value);  // used for controllers
	void LookUp(float Value);  // used for mouse
	void LookUpRate(float Value); // used for controllers

	void StartJump();
	void StopJump();
	void StartShoot();
	void StopShoot();
	void StartSprint();
	void StopSprint();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void CycleWeapons(bool bForwards);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void GrantWeapon(TSubclassOf<AWeaponBase> NewWeapon, bool bEquip);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void RemoveWeapon(TSubclassOf<AWeaponBase> Weapon);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Weapons")
	TArray<TSubclassOf<AWeaponBase>> WeaponInventory;

private:

	AWeaponBase* EquippedWeapon;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapons")
	FName AttachSocket;

	UFUNCTION(BlueprintPure, Category="Weapons")
	AWeaponBase* GetEquipppedWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	AWeaponBase* EquipWeapon(TSubclassOf<AWeaponBase> NewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void UnEquipWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseTurnRate = 45.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float BaseLookAtRate = 45.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lux")
	float MaxSprintSpeed = 900.0;

private:

	float DefaultWalkSpeed;

};
