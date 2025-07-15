// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"
#include "Components/StaticMeshComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Weapon/BulletProjectile.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponStaticMesh);

	BulletSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	BulletSpawnPoint->SetupAttachment(WeaponStaticMesh);

	RecoilMultiplier = 2.f;
	RecoilLocationMin = -15.f;
	RecoilLocationMax = -8.f;
	RecoilRotationMin = -7.f;
	RecoilRotationMax = -3.5f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	/*ResetRecoilTransform = FTransform(
		FRotator(0.f, -100.f, -5.f),
		FVector(60.f, 33.5f, -26.5f),
		FVector(1.f, 1.f, 1.f)*/
	
	ResetRecoilTransform = FTransform(
		FRotator(0.f, -90.f,0.f),
		FVector(52.5f, 19.5f, -32.5f),
		FVector(1.f, 1.f, 1.f)
	);

	RecoilTransform = FTransform(
		FRotator(0.f, -100.f, -5.f),
		FVector(52.5f, 19.5f, -32.5f),
		FVector(1.f, 1.f, 1.f)
	);
	TargetRecoilTransform = FTransform(
		FRotator(0.f, -100.f, -5.f),
		FVector(52.5f, 19.5f, -32.5f),
		FVector(1.f, 1.f, 1.f)
	);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, TargetRecoilTransform, DeltaTime, 30.f);

	SetActorRelativeTransform(RecoilTransform);

	TargetRecoilTransform = UKismetMathLibrary::TInterpTo(TargetRecoilTransform, ResetRecoilTransform, DeltaTime, 15.f);

}

void AWeapon::Equip(USceneComponent* Comp)
{
	WeaponStaticMesh->AttachToComponent(Comp, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
}

void AWeapon::Fire(FRotator FireRotation)
{
	//spawn projectile

	FActorSpawnParameters Params;
	Params.bNoFail = true;

	ABulletProjectile* B = GetWorld()->SpawnActor<ABulletProjectile>(
		Bullet,
		FTransform(
			FireRotation,
			BulletSpawnPoint->GetComponentLocation(),
			BulletSpawnPoint->GetComponentScale()
		),
		Params
	);

	

	AddRecoil();
}

void AWeapon::AddRecoil()
{
	FVector RecoilLocation = FVector(
		FMath::RandRange(RecoilMultiplier * RecoilLocationMin, RecoilMultiplier * RecoilLocationMax),
		0.f,
		0.f
	);

	FRotator RecoilRotation = FRotator(
		0.f,
		0.f,
		FMath::RandRange(RecoilMultiplier * RecoilRotationMin, RecoilMultiplier * RecoilRotationMax)
	);

	TargetRecoilTransform.SetLocation(TargetRecoilTransform.GetLocation() + RecoilLocation);
	TargetRecoilTransform.SetRotation(FQuat(TargetRecoilTransform.GetRotation().Rotator() + RecoilRotation));
}
