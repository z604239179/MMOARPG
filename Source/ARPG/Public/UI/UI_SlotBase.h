// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "UI_SlotBase.generated.h"

/**
 * 
 */
UENUM()
enum class ESlotType : uint8
{
	Inventory,
	Equipment,
	Shop
};

class UUI_Introduction;
UCLASS(Abstract)
class ARPG_API UUI_SlotBase : public UUIBase
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Item;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Block_Nums;

	UPROPERTY(meta = (BindWidget))
		class UBorder* Border_Item;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UUI_Introduction> IntroductClass;

	UPROPERTY(EditDefaultsOnly)
		UTexture2D* DefaultBackground;

	UPROPERTY(EditDefaultsOnly)
		UMaterial* BorderMaterial;


	UMaterialInstanceDynamic* MatInstance;

	UUI_Introduction* IntroductionPanle;

	UPrimaryGoods* SlotPtr;

	FSlateBrush ItemBrush;
	// protected:
	// 	UFUNCTION()
	// 		FSlateBrush Image_Delegate();
	// 
	// 	UFUNCTION()
	// 		virtual FText Block_Delegate();
	// 
	//  	UFUNCTION()
	//  		FSlateBrush Border_Delegate();

public:
	ESlotType SlotType;

	virtual bool Initialize() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	/*Custom*/
	virtual void OnMouseRightButtonDown(){};
	virtual void OnMouseLeftButtonDown() {};
	virtual void OnMouseRightButtonUp() {};
	virtual void OnMouseLeftButtonUp() {};
	void FlushSlot(UGoodsBase* InGoods);
	void FlushSlot(UPrimaryGoods* InGoodsInfo,int32 Nums);
};
