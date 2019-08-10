// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PrimaryItem.h"
#include "ARPG.h"
#include "PrimaryAI.generated.h"

/**
 * 
 */
UENUM()
enum class EAIType : uint8
{
	NPC,
	Monster
};
class AAIBase;
class USkeletalMesh;
class UAnimInstance;
UCLASS(Abstract)
class ARPG_API UPrimaryAI : public UPrimaryItem
{
	GENERATED_BODY()
public:
	UPrimaryAI();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		FString AIName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		TSubclassOf<AAIBase> AIClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		EAIType AIType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		bool bCanFight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		USkeletalMesh* mMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		TSubclassOf<UAnimInstance> AnimInstaceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI",meta = (EditCondition = "bCanFight"))
		TMap<EEquipmentPart, FPrimaryAssetId> DefaultEquipmentList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (EditCondition = "bCanFight"))
		TMap<EPropertyName, float> Attributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (EditCondition = "bCanFight"))
		float AttackRange;
};
