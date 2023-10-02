// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerShooter.h"

#include "Inventory.h"
#include "Pickup.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RCTopDownShooter/Gun.h"
#include "RCTopDownShooter/Ammo.h"
#include "EngineUtils.h"
#include "PlayerVisionComponent.h"
#include "RCTopDownShooter/EnemyShooter.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "RCTopDownShooter/RCTopDownShooterGameMode.h"
#include "RCTopDownShooter/RCTopDownShooterGameState.h"



// Sets default values
APlayerShooter::APlayerShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 100.0f);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetEnableGravity(false);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetupAttachment(GetCapsuleComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SocketOffset = FVector(0, 0, 300.0f);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bDoCollisionTest = true;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 0.5f;
	SpringArm->ProbeSize = 50.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeRotation(FRotator(-75.0f, 0.0f, 0.0f));
	Camera->FieldOfView = 120.0f;
	Camera->ProjectionMode = ECameraProjectionMode::Perspective;

	PickupCollider = CreateDefaultSubobject<USphereComponent>("Pickup Sphere");
	PickupCollider->InitSphereRadius(60.0f);
	PickupCollider->SetCollisionProfileName("OverlapAll");
	PickupCollider->SetupAttachment(GetCapsuleComponent());

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>("Noise Emitter");

	Inventory = CreateDefaultSubobject<UInventory>("Inventory");
	ScrollDir = EScrollDir::SD_UP;

	PlayerVision = CreateDefaultSubobject<UPlayerVisionComponent>("Player Vision");
	PlayerVision->VisionSphereRadius = 400.0f;
	PlayerVision->VisionRange = 400.0f;

	SpawnPoint = FVector::ZeroVector;

	this->Tags.Empty();
	this->Tags.Add("Player");
}

bool APlayerShooter::bHasGameWon()
{
	int c = 0;
	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		if (Actor->ActorHasTag("Enemy"))
			c++;
	}

	if (c == 0)
		return true;
	return false;
}

// Called when the game starts or when spawned
void APlayerShooter::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
}

// Called every frame
void APlayerShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//TArray<FHitResult> Hits;
	//FVector StartLocation = GetActorLocation();
	//FVector EndLocation = GetActorLocation() + (StaticMesh->GetForwardVector() * 400.0f);
	//FCollisionShape Sphere = FCollisionShape::MakeSphere(VisionSphereRadius);
	//bool isHit = GetWorld()->SweepMultiByChannel(Hits, StartLocation, EndLocation, FQuat::Identity, ECC_WorldDynamic, Sphere);

	//for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor) 
	//{
	//	if ((Actor->ActorHasTag("Gun") && Cast<AGun>(*Actor) != CurrentGun) || Actor->ActorHasTag("Ammo") || Actor->ActorHasTag("Enemy"))
	//	{
	//		Actor->SetActorHiddenInGame(true);
	//	}
	//}
	//
	//if(isHit == true)
	//{
	//    for(FHitResult& Hit: Hits)
	//    {
	//		if (Hit.Actor != nullptr)
	//		{
	//			if (Hit.Actor->ActorHasTag("Gun") || Hit.Actor->ActorHasTag("Ammo") || Hit.Actor->ActorHasTag("Enemy"))
	//			{
	//				Hit.Actor->SetActorHiddenInGame(false);	
	//			}
	//		}
	//    }
	//}

	PlayerVision->See(GetActorLocation(), GetMesh(), CurrentGun);

    ARCTopDownShooterGameMode* GameMode = Cast<ARCTopDownShooterGameMode>(GetWorld()->GetAuthGameMode());
    ARCTopDownShooterGameState* GameState = GameMode->GetGameState<ARCTopDownShooterGameState>();
	if(CurrentGun!=nullptr)
	{
		GameState->SetAmmoCount(CurrentGun->CurrentMag->AmmoCount);
		GameState->SetMagazineCount(CurrentGun->GetNumofMagazines());
	}
	else
	{
		GameState->SetAmmoCount(0);
		GameState->SetMagazineCount(0);
	}

	GameState->SetHealth(Health);

}

