// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UI_Shop.generated.h"

/**
 * 
 */
class UUI_ShopSlot;
UCLASS()
class ARPG_API UUI_Shop : public UUIBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUI_ShopSlot> SlotClass;

	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* ShopPanel;

	UPROPERTY(meta = (BindWidget))
		class UButton* Shop_Close;
// 
// 	UFUNCTION()
// 		void HandleClosed();
public:

	virtual bool Initialize() override;

	UFUNCTION(BlueprintCallable)
		virtual void InitShop(const TArray<FPrimaryAssetId>& GoodsList);

	UFUNCTION(BlueprintCallable)
		virtual void ClearShop();

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
