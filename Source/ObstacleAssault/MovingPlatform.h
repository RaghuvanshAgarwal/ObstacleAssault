// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Moving Platform|Locations")
	AActor* StartingPoint;

	UPROPERTY(EditAnywhere, Category = "Moving Platform|Locations")
	AActor* EndingPoint;

	UPROPERTY(EditAnywhere, Category = "Moving Platform|Movement")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category="Moving Platform|Movement")
	float WaitAtLocation = 2.0f;
private:
	FVector StartingLocation;
	FVector EndingLocation;
	float CurrentWaitingTime = 0.0f;
	bool bIsWaiting = false;
};
