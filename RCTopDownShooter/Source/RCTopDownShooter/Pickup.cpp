// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Components/SphereComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	SetRootComponent(Collider);
	Collider->InitSphereRadius(20.0f);
	Collider->SetCollisionProfileName("OverlapAll");
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetSimulatePhysics(false);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetupAttachment(Collider);

	this->Tags.Empty();
	this->Tags.Add("Pickup");

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//StaticMesh->AddRelativeRotation(FRotator(0.0f, DeltaTime * 50.0f, 0.0f));

}

void APickup::Activate()
{
	if(StaticMesh!=nullptr)
	{
		this->SetActorHiddenInGame(false);
		Collider->SetActive(true);
		Collider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void APickup::DeActivate()
{
	if(StaticMesh!= nullptr)
	{
		this->SetActorHiddenInGame(true);
		Collider->SetActive(false);
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}



//TO DO - DISABLE TICK ON PICKUP