// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "AsteroidMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class ASTEROID_LIGHTCURVES_API UAsteroidMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UAsteroidMeshComponent();
	UAsteroidMeshComponent(const FObjectInitializer& ObjectInitializer);

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
