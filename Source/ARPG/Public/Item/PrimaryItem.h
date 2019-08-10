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
	
	/*��Ʒ���*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		int32 ItemIndex;
	/*��Ʒ����*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FString ItemName;
	/*��Ʒͼ��*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		class UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FText Introduction;



	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
};
