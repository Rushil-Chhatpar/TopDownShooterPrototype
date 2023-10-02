// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShooter.h"

#include "Components/CapsuleComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "RCTopDownShooter/Gun.h"

// Sets default values
AEnemyShooter::AEnemyShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetEnableGravity(false);
	StaticMesh->SetCollisionProfileName("NoCollision");
	StaticMesh->SetupAttachment(GetCapsuleComponent());

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("Pawn Sensing");
	PawnSensing->OnSeePawn.AddDynamic(this, &AEnemyShooter::OnPawnSeen);
	PawnSensing->OnHearNoise.AddDynamic(this, &AEnemyShooter::OnNoiseHeard);
	PawnSensing->SightRadius = 700.0f;
	

	CharacterMovement = GetCharacterMovement();
	CharacterMovement->MaxWalkSpeed = 200.0f;

	Gun = CreateDefaultSubobject<AGun>("Player Weapon");

	this->Tags.Empty();
	this->Tags.Add("Enemy");
}

void AEnemyShooter::TakeDamage(float Damage)
{
	if (Health <= 0)
		return;
	Health -= Damage;

	if (Health <= 0)
	{
		this->Destroy();
	}
}


// Called when the game starts or when spawned
void AEnemyShooter::BeginPlay()
{
    Super::BeginPlay();
	Health = DefaultHealth;
	Controller = GetController();

	Gun->AttachToComponent(StaticMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, Gun->SocketName);

	if (PatrolPoints.Num() != 0)
		CurrentPatrolPoint = PatrolPoints[0];

	if (CurrentPatrolPoint != nullptr)
		Patrol();
}

void AEnemyShooter::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		CharacterMovement->MaxWalkSpeed = 200.0f;
		return;
	}
	if (SeenPawn->ActorHasTag("Enemy"))
		return;

	FVector Location = SeenPawn->GetActorLocation();
	float MovementSpeed = CharacterMovement->MaxWalkSpeed;
	if((Location - GetActorLocation()).Size() <= 500.0f)
	{
		MovementSpeed = 350.0f;
		Gun->Fire();
	}
	else if ((Location - GetActorLocation()).Size() <= PawnSensing->SightRadius)
	{
		MovementSpeed = 250.0f;
		GetWorldTimerManager().ClearTimer(Handle);
		GetWorldTimerManager().SetTimer(Handle, this, &AEnemyShooter::ResetChase, 3.0f);
	}
	
	TargetActor = SeenPawn;


	CharacterMovement->MaxWalkSpeed = MovementSpeed;


}

void AEnemyShooter::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (NoiseInstigator == nullptr)
	{
		CharacterMovement->MaxWalkSpeed = 200.0f;
		return;
	}

	float MovementSpeed = CharacterMovement->MaxWalkSpeed;

	if(Volume == 0.6)
	{
		if ((Location - GetActorLocation()).Size() <= 300.0f)
		{
			MovementSpeed = 350.0f;
		}
		else if ((Location - GetActorLocation()).Size() <= 600.0f)
		{
			MovementSpeed = 250.0f;
			GetWorldTimerManager().ClearTimer(Handle);
			GetWorldTimerManager().SetTimer(Handle, this, &AEnemyShooter::ResetChase, 3.0f);
		}
	}

	TargetActor = NoiseInstigator;

	CharacterMovement->MaxWalkSpeed = MovementSpeed;

}

void AEnemyShooter::Patrol()
{
	if(CurrentPatrolPoint!=nullptr)
	{
		int Index = PatrolPoints.Num() - 1;
		PatrolPoints.Find(CurrentPatrolPoint, Index);
		if (Index == PatrolPoints.Num() - 1)
			CurrentPatrolPoint = PatrolPoints[0];
		else
			CurrentPatrolPoint = PatrolPoints[Index + 1];

		UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, CurrentPatrolPoint);
	}

}

// Called every frame
void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentPatrolPoint != nullptr && TargetActor == nullptr)
	{
		FVector Dist = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
		float Distace = Dist.Size();
		if (Distace < 50.0f)
			Patrol();
	}
	if(TargetActor!=nullptr)
	{
	    if(Controller!=nullptr)
	    {
			UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, TargetActor);
	    }
	}

}

// Called to bind functionality to input
void AEnemyShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyShooter::ResetChase()
{
	TargetActor = nullptr;
	CharacterMovement->MaxWalkSpeed = 200.0f;
	Patrol();

}

