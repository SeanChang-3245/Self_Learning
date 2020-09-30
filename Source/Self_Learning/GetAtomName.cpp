// Fill out your copyright notice in the Description page of Project Settings.


#include "GetAtomName.h"
#include "Misc/FileHelper.h"
#include <bits/stdc++.h>

using namespace std;

// Sets default values


FString GetAtomNameString(int num)
{
	//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("test enter func test\n"));


	FString result;

	FString path = FString("C:/Users/Sean/source/repos/Self_Learning/Source/Self_Learning/PeriodicTable.json");
	FString content;
	TSharedPtr<FJsonObject> JsonObject;

	FFileHelper::LoadFileToString(content, *path);


	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(content);


	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField("elements");


		TSharedPtr<FJsonValue> atom = objArray[num - 1];
		TSharedPtr<FJsonObject> json = atom->AsObject();

		result = json->GetStringField("symbol");
		int32 tmp = json->GetNumberField("molar_heat");

		//display
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::FString(result));
		//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(tmp));
		//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("Screen Massage"));
	}

	return result;

}





AGetAtomName::AGetAtomName()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGetAtomName::BeginPlay()
{
	FString k = GetAtomNameString(90);
	
	//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::FString(k));
	
	Super::BeginPlay();
}

// Called every frame
void AGetAtomName::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}






