// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "RCTopDownShooter/EnemyShooter.h"
#include "RCTopDownShooter/PlayerShooter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>("Collider");
	Collider->SetCollisionProfileName("BlockAllDynamic");
	Collider->SetSimulatePhysics(false);
	Collider->InitSphereRadius(10.0f);
	Collider->SetNotifyRigidBodyCollision(true);
	Collider->SetEnableGravity(false);
	SetRootComponent(Collider);

	Collider->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetupAttachment(Collider);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetEnableGravity(false);

	InitialSpeed = 700.0f;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->UpdatedComponent = Collider;
	InitialLifeSpan = 5.0f;

	bIsPlayerProjectile = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetVelocity(FVector Velocity)
{
	ProjectileMovement->Velocity = Velocity * InitialSpeed;
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(bIsPlayerProjectile == true)
	{
	    if(OtherActor!=nullptr)
	    {
			if(OtherActor->ActorHasTag("Enemy"))
			{
				AEnemyShooter* Enemy = Cast<AEnemyShooter>(OtherActor);
				Enemy->TakeDamage(Damage);
			}
	    }
	}
	else
	{
	    if(OtherActor!=nullptr)
	    {
	        if(OtherActor->ActorHasTag("Player"))
	        {
				APlayerShooter* Player = Cast<APlayerShooter>(OtherActor);
				Player->TakeDamage(Damage);
	        }
	    }
	}
	Destroy();
}



