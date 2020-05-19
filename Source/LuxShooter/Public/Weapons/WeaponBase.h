// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class ABulletBase;

UCLASS()
class LUXSHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon", meta=(AllowPrivateAccess = "true"))
	class UArrowComponent* MuzzlePoint;

public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Weapon")
	TSubclassOf<ABulletBase> BulletClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float RefireRate = 0.1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	int RemainingAmmo = 9999;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	bool bFullyAutomatic = false;

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void StartFiring();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void StopFiring();

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void onEquipeed();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon")
	void onUnequipped();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category="Weapon")
	void OnFiredRound();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon")
	float Damage = 30;

private:

	UFUNCTION()
	void FireRound();
	
	FTimerHandle RefireHandle;

};
