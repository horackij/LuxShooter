// Copyright Joe Horacki 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCoords.h"
#include "GridSystem.generated.h"

class USceneComponent;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS(hideCategories = (Physics, LOD, Replication, Cooking, Activation), CollapseCategories = (Actor, INPUT, AssetUserData, Collision, Rendering, Tags), AutoExpandCategories = (Grids), ClassGroup = "GridSystem")
class RTSGRIDS_API AGridSystem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grids, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Grids, meta = (AllowPrivateAccess = "true"))
	UHierarchicalInstancedStaticMeshComponent* PreviewGridHISM;

public:	
	// Sets default values for this actor's properties
	AGridSystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grids)
	FGridCoord GridDimensions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grids)
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grids)
	TSet<FGridCoord> BlockedTiles;

	UPROPERTY(BlueprintReadOnly, Category = Grids)
	TArray<FGridCoord> GeneratedGrid;

	//Dev options

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grids)
	bool bShowPreviewGrid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grids)
	bool bShowTileTextInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Grids)
	bool bDrawBoundingBox;

	// Core Functions

	UFUNCTION(BlueprintCallable, Category = "Grids")
	TArray<FGridCoord> GenerateGrid();

	UFUNCTION(BlueprintPure, Category = "Grids")
	FVector GetGridOriginRelative();

	UFUNCTION(BlueprintPure, Category = "Grids")
	FVector GetGridOriginWorld();

	UFUNCTION(BlueprintPure, Category = "Grids")
	FVector2D GetGridSize();

	UFUNCTION(BlueprintPure, Category = "Grids")
	FVector2D GetGridExtents();

	UFUNCTION(BlueprintPure, Category = "Grids")
	FVector GetGridRelativeFromWorld(FVector WorldLocation);

	UFUNCTION(BlueprintPure, Category = "Grids")
	FVector GetCellCenterFromRelative(FVector RelativeLocation, bool bReturnWorldSpace);

	UFUNCTION(BlueprintPure, Category = "Grids")
	bool IsInGridBounds(FGridCoord Coordinate);

	UFUNCTION(BlueprintPure, Category = "Grids")
	bool IsClearTile(FGridCoord Coordinate);

	UFUNCTION(BlueprintPure, Category = "Grids")
	bool IsValidLocation(FGridCoord Coordinate);

	UFUNCTION(BlueprintPure, Category = "Grids")
	FGridCoord GetCoordinateFromRelative(FVector RelativeLocation, int& CellID);

	UFUNCTION(BlueprintPure, Category = "Grids")
	FGridCoord GetCoordinateFromCellID(int ID);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
