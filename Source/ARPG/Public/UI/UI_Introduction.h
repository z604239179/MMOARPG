// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "UI_Introduction.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_Introduction : public UUIBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Item_Image;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Item_Name;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Item_Type;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Item_Introducetion;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Item_Price;

	UPrimaryGoods* LocalInfo;

	UFUNCTION()
		FSlateBrush Imamge_Delegate();

	UFUNCTION()
		FText Name_Delegate();

	UFUNCTION()
		FText Type_Delegate();

	UFUNCTION()
		FText Introducetion_Delegate();

	UFUNCTION()
		FText Price_Delegate();
public:
	virtual bool Initialize() override;

	virtual void SetLocalItem(UPrimaryGoods* TargetItem) { LocalInfo = TargetItem; }
};
