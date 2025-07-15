// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxSpawner.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonObjectConverter.h"
#include "Enemy/EnemyBox.h"

// Sets default values
ABoxSpawner::ABoxSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoxSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SendHttpRequest();
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxSpawner::SendHttpRequest()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetURL(URL);

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			if (!bSuccess || !Response.IsValid())
			{
				UE_LOG(LogTemp, Error, TEXT("HTTP request failed"));
				return;
			}

			FString ResponseString = Response->GetContentAsString();
				
			HandleRequestCompleted(ResponseString);
		});

	Request->ProcessRequest();
}

void ABoxSpawner::HandleRequestCompleted(const FString& ResponseString)
{
	if (ParseBoxData(ResponseString))
	{
		SpawnBoxes();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse box data"));
	}
}


bool ABoxSpawner::ParseBoxData(const FString& JsonString)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	TSharedPtr<FJsonObject> obj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, obj))
	{
		const TArray<TSharedPtr<FJsonValue>>* boxtypes;

		if (obj->TryGetArrayField(TEXT("types"), boxtypes))
		{
			if (!FJsonObjectConverter::JsonArrayToUStruct(*boxtypes, &BoxTypes, 0, 0))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed To parse \"types\""));
				return false;
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* objects;

		if (obj->TryGetArrayField(TEXT("objects"), objects))
		{
			if (!FJsonObjectConverter::JsonArrayToUStruct(*objects, &BoxObjects, 0, 0))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed To parse \"objects\""));
				return false;
			}
		}
	}
	else 
		UE_LOG(LogTemp, Error, TEXT("Failed To deserialize Json"));

	return true;
}

void ABoxSpawner::SpawnBoxes()
{
	if (!EnemySpawn)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn EnemyBox. Enemy is null"));
		return;
	}

	for (const FBoxObject& BoxObject : BoxObjects)
	{
		FActorSpawnParameters params;
		params.bNoFail = true;

		if (AEnemyBox* SpawnedBox = GetWorld()->SpawnActor<AEnemyBox>(EnemySpawn, GetTransformFromBoxObject(BoxObject), params))
		{
			SpawnedBox->Type = BoxObject.Type;

			FBoxType& Bt = *BoxTypes.FindByPredicate(
				[&SpawnedBox](const FBoxType& BType)
				{
					return SpawnedBox->Type == BType.Name;
				});

			SpawnedBox->Init(Bt);
		}

	}
}

