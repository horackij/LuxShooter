// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridsCharacter.generated.h"

UCLASS()
class RTSGRIDS_API AGridsCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGridsCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
