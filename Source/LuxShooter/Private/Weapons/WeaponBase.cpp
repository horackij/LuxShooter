// Copyright Joe Horacki 2020


#include "Weapons/WeaponBase.h"
#include "Components/ArrowComponent.h"
#include "Weapons/BulletBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
	: BulletClass(ABulletBase::StaticClass())
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);

	MuzzlePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Muzzle"));
	MuzzlePoint->SetupAttachment(RootComp);
	MuzzlePoint->ArrowSize = 0.25;
	MuzzlePoint->ArrowColor = FColor::Blue;

}

void AWeaponBase::StartFiring_Implementation()
{
	if (!BulletClass)
	{
		return;
	}

	if (RemainingAmmo > 0)
	{
		AActor* BulletOwner = GetOwner() ? GetOwner() : this;
		const FTransform SpawnTransform = MuzzlePoint->GetComponentTransform();

		FActorSpawnParameters Params;
		Params.Owner = BulletOwner;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(BulletClass, SpawnTransform, Params);
	}
	else  //no ammo
	{

	}
}

void AWeaponBase::StopFiring_Implementation()
{

}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

