// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Damageable.h"
#include "MiscTypes.h"
#include "EnemyBox.generated.h"

UCLASS()
class CYRUSTEST_API AEnemyBox : public AActor,public IDamageable
{
	GENERATED_BODY()

public:

	FString Type;
	FLinearColor Color;
	int32 Health;
	int32 KillScore;

public:	
	// Sets default values for this actor's properties
	AEnemyBox();

	void Init(FBoxType BoxType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DamageTaken(const float Damage) override;

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

};
