// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlock.h"
#include "UI_MessageItem.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_MessageItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* MessageText;
};
