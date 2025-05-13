// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartingLocation = StartingPoint->GetActorLocation();
	EndingLocation = EndingPoint->GetActorLocation();
	const FString StartingLog = FString::Printf(TEXT("Starting Location : [%s]"), *StartingLocation.ToString());
	const FString EndingLog = FString::Printf(TEXT("Ending Location : [%s]"), *EndingLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *StartingLog);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *EndingLog);
	SetActorLocation(StartingLocation);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsWaiting)
	{
		if (CurrentWaitingTime < WaitAtLocation)
		{
			CurrentWaitingTime += DeltaTime;
			return;
		}
		bIsWaiting = false;
		CurrentWaitingTime = 0.0f;
		return;
	}
	
	FVector CurrentLocation = GetActorLocation();
	// Check if the distance between us and ending point is less than threshold[100]
	if (FVector::DistSquared(CurrentLocation, EndingLocation) < 100) {
		// Set the location to End Point
		SetActorLocation(EndingLocation);
		UE_LOG(LogTemp,Display, TEXT("Platform Reached End Location of X:%f Y:%f Z:%f"), EndingLocation.X, EndingLocation.Y, EndingLocation.Z);

		// Flip the Start and End point Vectors
		FVector TempLocation = StartingLocation;
		StartingLocation = EndingLocation;
		EndingLocation = TempLocation;
		bIsWaiting = true;
	}
	else {
		// Calculate the direction from our location to end point
		FVector Direction = EndingLocation - CurrentLocation;
		Direction.Normalize();

		// Calculate the change in location using normalized direction and speed
		FVector MovementDelta = Direction * MovementSpeed * DeltaTime;

		// Set the location of our actor
		SetActorLocation(CurrentLocation + MovementDelta);
	}
}

