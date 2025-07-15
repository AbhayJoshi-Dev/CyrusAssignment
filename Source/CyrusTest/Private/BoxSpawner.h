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
	// Sets default values for this actor's properties
	ABoxSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY()
	TArray<FBoxType> BoxTypes;

	UPROPERTY()
	TArray<FBoxObject> BoxObjects;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBox> EnemySpawn;

	UPROPERTY(EditAnywhere)
	FString URL = "https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json";

private:

	void SendHttpRequest();
	void HandleRequestCompleted(const FString& ResponseString);

	bool ParseBoxData(const FString& JsonString);
	void SpawnBoxes();
};
