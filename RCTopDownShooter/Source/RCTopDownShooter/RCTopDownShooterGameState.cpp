// Fill out your copyright notice in the Description page of Project Settings.


#include "RCTopDownShooterGameState.h"

ARCTopDownShooterGameState::ARCTopDownShooterGameState()
{
}
int ARCTopDownShooterGameState::GetAmmoCount()
{
    return Ammo;
}

int ARCTopDownShooterGameState::GetMagazineCount()
{
    return MagCount;
}

float ARCTopDownShooterGameState::GetHealth()
{
    return Health;
}

void ARCTopDownShooterGameState::SetAmmoCount(int ammo)
{
    Ammo = ammo;
}

void ARCTopDownShooterGameState::SetMagazineCount(int mag)
{
    MagCount = mag;
}

void ARCTopDownShooterGameState::SetHealth(float health)
{
    Health = health;
}

