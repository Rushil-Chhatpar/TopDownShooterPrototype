// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RcTopDownShooterHUD.generated.h"

/**
 * 
 */
UCLASS()
class RCTOPDOWNSHOOTER_API ARcTopDownShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	ARcTopDownShooterHUD();

	UPROPERTY(EditAnywhere, Category = "HUD Class")
		TSubclassOf<class UUserWidget> GUIClass;

	UPROPERTY()
		UUserWidget* PlayerGUI;

protected:
	virtual void BeginPlay() override;

};
