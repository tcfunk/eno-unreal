// Fill out your copyright notice in the Description page of Project Settings.


#include "SplineLayoutTool.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SplineComponent.h"

// Sets default values
ASplineLayoutTool::ASplineLayoutTool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Static Mesh"));

	InstancedMesh->bRenderCustomDepth = true;
}

// Called when the game starts or when spawned
void ASplineLayoutTool::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASplineLayoutTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASplineLayoutTool::InstanceMeshesAlongSpline()
{
	// Make sure we have defined a mesh to instance.
	if (!ensure(PlacedMesh != nullptr)) return;

	InstancedMesh->ClearInstances();
	InstancedMesh->SetStaticMesh(PlacedMesh);

	const FBox MeshBounds = PlacedMesh->GetBoundingBox();
	const float MeshSpacing = (MeshBounds.Max - MeshBounds.Min).X * Spacing;
	const int32 NumSplinePoints = UE4::SSE::FloorToInt32(Spline->GetSplineLength());

	for (int i = 0; i < NumSplinePoints; ++i)
	{
		// Get location and rotation along spline.
		auto InstanceLocation = Spline->
			GetLocationAtDistanceAlongSpline(MeshSpacing * i, ESplineCoordinateSpace::World);
		auto InstanceRotation = Spline->
			GetRotationAtDistanceAlongSpline(MeshSpacing * i, ESplineCoordinateSpace::World);

		// Add vertical offset.
		InstanceLocation += FVector::UpVector * VerticalOffset;
		
		InstancedMesh->AddInstance(FTransform(InstanceRotation, InstanceLocation));
	}
}

FVector ASplineLayoutTool::GetLocationAtIndex(float DistanceAlongSpline) const
{
	return Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::World);
}
