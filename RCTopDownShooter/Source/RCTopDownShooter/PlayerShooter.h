// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerShooter.generated.h"

UENUM(BlueprintType)
enum class EScrollDir : uint8
{
    SD_UP UMETA(DisplayName = "UP"),
	SD_DOWN UMETA(DisplayName = "DOWN"),
};
UCLASS()
class RCTOPDOWNSHOOTER_API APlayerShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerShooter();

	//ACharacter has static mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
		class UStaticMeshComponent* StaticMesh;

	//dont need collider cuz character has its own

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spring Arm")
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Collider")
		class USphereComponent* PickupCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class UInventory* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		EScrollDir ScrollDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vision")
		class UPlayerVisionComponent* PlayerVision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Noise Emitter")
		class UPawnNoiseEmitterComponent* NoiseEmitter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Health")
		float DefaultHealth;

    float Health;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Point")
        FVector SpawnPoint;

	UFUNCTION(BlueprintCallable)
		bool bHasGameWon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AGun* CurrentGun;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void Sprint(float value);

	void Pickup();
	void CycleWeapons(float value);
	void Shoot();
	void Reload();

	float SprintScalar;

	void SetResultRotator(FRotator Rot);

	void TakeDamage(float Damage);

	void SetSpawnPoint(FVector Spawn);

	UFUNCTION()
		FVector GetSpawnPoint();

private:
	void EquipFromInventory(EScrollDir Dir);

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};



