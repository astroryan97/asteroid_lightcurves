// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidComponent.h"
#include "StaticMeshResources.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UAsteroidComponent::UAsteroidComponent()
{}

UAsteroidComponent::UAsteroidComponent(const FObjectInitializer& ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = false;
}

void UAsteroidComponent::BeginPlay()
{
	maxDotProductSum = computeDotProducts(FVector(0, 0, 0), true);

	Super::BeginPlay();
}

void UAsteroidComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAsteroidComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	currRotation += DeltaTime * rotationSpeed;
	float currRotationRad = FMath::DegreesToRadians(currRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Max:\t%f\tCurrent:\t%f"), maxDotProductSum, computeDotProducts(FVector(cos(currRotationRad), sin(currRotationRad), 0.0)));

	
}

float UAsteroidComponent::computeDotProducts(FVector lightDirection, bool ignoreLightDirection)
{
	float ret = 0.;

	UStaticMesh* mesh = this->GetStaticMesh();

	if (mesh)
	{
		check(mesh);
		check(mesh->RenderData);
		check(mesh->RenderData->LODResources.Num());

		const int32 LODIndex = 0;
		FStaticMeshLODResources& LODModel = mesh->RenderData->LODResources[LODIndex];
		FIndexArrayView Indices = LODModel.IndexBuffer.GetArrayView();

		//TArray<AActor*> FoundActors;
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), FoundActors);
		//UE_LOG(LogTemp, Warning, TEXT("Num actors found:%d"), FoundActors.Num());

		//FVector forwardVector = -FoundActors[0]->GetActorForwardVector();
		//FVector sunVector = lightDirection;

		if (mesh->RenderData->LODResources.Num() > 0)
		{

			FStaticMeshVertexBuffers* VertexBuffer = &mesh->RenderData->LODResources[0].VertexBuffers;
			if (VertexBuffer)
			{
				for (unsigned int i = 0; i < VertexBuffer->PositionVertexBuffer.GetNumVertices(); i += 3)
				{
					FVector n1 = VertexBuffer->StaticMeshVertexBuffer.VertexTangentZ(i);
					FVector n2 = VertexBuffer->StaticMeshVertexBuffer.VertexTangentZ(i + 1);
					FVector n3 = VertexBuffer->StaticMeshVertexBuffer.VertexTangentZ(i + 2);

					FVector p1 = VertexBuffer->PositionVertexBuffer.VertexPosition(i);
					FVector p2 = VertexBuffer->PositionVertexBuffer.VertexPosition(i + 1);
					FVector p3 = VertexBuffer->PositionVertexBuffer.VertexPosition(i + 2);

					FVector side1 = p2 - p1;
					FVector side2 = p3 - p1;

					float area = (FVector::CrossProduct(side1, side2).Size())/2;

					FVector triN = (n1 + n2 + n3) / 3.;

					//FVector reflect = sunVector - 2.*(FVector::DotProduct(sunVector, triN))*triN;
					//float cameraret = FVector::DotProduct(reflect, forwardVector);

					if (!ignoreLightDirection)
						ret += area*FMath::Max(0.f, FVector::DotProduct(lightDirection, triN));
						//ret += area * cameraret;
					else
						ret += area*triN.Size();

					//UE_LOG(LogTemp, Warning, TEXT("Triangle %d: %f\t%f\t%f"), i / 3, triN.X, triN.Y, triN.Z);
				}

			}
		}
	}

	return ret;
}