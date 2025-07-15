// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBox.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AEnemyBox::AEnemyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
}

void AEnemyBox::Init(FBoxType BoxType)
{
	Color = FLinearColor(BoxType.Color[0], BoxType.Color[1], BoxType.Color[2]);
	Health = BoxType.Health;
	KillScore = BoxType.Score;



	UMaterialInterface* MI = StaticMeshComponent->GetMaterial(0);
	UMaterialInstanceDynamic* dynamic = UMaterialInstanceDynamic::Create(MI, StaticMeshComponent);
	dynamic->SetVectorParameterValue("Color", Color);
	StaticMeshComponent->SetMaterial(0, dynamic);
}

// Called when the game starts or when spawned
void AEnemyBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#include "Player/PlayerCharacter.h"

void AEnemyBox::DamageTaken(const float Damage)
{
	Health -= Damage;

	if (Health <= 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Enemy Died"));

		APlayerCharacter* Character = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
		Character->OnScoreUpdated.Broadcast(KillScore);

		Destroy();
	}
}

