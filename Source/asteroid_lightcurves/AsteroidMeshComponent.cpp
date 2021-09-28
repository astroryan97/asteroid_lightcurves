// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidMeshComponent.h"

UAsteroidMeshComponent::UAsteroidMeshComponent()
{}

UAsteroidMeshComponent::UAsteroidMeshComponent(const FObjectInitializer& ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	bTickInEditor = true;
}

void UAsteroidMeshComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAsteroidMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UAsteroidMeshComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)

{
	UE_LOG(LogTemp, Warning, TEXT("Chicken nuggets"));
}