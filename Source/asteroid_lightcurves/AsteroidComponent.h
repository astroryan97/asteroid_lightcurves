// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "AsteroidComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ASTEROID_LIGHTCURVES_API UAsteroidComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

	UAsteroidComponent();
	UAsteroidComponent(const FObjectInitializer& ObjectInitializer);

	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere)
	float rotationSpeed; //degrees/s

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float computeDotProducts(FVector lightDirection, bool ignoreLightDirection = false);
	float maxDotProductSum;
	float currRotation;
};
