// Fill out your copyright notice in the Description page of Project Settings.


#include "RCTopDownShooterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "RCTopDownShooter/PlayerShooter.h"


void ARCTopDownShooterGameMode::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);



    //for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
    //{
    //    if(Actor->GetClass() == APlayerShooter::StaticClass())
    //    {
    //        APlayerShooter* Player = Cast<APlayerShooter>(*Actor);
    //        CheckDeath(Player);
    //    }

    //}


}

void ARCTopDownShooterGameMode::BeginPlay()
{
    Super::BeginPlay();


}

void ARCTopDownShooterGameMode::CheckDeath(APlayerShooter* Player)
{
    if(Player->Health <=0)
    {
        Player->Health = Player->DefaultHealth;
        if(Player->SpawnPoint == FVector::ZeroVector)
        {
            for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
            {
                if(Actor->ActorHasTag("Checkpoint"))
                {
                    Player->SetActorLocation(Actor->GetActorLocation());
                }
            }
        }
        else
        {
            Player->SetActorLocation(Player->SpawnPoint);
        }
    }


}
