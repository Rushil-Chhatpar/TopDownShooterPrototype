// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RCTopDownShooterGameState.generated.h"

/**
 * 
 */
UCLASS()
class RCTOPDOWNSHOOTER_API ARCTopDownShooterGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ARCTopDownShooterGameState();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int GetAmmoCount();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int GetMagazineCount();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealth();

	void SetAmmoCount(int ammo);
	void SetMagazineCount(int mag);
	void SetHealth(float health);

private:
	int Ammo;
	int MagCount;
	float Health;

};
