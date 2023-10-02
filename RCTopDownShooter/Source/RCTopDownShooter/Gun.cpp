// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/ArrowComponent.h"
#include "RCTopDownShooter/PlayerShooter.h"
#include "RCTopDownShooter/Projectile.h"

AGun::AGun()
{
    ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("Projectile Spawn Point");
    ProjectileSpawnPoint->SetupAttachment(RootComponent);

    

    //this->Tags.Empty();
    this->Tags.Add("Gun");
}

FTransform AGun::GetProjectileSpawnPointTransform()
{
    return ProjectileSpawnPoint->GetComponentTransform();
}

void AGun::Equip(class APlayerShooter* Player)
{
    this->DeActivate();
    this->SetActorHiddenInGame(false);
    this->SetOwner(Player);
    this->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
    
    this->SetActorTickEnabled(false);
}

void AGun::UnEquip()
{
    this->DeActivate();
    this->SetOwner(nullptr);
    this->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    this->SetActorTickEnabled(false);
}

void AGun::Fire()
{
    if (CurrentMag->AmmoCount > 0)
        SpawnProjectile();
}

void AGun::Reload()
{
    FGunMagazine* Magazine = GetFreshMag();
    if (Magazine != nullptr)
        CurrentMag = Magazine;
}

int AGun::GetNumofMagazines()
{
    return Magazines.Num();
}

void AGun::SpawnProjectile()
{
    UWorld* World = GetWorld();
    if(World!=nullptr)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = this;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        FTransform STransform = GetProjectileSpawnPointTransform();

        AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, STransform, SpawnParameters);
        FVector Dir = GetActorForwardVector();
        Projectile->SetVelocity(Dir);
        CurrentMag->AmmoCount--;
    }
}

FGunMagazine* AGun::GetFreshMag()
{
    int ammo = 0;
    FGunMagazine* FreshMag = nullptr;
    for (FGunMagazine* Magazine : Magazines)
    {
        if (Magazine->AmmoCount >= ammo)
        {
            FreshMag = Magazine;
            ammo = Magazine->AmmoCount;
        }
    }
    return FreshMag;
}

void AGun::AddMag(int num)
{
    for (int i = 0; i < num; i++)
        Magazines.Add(new FGunMagazine(Max_Ammo_Per_Magazine));
}

void AGun::BeginPlay()
{
    Super::BeginPlay();
    Magazines.Add(new FGunMagazine(Max_Ammo_Per_Magazine));
    Magazines.Add(new FGunMagazine(Max_Ammo_Per_Magazine));
    CurrentMag = GetFreshMag();
}
