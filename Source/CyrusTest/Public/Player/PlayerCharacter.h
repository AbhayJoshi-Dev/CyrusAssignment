// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class AWeapon;
class ACyrusHUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreUpdatedSignature, int32, Score);
//DECLARE_MULTICAST_DELEGATE(FOnScoreUpdated);

UCLASS()
class CYRUSTEST_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	FOnScoreUpdatedSignature OnScoreUpdated;

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnScoreUpdate(int32 Score);

private:

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void FireWeapon(const FInputActionValue& Value);

private:

	/*
	* Components
	*/
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	/*
	*Input 
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponToSpawn;

	UPROPERTY()
	AWeapon* OwnedWeapon;

	int32 PlayerScore;

	UPROPERTY()
	ACyrusHUD* HUD;
};
