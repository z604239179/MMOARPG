// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIBase.h"
#include "UI_Character.generated.h"

/**
 * 
 */
class UUI_EquipmentSlot;
class UUI_AttributeItem;

USTRUCT(BlueprintType)
struct FAttributeItemInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
		FSlateBrush AttributeBrush;
	UPROPERTY(EditDefaultsOnly)
		FText AttributeName;
	UUI_AttributeItem* ItemRef;
};

UCLASS()
class ARPG_API UUI_Character : public UUIBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* HeadSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* RingSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* NecklaceSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* ArmorSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* PantSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* ShoesSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* LeftSlot;

	UPROPERTY(meta = (BindWidget))
		UUI_EquipmentSlot* RightSlot;

	UPROPERTY(meta = (BindWidget))
		class UScrollBox* AttributeBox;

	UPROPERTY(EditDefaultsOnly)
		TMap<EPropertyName, FAttributeItemInfo> AttributeInfos;

	TMap<EEquipmentPart, UUI_EquipmentSlot*> EquipSlotMap;

	UFUNCTION()
		void OnValueChanged(EPropertyName ChangedName, const FPropertesValue& ChangedValue);

	UFUNCTION()
		void HandleEquipChanged(UEquipmentGoods* ChangedGoods, EEquipmentPart ChangedPart);

public:

	UUI_Character(const FObjectInitializer& ObjectInitializer);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)override;

	virtual bool Initialize() override;
};
