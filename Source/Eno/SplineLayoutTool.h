// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineLayoutTool.generated.h"

UCLASS()
class ENO_API ASplineLayoutTool : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASplineLayoutTool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USplineComponent* Spline;

	UPROPERTY(EditAnywhere)
	class UStaticMesh* PlacedMesh;

	UPROPERTY(EditDefaultsOnly)
	class UInstancedStaticMeshComponent* InstancedMesh;

	/** Space according to mesh size. 1.0 places them directly side-by-side */
	UPROPERTY(EditAnywhere)
	float Spacing = 1.0;

	/** Offset mesh along up axis. */
	UPROPERTY(EditAnywhere)
	float VerticalOffset = 0.0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:

	UFUNCTION(BlueprintCallable)
	void InstanceMeshesAlongSpline();

	FVector GetLocationAtIndex(float DistanceAlongSpline) const;
};
