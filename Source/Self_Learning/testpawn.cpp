// Fill out your copyright notice in the Description page of Project Settings.


#include "testpawn.h"

// Sets default values
Atestpawn::Atestpawn()
{
	UE_LOG(LogTemp, Warning, TEXT("MyCharacter's second is f"));


	this->SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshz"));
	//this->SphereMesh->AttachTo(GetRootComponent());
	this->SetRootComponent(this->SphereMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	this->SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
}

// Called when the game starts or when spawned
void Atestpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Atestpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Atestpawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

