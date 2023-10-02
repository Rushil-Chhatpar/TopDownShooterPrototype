// Fill out your copyright notice in the Description page of Project Settings.


#include "RcTopDownShooterHUD.h"
#include "Blueprint/UserWidget.h"


ARcTopDownShooterHUD::ARcTopDownShooterHUD()
{
}

void ARcTopDownShooterHUD::BeginPlay()
{
    Super::BeginPlay();

    PlayerGUI = CreateWidget<UUserWidget>(GetGameInstance(), GUIClass);

    PlayerGUI->AddToViewport();
    PlayerGUI->SetDesiredSizeInViewport(FVector2D(1000, 1000));
}
