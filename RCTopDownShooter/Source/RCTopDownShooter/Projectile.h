// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class RCTOPDOWNSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Movement Component")
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Projectile Speed")
		float InitialSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Is a Player Projectile")
		bool bIsPlayerProjectile;

	UPROPERTY(EditDefaultsOnly, Category = "Damage Value")
		float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetVelocity(FVector Velocity);

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
