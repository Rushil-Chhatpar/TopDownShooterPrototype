// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerVisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RCTOPDOWNSHOOTER_API UPlayerVisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerVisionComponent();

	UPROPERTY(EditAnywhere, Category = "Vision Settings")
		float VisionSphereRadius;

	UPROPERTY(EditAnywhere, Category = "Vision Settings")
		float VisionRange;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void See(FVector Start, class USkeletalMeshComponent* StaticMesh, class AGun* CurrentGun);
		
};
