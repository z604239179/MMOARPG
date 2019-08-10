// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI_SlotBase.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_InventorySlot : public UUI_SlotBase
{
	GENERATED_BODY()



public:
	UUI_InventorySlot(const FObjectInitializer& ObjectInitializer);

	virtual void OnMouseRightButtonUp() override;
	virtual void OnMouseLeftButtonUp()override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	int32 SlotIndex = -1;




};
