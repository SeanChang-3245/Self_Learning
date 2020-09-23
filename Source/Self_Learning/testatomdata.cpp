// Fill out your copyright notice in the Description page of Project Settings.


#include "testatomdata.h"
#include <bits/stdc++.h>
#include "Misc/FileHelper.h"

using namespace std;

FString test(int num);


// Sets default values
Atestatomdata::Atestatomdata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Atestatomdata::BeginPlay()
{
	test(1);
	Super::BeginPlay();
	
}

// Called every frame
void Atestatomdata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString test(int num)
{
	FString result;

	FString path = "C:/Users/Sean/source/repos/Self_Learning/Source/Self_Learning/PeriodicTable";
	FString content = "";
	TSharedPtr<FJsonObject> JsonObject;
	
	FFileHelper::LoadFileToString(content, *path);

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(content);


	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField("elements");


		TSharedPtr<FJsonValue> atom = objArray[num-1];
		TSharedPtr<FJsonObject> json = atom->AsObject();

		result = json->GetStringField("symbol");
		int32 tmp = json->GetNumberField("molar_heat");
		
		//display
		//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::FromString(result));
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(tmp));
	}

	return result;

}


