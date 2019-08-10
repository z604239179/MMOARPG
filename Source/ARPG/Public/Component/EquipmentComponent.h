// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARPG.h"
#include "EquipmentComponent.generated.h"

//UENUM()
//enum class EEquipWeaponType :uint8
//{
//	None,
//	SingleHand,
//	TwoHand
//};

class AEquipment; 
class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Replicated)
		TArray< AEquipment*> EquipmentInventory;

	//UPROPERTY(BlueprintReadOnly,Replicated)
	//	TArray<EEquipmentType> CurrentEquipType;


/*	UFUNCTION(Server, Reliable, WithValidation)
		void SpawnAndEquip(TSubclassOf<AEquipment> SpawnClass, FPrimaryAssetId _InId, EEquipmentPart EquipPart);
	*/	//void SpawnAndEquip(TSubclassOf<AEquipment> SpawnClass, EEquipPart EquipPart, EEquipmentType EquipmentType);

	UFUNCTION(Server, Reliable, WithValidation)
		void ServerUnEquip(EEquipmentPart UnEqiupPart);


public:
	
	FORCEINLINE TArray<AEquipment*>& GetEquipmentInventory() { return EquipmentInventory; }
/*
	bool Equip(APickupEquip* InPickupEquip);*/
	UFUNCTION(Server, Reliable, WithValidation)
		void Equip(const FPrimaryAssetId& InId);

	/*卸除装备*/
	void UnEquip(EEquipmentPart UnEqiupPart);


//	EEquipWeaponType CurrentWeaponType;

	AWeapon* GetLWeapon();

	AWeapon* GetRWeapon();

	//FORCEINLINE EEquipmentType GetLWeaponType() { return CurrentEquipType[(int32)EEquipmentPart::Left]; }
	
	//FORCEINLINE EEquipmentType GetRWeaponType() { return CurrentEquipType[(int32)EEquipmentPart::Right]; }

	/*仅能在服务器上执行*/
	void DestroyAllEquipment(float DestroyTime);
};
