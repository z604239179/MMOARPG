// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.h"
#include "PlayerInfoData.h"
#include "UIBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUIBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	class APlayerInfoData* OnwerData;

public:
	UUIBase(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

	APlayerInfoData* GetOwnerData() { return OnwerData; }

	//virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
};
