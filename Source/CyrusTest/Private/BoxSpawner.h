// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiscTypes.h"

#include "BoxSpawner.generated.h"




UCLASS()
class ABoxSpawner : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FBoxType> BoxTypes;

	UPROPERTY()
	TArray<FBoxObject> BoxObjects;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBox> EnemySpawn;

public:	
	// Sets default values for this actor's properties
	ABoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

	void RequestHttp();

	void HandleRequestCompleted(const FString& ResponseString, bool bSuccess);

	void SpawnBoxes();
};
