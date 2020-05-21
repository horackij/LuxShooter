// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaceableBase.generated.h"

UCLASS()
class RTSGRIDS_API APlaceableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlaceableBase();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Placeable")
	void OnPlacementCompleted();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Placeable")
	void OnPlacementBegin();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Placeable")
	void OnPlacementCancelled();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable")
	TSubclassOf<AActor> ConstructionProxy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable")
	TSubclassOf<AActor> PlacementProxy;

	// If BuildDuration <= 0.0, Build instantly skipping construction phase
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable")
	float BuildDuration = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeable")
	float BuildDurationMultiply = 1.0;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	AActor* PlacementProxy;
	AActor* ConstructionProxy;
};
