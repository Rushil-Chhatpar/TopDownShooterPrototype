// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

#include "Components/BoxComponent.h"
#include "RCTopDownShooter/PlayerShooter.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetEnableGravity(false);
	StaticMesh->SetCollisionProfileName("NoCollision");

	Collider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetCollisionProfileName("OverlapAll");
	Collider->SetEnableGravity(false);
	Collider->InitBoxExtent(FVector(20.0f, 20.0f, 100.0f));

	SetRootComponent(Collider);
	StaticMesh->SetupAttachment(Collider);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnBeginOverlap);

	this->Tags.Empty();
	this->Tags.Add("Checkpoint");
    
}

void ACheckpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor!=nullptr)
	{
	    if(OtherActor->ActorHasTag("Player"))
	    {
			APlayerShooter* Player = Cast<APlayerShooter>(OtherActor);
			Player->SetSpawnPoint(GetActorLocation());
	    }
	}
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

