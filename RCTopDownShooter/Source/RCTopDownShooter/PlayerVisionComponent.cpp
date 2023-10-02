// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerVisionComponent.h"
#include  "EngineUtils.h"
#include "RCTopDownShooter/Gun.h"

// Sets default values for this component's properties
UPlayerVisionComponent::UPlayerVisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerVisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerVisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerVisionComponent::See(FVector Start, USkeletalMeshComponent* StaticMesh, AGun* CurrentGun)
{
	TArray<FHitResult> Hits;
	FVector EndLocation = Start + (StaticMesh->GetForwardVector().RotateAngleAxis(                                                    90.0f, FVector(0,0,1)) * VisionRange);
	//EndLocation = EndLocation.RotateAngleAxis(-90.0f, FVector(0, 0, 1));
	FCollisionShape Sphere = FCollisionShape::MakeSphere(VisionSphereRadius);
	bool isHit = GetWorld()->SweepMultiByChannel(Hits, Start, EndLocation, FQuat::Identity, ECC_WorldDynamic, Sphere);

	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		if ((Actor->ActorHasTag("Gun") && Cast<AGun>(*Actor) != CurrentGun) || Actor->ActorHasTag("Ammo") || Actor->ActorHasTag("Enemy"))
		{
			Actor->SetActorHiddenInGame(true);
		}
	}

	if (isHit == true)
	{
		for (FHitResult& Hit : Hits)
		{
			if (Hit.Actor != nullptr)
			{
				if (Hit.Actor->ActorHasTag("Gun") || Hit.Actor->ActorHasTag("Ammo") || Hit.Actor->ActorHasTag("Enemy"))
				{
					Hit.Actor->SetActorHiddenInGame(false);
				}
			}
		}
	}
}

