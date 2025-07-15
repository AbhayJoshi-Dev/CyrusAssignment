// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CyrusHUD.generated.h"

class UScoreWidget;

UCLASS()
class CYRUSTEST_API ACyrusHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	void UpdateScoreWidget(int32 Score);

protected:

	void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UScoreWidget> ScoreWidget;

	UPROPERTY()
	UScoreWidget* SWidget;

};
