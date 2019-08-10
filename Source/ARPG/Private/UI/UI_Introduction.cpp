// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Introduction.h"
#include "Inventory/GoodsBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

FSlateBrush UUI_Introduction::Imamge_Delegate()
{
	FSlateBrush TempSlateBrush;
	if (LocalInfo)
	{
		TempSlateBrush.SetResourceObject(LocalInfo->ItemIcon);
	}
	return TempSlateBrush;
}

FText UUI_Introduction::Name_Delegate()
{
	if (LocalInfo)
	{
		return FText(FText::FromString(LocalInfo->ItemName));
	}
	return FText();
}

FText UUI_Introduction::Type_Delegate()
{
	FText TempText;
	if (LocalInfo)
	{
		switch (LocalInfo->mGoodsType)
		{
		case EGoodsType::Equipment:
			TempText = FText::FromString(TEXT("Equipment"));
			break;
		case EGoodsType::Consume:
			TempText = FText::FromString(TEXT("Consume"));
			break;
		case EGoodsType::Stuff:
			TempText = FText::FromString(TEXT("Stuff"));
			break;
		default:
			break;

		}
	}
	return TempText;
}

FText UUI_Introduction::Introducetion_Delegate()
{
	return LocalInfo->Introduction;
}

FText UUI_Introduction::Price_Delegate()
{
	return FText::AsNumber(LocalInfo->Price);
}

bool UUI_Introduction::Initialize()
{
	Super::Initialize();


	Item_Image->BrushDelegate.BindUFunction(this, FName("Imamge_Delegate"));
	Item_Name->TextDelegate.BindUFunction(this, FName("Name_Delegate"));
	Item_Type->TextDelegate.BindUFunction(this, FName("Type_Delegate"));
	Item_Introducetion->TextDelegate.BindUFunction(this, FName("Introducetion_Delegate"));
	Item_Price->TextDelegate.BindUFunction(this, FName("Price_Delegate"));


	return true;
}
