// Copyright Joe Horacki 2020


#include "Weapons/BulletBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Weapons/WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Hit Sphere
	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HitSphere"));
	SetRootComponent(HitSphere);

	HitSphere->InitSphereRadius(12.0);
	HitSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	HitSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	HitSphere->SetNotifyRigidBodyCollision(true);

	// Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetupAttachment(HitSphere);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (GetOwner())
	{
		MeshComp->IgnoreActorWhenMoving(GetOwner(), true);
	}
	
	if (GetOwner() && GetOwner()->GetOwner())
	{
		MeshComp->IgnoreActorWhenMoving(GetOwner()->GetOwner(), true);
	}
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComp->InitialSpeed = 3000.0;
	ProjectileMovementComp->Velocity = FVector(1.0, 0.0, 0.0);

}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	HitSphere->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor)
	{
		return;
	}
	AWeaponBase* MyGun = Cast<AWeaponBase>(GetOwner());
	float DamageToDeal;
	if (MyGun)
	{
		DamageToDeal = MyGun->Damage;
	}
	else
	{
		DamageToDeal = 50;
	}
	
	float DamageMultiplier = 1.0;
	if (Hit.BoneName == TEXT("Head"))
	{
		DamageMultiplier = 2.0;
	}
	
	const float FinalDamage = DamageToDeal * DamageMultiplier;
		
	UGameplayStatics::ApplyDamage(OtherActor, FinalDamage, nullptr, GetOwner(), UDamageType::StaticClass());
	this->Destroy();
}

