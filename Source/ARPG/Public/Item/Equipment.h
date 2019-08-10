// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ItemBase.h"
#include "Equipment.generated.h"

UCLASS()
class ARPG_API AEquipment : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* MeshComp;

	UFUNCTION()
		virtual void OnRep_OnEquip() {};
public:	
	UFUNCTION(Client,Reliable)
		virtual void InitEquipment(FPrimaryAssetId EquipInfoId);

	UPROPERTY(ReplicatedUsing = OnRep_OnEquip)
		class ACharacterBase* EquipmentOwner;

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return MeshComp; }

};
