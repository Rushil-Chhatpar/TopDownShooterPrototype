// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RCTopDownShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RCTOPDOWNSHOOTER_API ARCTopDownShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	void CheckDeath(class APlayerShooter* Player);
protected:
	virtual void BeginPlay() override;
};
