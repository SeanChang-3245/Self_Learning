// Fill out your copyright notice in the Description page of Project Settings.


#include "testatomdata.h"
#include <bits/stdc++.h>

using namespace std;

// Sets default values
Atestatomdata::Atestatomdata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Atestatomdata::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Atestatomdata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

string test(int num)
{
	string result;

	FString path = "PeriodicTable.json";
	FString content = "";
	TSharedPtr<FJsonObject> JsonObject;
	
	FFileHelper::LoadFileToString(content, path);

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(content);


	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField("elements");


		TSharedPtr<FJsonValue> atom = objArray[num-1];
		TSharedPtr<FJsonObject> json = atom->AsObject();

		result = json->GetStringField("symbol")


		
		//display
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::FromString(result));








		//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
	}

}


