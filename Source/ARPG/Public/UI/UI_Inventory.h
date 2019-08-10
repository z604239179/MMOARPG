// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "UI_Inventory.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_Inventory : public UUIBase
{
	GENERATED_BODY()
public:

	UUI_Inventory(const FObjectInitializer& ObjectInitializer);

protected:


	UPROPERTY(EditDefaultsOnly)
		int32 InvetoryRow;

	UPROPERTY(EditDefaultsOnly)
		int32 InvetoryColumn;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUI_InventorySlot> SlotClass;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* InventoryPanel;

	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Close;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Block_Gold;


	UFUNCTION()
		FText GoldDelegate();
	UFUNCTION()
		void HandleClosed();
	UFUNCTION()
		void HandleInventoryChanged(UGoodsBase* ChangedGoods, int32 ChangedIndex);
public:

	virtual bool Initialize() override;
	
};
