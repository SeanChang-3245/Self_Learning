// Fill out your copyright notice in the Description page of Project Settings.

#include "HttpActor.h"
#include "Self_Learning.h"
#include <bits/stdc++.h>

using namespace std;



struct coordinate
{
	double x;
	double y;
	double z;
};

struct bonds
{
	int aid_1;
	int aid_2;
	int order;

};

class conformer_create
{
public:
	vector<int> ele_id;
	vector<coordinate> pos;
	vector<bonds> ele_bond;
};




// Sets default values
AHttpActor::AHttpActor()
{
	//When the object is constructed, Get the HTTP module
	Http = &FHttpModule::Get();
}

// Called when the game starts or when spawned
void AHttpActor::BeginPlay()
{
	MyHttpCall();
	Super::BeginPlay();
}

/*Http call*/
void AHttpActor::MyHttpCall()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpActor::OnResponseReceived);
	//This is the url on which to process the request
	Request->SetURL("https://pubchem.ncbi.nlm.nih.gov/rest/pug/compound/CID/702/record/JSON/?record_type=3d&response_type=display");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

/*Assigned function on successfull http call*/
void AHttpActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		TSharedPtr<FJsonValue> fault = JsonObject->TryGetField("Fault");

		if (fault == nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("got data1\n"));
			conformer_create con;


			//Get the value of the json object by field name
			TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField("PC_Compounds");


			int32 cid = 280;




			TSharedPtr<FJsonValue> value = objArray[0];
			TSharedPtr<FJsonObject> json = value->AsObject();



			TArray<TSharedPtr<FJsonValue>> ele_num = json->GetArrayField("element"); //≠Ï§lß«
			for (int i = 0; i < ele_num.Num(); ++i)
			{
				con.ele_id.push_back((int)(ele_num[i]->AsNumber()));
			}



			TSharedPtr<FJsonObject> bond = json->GetObjectField("bonds");
			TArray<TSharedPtr<FJsonValue>> aid1 = bond->GetArrayField("aid1");
			TArray<TSharedPtr<FJsonValue>> aid2 = bond->GetArrayField("aid2");
			TArray<TSharedPtr<FJsonValue>> bond_num = bond->GetArrayField("order");   // ¡‰
			for (int i = 0; i < aid1.Num(); ++i)
			{
				bonds tmp;
				tmp.aid_1 = (int)aid1[i]->AsNumber();
				tmp.aid_2 = (int)aid2[i]->AsNumber();
				tmp.order = (int)bond_num[i]->AsNumber();
				con.ele_bond.push_back(tmp);
			}




			TArray<TSharedPtr<FJsonValue>> coor = json->GetArrayField("coords");
			TSharedPtr<FJsonObject> coord = coor[0]->AsObject();
			TArray<TSharedPtr<FJsonValue>> conform = coord->GetArrayField("conformers");
			TSharedPtr<FJsonObject> conformer = conform[0]->AsObject();
			TArray<TSharedPtr<FJsonValue>> xa = conformer->GetArrayField("x");
			TArray<TSharedPtr<FJsonValue>> ya = conformer->GetArrayField("y");
			TArray<TSharedPtr<FJsonValue>> za = conformer->GetArrayField("z");
			for (int i = 0; i < xa.Num(); ++i)
			{
				coordinate tmp;
				tmp.x = xa[i]->AsNumber();
				tmp.y = ya[i]->AsNumber();
				tmp.z = za[i]->AsNumber();
				con.pos.push_back(tmp);
			}


			//display
			//GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::FromInt(cid));
			//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("got data2\n"));
			if(con.ele_id[0])
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, FString::FromInt(cid));
			//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, FString::FromInt(recievedInt));
			//UE_LOG(LogTemp, Warning, TEXT("Text, %lf"), con.pos[2].z);
			//GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("got data %d \n"), (int)con.pos[2].z);


		}
		else
		{
			GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, TEXT("error12345\n"));
		}


		
	}
}





