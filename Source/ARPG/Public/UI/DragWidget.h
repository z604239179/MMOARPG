// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragWidget.generated.h"



/**
 * 
 */
UCLASS()
class ARPG_API UDragWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* LocalImg;
public:

	void InitDragWidget(UTexture2D* ToShowTexture);

};
