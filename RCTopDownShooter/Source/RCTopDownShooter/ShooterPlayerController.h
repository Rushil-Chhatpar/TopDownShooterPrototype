// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RCTOPDOWNSHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	class APlayerShooter* Player;
public:
	virtual void Tick(float DeltaSeconds) override;
};
