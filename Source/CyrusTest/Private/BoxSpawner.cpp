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
	
	RequestHttp();
}

// Called every frame
void ABoxSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxSpawner::RequestHttp()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Contect-Type"), TEXT("application/json"));
	Request->SetURL("https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json");

	Request->OnProcessRequestComplete().BindLambda(
		[this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
		{
			FString ResponseString = "";

			if (bSuccess)
			{
				ResponseString = Response->GetContentAsString();
				
				HandleRequestCompleted(ResponseString, bSuccess);

			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed Http Request!"));
				return;
			}
		});

	Request->ProcessRequest();
}

void ABoxSpawner::HandleRequestCompleted(const FString& ResponseString, bool bSuccess)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(ResponseString);
	
	TSharedPtr<FJsonObject> obj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, obj))
	{
		UE_LOG(LogTemp, Warning, TEXT("Deserialize"));
		const TArray<TSharedPtr<FJsonValue>>* boxtypes;

		if (obj->TryGetArrayField(TEXT("types"), boxtypes))
		{
			if (!FJsonObjectConverter::JsonArrayToUStruct(*boxtypes, &BoxTypes, 0, 0))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed To Deserialize \"types\""));
				return;
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* objects;

		if (obj->TryGetArrayField(TEXT("objects"), objects))
		{
			if (!FJsonObjectConverter::JsonArrayToUStruct(*objects, &BoxObjects, 0, 0))
			{
				UE_LOG(LogTemp, Error, TEXT("Failed To Deserialize \"objects\""));
				return;
			}
		}
	}

	SpawnBoxes();
}


void ABoxSpawner::SpawnBoxes()
{
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

