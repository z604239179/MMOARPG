// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PrimaryItem.generated.h"

/**
 * 
 */

UCLASS(Abstract)
class ARPG_API UPrimaryItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Item")
		FPrimaryAssetType m_Type;
	
	/*物品编号*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		int32 ItemIndex;
	/*物品名称*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FString ItemName;
	/*物品图标*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		class UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FText Introduction;



	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
};
