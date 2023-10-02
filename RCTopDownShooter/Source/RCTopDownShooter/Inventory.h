// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UENUM(BlueprintType)
enum class EInventoryDir : uint8
{
    NEXT  UMETA(DisplayName = "NEXT"),
	PREV  UMETA(DisplayName = "PREV"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RCTOPDOWNSHOOTER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Array")
		TArray<class APickup*> Inventory;

	void AddToInventory(APickup* NewItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory Cycle")
		void NextInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Inventory Cycle")
		void PreviousInventoryItem();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory Cycle")
		APickup* CurrentInventoryItem;

	void EquipNewItem(APickup* NewItem);

	void SelectInventoryItem(EInventoryDir Dir);
		
};
