// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "RCTopDownShooter/Gun.h"
#include "RCTopDownShooter/PlayerShooter.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::AddToInventory(APickup* NewItem)
{
	Inventory.AddUnique(NewItem);

	NewItem->DeActivate();
}

void UInventory::NextInventoryItem()
{
	SelectInventoryItem(EInventoryDir::NEXT);
}

void UInventory::PreviousInventoryItem()
{
	SelectInventoryItem(EInventoryDir::PREV);
}

void UInventory::EquipNewItem(APickup* NewItem)
{
	if(CurrentInventoryItem!=nullptr)
	{
		CurrentInventoryItem->DeActivate();
		CurrentInventoryItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	if(NewItem!=nullptr)
	{
		NewItem->Activate();
		APlayerShooter* Player = Cast<APlayerShooter>(GetOwner());
		if(NewItem->GetClass() == AGun::StaticClass())
		{
			AGun* Gun = Cast<AGun>(NewItem);
			Gun->Equip(Player);
		}
	}

	CurrentInventoryItem = NewItem;
}

void UInventory::SelectInventoryItem(EInventoryDir Dir)
{
	if (Inventory.Num() == 0)
		return;

	APickup* ItemtoEquip = nullptr;
	int32 Index;
	if (Dir == EInventoryDir::NEXT)
		Index = 0;
	else
		Index = Inventory.Num() - 1;

	if(CurrentInventoryItem!=nullptr)
	{
		Inventory.Find(CurrentInventoryItem, Index);
		if (Dir == EInventoryDir::NEXT)
			Index++;
		else
			Index--;
	}

	if(Index>=0 && Index<Inventory.Num())
	{
		ItemtoEquip = Inventory[Index];
	}
	EquipNewItem(ItemtoEquip);

}

