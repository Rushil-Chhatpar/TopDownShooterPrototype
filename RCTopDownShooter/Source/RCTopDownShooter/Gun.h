// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Gun.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
struct FGunMagazine
{
	GENERATED_BODY()

	FGunMagazine():MaxAmmo(30), AmmoCount(30) {}
    FGunMagazine(int maxammo): MaxAmmo(maxammo), AmmoCount(maxammo) {}
	
	int MaxAmmo;
	int AmmoCount;
};
UCLASS()
class RCTOPDOWNSHOOTER_API AGun : public APickup
{
	GENERATED_BODY()
public:
	AGun();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Spawn Point")
		class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category = "Socket Name")
		FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Class")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Max Ammo Per Magazine")
		int Max_Ammo_Per_Magazine;


	FTransform GetProjectileSpawnPointTransform();

	void Equip(class APlayerShooter* Player);
	void UnEquip();

	void Fire();
	void Reload();

	TArray<FGunMagazine*> Magazines;

	void AddMag(int num);

	FGunMagazine* CurrentMag;

	int GetNumofMagazines();
private:
	void SpawnProjectile();

	FGunMagazine* GetFreshMag();



protected:
	virtual void BeginPlay() override;

};
