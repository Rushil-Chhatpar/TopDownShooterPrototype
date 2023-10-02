// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyShooter.generated.h"

UCLASS()
class RCTOPDOWNSHOOTER_API AEnemyShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyShooter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Static Mesh")
		class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		class AGun* Gun;

	UPROPERTY(EditInstanceOnly, Category = "Patrol Points")
		TArray<AActor*> PatrolPoints;

	AActor* CurrentPatrolPoint;

	UFUNCTION()
		void Patrol();

	UPROPERTY(VisibleAnywhere, Category = "Pawn Sensing Component")
		class UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Health")
		float DefaultHealth;

	float Health;

	void TakeDamage(float Damage);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UCharacterMovementComponent* CharacterMovement;

	AActor* TargetActor;

	FTimerHandle Handle;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void ResetChase();

private:
	AActor* Player;
	AController* Controller;
};