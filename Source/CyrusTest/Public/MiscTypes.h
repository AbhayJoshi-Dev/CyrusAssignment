#pragma once

#include "CoreMinimal.h"
#include "MiscTypes.generated.h"


USTRUCT()
struct FBoxType
{
	GENERATED_BODY()

	UPROPERTY()
	FString Name;
	UPROPERTY()
	TArray<int32> Color;
	UPROPERTY()
	int32 Health;
	UPROPERTY()
	int32 Score;
};

USTRUCT()
struct FTransformData
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<float> Location;
	UPROPERTY()
	TArray<float> Rotation;
	UPROPERTY()
	TArray<float> Scale;
};

USTRUCT()
struct FBoxObject
{
	GENERATED_BODY()

	UPROPERTY()
	FString Type;
	UPROPERTY()
	FTransformData Transform;
};

static FTransform GetTransformFromBoxObject(const FBoxObject& Box)
{
	FTransform T;

	T.SetLocation(
		FVector(
			Box.Transform.Location[0],
			Box.Transform.Location[1],
			Box.Transform.Location[2]
		));

	T.SetRotation(
		FQuat::MakeFromEuler(
			FVector(
				Box.Transform.Rotation[0],
				Box.Transform.Rotation[1],
				Box.Transform.Rotation[2]
			)));

	T.SetScale3D(
		FVector(
			Box.Transform.Scale[0],
			Box.Transform.Scale[1],
			Box.Transform.Scale[2]
		));

	return T;
}