// Called to bind functionality to input
void APlayerShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void APlayerShooter::MoveForward(float value)
{
	if (SprintScalar == 1)
	{
		AddMovementInput(GetActorForwardVector(), value);
		MakeNoise(0.6, this, GetActorLocation());
	}
	else
		AddMovementInput(GetActorForwardVector(), value / 2);
}

void APlayerShooter::MoveRight(float value)
{
	if (SprintScalar == 1)
	{
		AddMovementInput(GetActorRightVector(), value);
		MakeNoise(0.6, this, GetActorLocation());
	}
	else
		AddMovementInput(GetActorRightVector(), value / 2);
}

void APlayerShooter::Sprint(float value)
{
	SprintScalar = value;
}

void APlayerShooter::Pickup()
{
	TArray<AActor*> overlappingActors;

	PickupCollider->GetOverlappingActors(overlappingActors, APickup::StaticClass());

	for (AActor* Actor : overlappingActors)
	{
	    if(Actor->ActorHasTag("Gun"))
	    {
			Inventory->AddToInventory(Cast<APickup>(Actor));
	    }
		else if(Actor->ActorHasTag("Ammo"))
		{
			if (CurrentGun != nullptr)
				CurrentGun->AddMag(1);
		}
	}
}

void APlayerShooter::CycleWeapons(float value)
{
	if(value == 1)
	{
		EquipFromInventory(EScrollDir::SD_UP);
	}
	else if(value == -1)
	{
		EquipFromInventory(EScrollDir::SD_DOWN);
	}
}

void APlayerShooter::Shoot()
{
	if(CurrentGun!=nullptr)
	{
		CurrentGun->Fire();
	}
}

void APlayerShooter::Reload()
{
	if(CurrentGun!=nullptr)
	{
		CurrentGun->Reload();
	}
}

void APlayerShooter::SetResultRotator(FRotator Rot)
{
	this->GetMesh()->SetWorldRotation(FRotator(0, Rot.Yaw - 90.0f, 0));
	//StaticMesh->SetWorldRotation(FRotator(0, Rot.Yaw, 0));
}

void APlayerShooter::TakeDamage(float Damage)
{
	//if (Health <= 0)
	//	return;
	Health -= Damage;

	if (Health <= 0)
	{
		ARCTopDownShooterGameMode* GameMode = Cast<ARCTopDownShooterGameMode>(GetWorld()->GetAuthGameMode());
		GameMode->CheckDeath(this);
		for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
		{
			if (Actor->ActorHasTag("Enemy"))
			{
				AEnemyShooter* Enemy = Cast<AEnemyShooter>(*Actor);
				Enemy->ResetChase();
			}
		}
	}
}

void APlayerShooter::SetSpawnPoint(FVector Spawn)
{
	SpawnPoint = Spawn;
}

FVector APlayerShooter::GetSpawnPoint()
{
	return SpawnPoint;
}

void APlayerShooter::EquipFromInventory(EScrollDir Dir)
{
	if(CurrentGun!=nullptr)
	{
		CurrentGun->UnEquip();
	}
	if (Dir == EScrollDir::SD_UP)
		Inventory->NextInventoryItem();
	else
		Inventory->PreviousInventoryItem();

	CurrentGun = Cast<AGun>(Inventory->CurrentInventoryItem);

	if (CurrentGun != nullptr)
	{
		CurrentGun->Equip(this);
	}
}

void APlayerShooter::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor!=nullptr)
	{
	    if(OtherActor->ActorHasTag("Ammo"))
	    {
			AAmmo* ammo = Cast<AAmmo>(OtherActor);
			if(CurrentGun!=nullptr)
			{
				CurrentGun->AddMag(ammo->MagazineCount);
				ammo->Destroy();
			}
	    }
	}
}
