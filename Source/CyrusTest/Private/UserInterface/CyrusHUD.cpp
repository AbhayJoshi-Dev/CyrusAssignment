// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/CyrusHUD.h"
#include "UserInterface/ScoreWidget.h"

void ACyrusHUD::UpdateScoreWidget(int32 Score)
{
	SWidget->UpdateScore(Score);
}

void ACyrusHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidget)
	{
		SWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidget);
		SWidget->AddToViewport();
	}
}
