// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UStaticMeshComponent;
class ABulletProjectile;

UCLASS()
class CYRUSTEST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BulletSpawnPoint;

public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Equip(USceneComponent* Comp);

	void Fire(FRotator FireRotation);

private:

	void AddRecoil();

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WeaponStaticMesh;


	FTransform TargetRecoilTransform;

	FTransform RecoilTransform;

	FTransform ResetRecoilTransform;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	double RecoilMultiplier;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	double RecoilLocationMin;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	double RecoilLocationMax;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	double RecoilRotationMin;

	UPROPERTY(EditAnywhere, Category = "Recoil")
	double RecoilRotationMax;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABulletProjectile> Bullet;
};
