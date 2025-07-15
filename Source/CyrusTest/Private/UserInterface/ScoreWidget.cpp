// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore(int32 Score)
{
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
}

void UScoreWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	
}
