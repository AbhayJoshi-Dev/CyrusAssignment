// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BulletProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"
#include "Components/SphereComponent.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	SphereComp->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnHit);
}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SelfDestructTimer, this, &ABulletProjectile::SelfDestruct, 3.f, false);

}

// Called every frame
void ABulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetOwner()) return;

	if (IDamageable* Damageable = Cast<IDamageable>(OtherActor))
	{
		Damageable->DamageTaken(Damage);
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), 5, 32, FColor::Red, false, 1.f);

	SelfDestruct();
}

void ABulletProjectile::SelfDestruct()
{
	Destroy();
}

