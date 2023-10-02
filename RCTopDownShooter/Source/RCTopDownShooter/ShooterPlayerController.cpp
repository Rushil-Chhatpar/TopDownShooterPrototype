// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "RCTopDownShooter/PlayerShooter.h"

void AShooterPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    Player = Cast<APlayerShooter>(InPawn);
    InputComponent->BindAxis("Move Forward", Player, &APlayerShooter::MoveForward);
    InputComponent->BindAxis("Move Right", Player, &APlayerShooter::MoveRight);
    InputComponent->BindAxis("Sprint", Player, &APlayerShooter::Sprint);

    InputComponent->BindAction("Jump", IE_Pressed, Player, &ACharacter::Jump);
    InputComponent->BindAction("Jump", IE_Released, Player, &ACharacter::StopJumping);

    InputComponent->BindAction("Pickup", IE_Pressed, Player, &APlayerShooter::Pickup);
    InputComponent->BindAxis("Cycle Weapons", Player, &APlayerShooter::CycleWeapons);
    InputComponent->BindAction("Shoot", IE_Pressed, Player, &APlayerShooter::Shoot);
    InputComponent->BindAction("Reload", IE_Pressed, Player, &APlayerShooter::Reload);

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    
    
}

void AShooterPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void AShooterPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    FHitResult Hit;
    GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, Hit);
    if (this->GetCharacter() != nullptr)
    {
        FVector PlayerPos = this->GetCharacter()->GetActorLocation();
        FRotator PlayerRot = FRotationMatrix::MakeFromX(Hit.Location - PlayerPos).Rotator();
        Player->SetResultRotator(PlayerRot);
    }
}
