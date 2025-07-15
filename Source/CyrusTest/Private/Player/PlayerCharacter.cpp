// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon/Weapon.h"
#include "UserInterface/CyrusHUD.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());

	PlayerScore = 0;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	OwnedWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponToSpawn);
	OwnedWeapon->SetOwner(this);
	OwnedWeapon->Equip(CameraComponent);

	OwnedWeapon->SetActorRelativeLocation(FVector(60.f, 33.5f, -26.5f));
	OwnedWeapon->SetActorRelativeRotation(FRotator(0.f, -100.f, -5.f));

	HUD = Cast<ACyrusHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	OnScoreUpdated.AddUniqueDynamic(this, &APlayerCharacter::OnScoreUpdate);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedComp->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::FireWeapon);
	}
}

void APlayerCharacter::OnScoreUpdate(int32 Score)
{
	PlayerScore += Score;
	 
	HUD->UpdateScoreWidget(PlayerScore);
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorRightVector(), MovementVector.X);
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void APlayerCharacter::FireWeapon(const FInputActionValue& Value)
{
	if (!OwnedWeapon) return;

	FHitResult Hit;
	FVector Start = CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector();
	FVector End = CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() *20000.f);
	FCollisionQueryParams Params;
	
	FRotator Rotation;
	FVector Target;

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility))
	{
		Target = Hit.Location;
	}
	else
	{
		Target = CameraComponent->GetComponentLocation() + (CameraComponent->GetForwardVector() * 20000.f);
	}

	Start = OwnedWeapon->BulletSpawnPoint->GetComponentLocation();
	Rotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);

	OwnedWeapon->Fire(Rotation);
}

