// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentComponent.h"
#include "Equipment.h"
#include "CharacterBase.h"
#include "MyAssetManager.h"
#include "Net/UnrealNetwork.h"
// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
	//:CurrentWeaponType(EEquipWeaponType::None)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// ...
	//EquipmentInventory.Init(nullptr, (int32)EEquipmentPart::Max);
	//CurrentEquipType.Init(EEquipmentType::None, (int32)EEquipmentPart::Max);
	//bReplicates = true;

	EquipmentInventory.Init(nullptr, (uint8)EEquipmentPart::Max);
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}







//bool UEquipmentComponent::Equip(TSubclassOf<AEquipment> InEquipment, EEquipPart EquipPart, EEquipmentType EquipmentType)

//bool UEquipmentComponent::Equip(APickupEquip* InPickupEquip)
//{
//	TSubclassOf<AEquipment> SpawnClass = InPickupEquip->ItemInfo->EquipmentClass;
//	SpawnAndEquip(SpawnClass, InPickupEquip->ItemInfo->GetPrimaryAssetId(), InPickupEquip->ItemInfo->EquipPart);
//	return true;
//}


void UEquipmentComponent::Equip_Implementation(const FPrimaryAssetId& InId)
{
	UPrimaryEquip* TempEquip = UMyAssetManager::Get().FindObjectFromId<UPrimaryEquip>(InId);
	if (TempEquip)
	{
		FActorSpawnParameters TempParam;
		TempParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		TempParam.Owner = GetOwner();
		AEquipment* EquipActor = GetWorld()->SpawnActor<AEquipment>(TempEquip->EquipmentClass, GetOwner()->GetTransform(), TempParam);
		EquipActor->InitEquipment(InId);
		EquipmentInventory[(uint8)TempEquip->EquipPart] = EquipActor;
		switch (TempEquip->EquipPart)
		{
		case EEquipmentPart::Head:
			break;
		case EEquipmentPart::Armor:
			break;
		case EEquipmentPart::Pant:
			break;
		case EEquipmentPart::Shoes:
			break;
		case EEquipmentPart::Left:
			EquipActor->AttachToComponent(Cast<ACharacterBase>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("LWeapon"));
			break;
		case EEquipmentPart::Right:
			EquipActor->AttachToComponent(Cast<ACharacterBase>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RWeapon"));
			break;
		default:
			break;
		}
	}
}
bool UEquipmentComponent::Equip_Validate(const FPrimaryAssetId& InId)
{
	return true;
}


//bool UEquipmentComponent::Equip(TSubclassOf<AWeapon> InEquipment, EEquipmentType EquipmentType, EEquipWeaponType EquipWeaonType)
//{
//	SpawnAndEquip(InEquipment,)
//}

void UEquipmentComponent::UnEquip(EEquipmentPart UnEqiupPart)
{
	if (EquipmentInventory[(uint8)UnEqiupPart])
	{
		ServerUnEquip(UnEqiupPart);
	}
}

AWeapon* UEquipmentComponent::GetLWeapon()
{
	return Cast<AWeapon>(EquipmentInventory[(uint8)EEquipmentPart::Left]);
}

AWeapon* UEquipmentComponent::GetRWeapon()
{
	return Cast<AWeapon>(EquipmentInventory[(uint8)EEquipmentPart::Right]);
}

void UEquipmentComponent::DestroyAllEquipment(float DestroyTime)
{


	for (int32 it = 0; it < EquipmentInventory.Num(); ++it)
	{
		if (EquipmentInventory[(uint8)(EEquipmentPart)it])
		{
			EquipmentInventory[(uint8)(EEquipmentPart)it]->SetLifeSpan(DestroyTime);
			EquipmentInventory[(uint8)(EEquipmentPart)it] = nullptr;
		}
	}
}

void UEquipmentComponent::ServerUnEquip_Implementation(EEquipmentPart UnEqiupPart)
{
	if (EquipmentInventory[(uint8)UnEqiupPart])
	{
		EquipmentInventory[(uint8)UnEqiupPart]->Destroy();
		EquipmentInventory[(uint8)UnEqiupPart] = nullptr;
	}

}

bool UEquipmentComponent::ServerUnEquip_Validate(EEquipmentPart UnEqiupPart)
{
	return true;
}


//void UEquipmentComponent::SpawnAndEquip_Implementation(TSubclassOf<AEquipment> SpawnClass,FPrimaryAssetId _InId,EEquipmentPart EquipPart)
//{
//	if (SpawnClass)
//	{
//		FActorSpawnParameters TempParam;
//		TempParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//		TempParam.Owner = GetOwner();
//		AEquipment* EquipActor = GetWorld()->SpawnActor<AEquipment>(SpawnClass, GetOwner()->GetTransform(), TempParam);
//		EquipActor->InitEquipment(_InId);
//			EquipmentInventory[(uint8)EquipPart] = EquipActor;
//			//CurrentEquipType[(int32)EquipPart] = EquipmentType;
//			//MulticastEquip(EquipPart);
//			switch (EquipPart)
//			{
//			case EEquipmentPart::Head:
//				break;
//			case EEquipmentPart::Armor:
//				break;
//			case EEquipmentPart::Pant:
//				break;
//			case EEquipmentPart::Shoes:
//				break;
//			case EEquipmentPart::Left:
//				EquipmentInventory[(uint8)EquipPart]->AttachToComponent(Cast<ACharacterBase>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("LWeapon"));
//				break;
//			case EEquipmentPart::Right:
//				EquipmentInventory[(uint8)EquipPart]->AttachToComponent(Cast<ACharacterBase>(GetOwner())->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("RWeapon"));
//				break;
//			default:
//				break;
//			
//		}
//	}
//	
//}
//
//bool UEquipmentComponent::SpawnAndEquip_Validate(TSubclassOf<AEquipment> SpawnClass, FPrimaryAssetId _InId, EEquipmentPart EquipPart)
//{
//	return true;
//}







void UEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UEquipmentComponent, EquipmentInventory);
	//DOREPLIFETIME(UEquipmentComponent, CurrentEquipType);
}
