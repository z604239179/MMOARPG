// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_AttributeItem.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_AttributeItem : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
		class UImage* Attribute_Icon;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Attribute_Name;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Attribute_Value;

};
