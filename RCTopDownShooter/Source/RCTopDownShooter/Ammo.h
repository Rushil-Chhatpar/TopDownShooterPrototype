// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Ammo.generated.h"

/**
 * 
 */
UCLASS()
class RCTOPDOWNSHOOTER_API AAmmo : public APickup
{
	GENERATED_BODY()

public:
	AAmmo();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magazine Count")
		int MagazineCount;
};
