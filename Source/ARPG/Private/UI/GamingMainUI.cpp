// Fill out your copyright notice in the Description page of Project Settings.

#include "GamingMainUI.h"
#include "Components/HorizontalBox.h"
#include "Components/EditableText.h"
#include "UI_Inventory.h"
#include "UI_Character.h"
#include "UI_CheatPanel.h"
#include "UI_BuffPanel.h"

bool UGamingMainUI::Initialize()
{
	Super::Initialize();

	if (InventoryClass)
	{
		if (GetOwningPlayer())
		{
			InventoryPanel = CreateWidget<UUI_Inventory, APlayerController>(GetOwningPlayer(), InventoryClass);
			InventoryPanel->AddToViewport();
			InventoryPanel->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (CharacterPanelClass)
	{
		if (GetOwningPlayer())
		{
		CharacterPanel = CreateWidget<UUI_Character, APlayerController>(GetOwningPlayer(), CharacterPanelClass);
		CharacterPanel->AddToViewport();
		CharacterPanel->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
	return true;

}

void UGamingMainUI::AddMessage(const FString& msg, const FString& InstigaterName)
{
	UMG_CheatPanel->AddMessage(msg, InstigaterName);
}

bool UGamingMainUI::CallInventory()
{
	if (InventoryPanel&&InventoryPanel->IsVisible())
	{
		InventoryPanel->SetVisibility(ESlateVisibility::Hidden);
		InventoryPanel->RemoveFromParent(); 
		if (ChildPanel->HasAnyChildren())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	InventoryPanel->SetVisibility(ESlateVisibility::Visible);
	ChildPanel->AddChildToHorizontalBox(InventoryPanel);
	return true;
}

bool UGamingMainUI::CallCharacterPanel()
{
	if (CharacterPanel&&CharacterPanel->IsVisible())
	{
		CharacterPanel->SetVisibility(ESlateVisibility::Hidden);
		CharacterPanel->RemoveFromParent();
		if (ChildPanel->HasAnyChildren())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	CharacterPanel->SetVisibility(ESlateVisibility::Visible);
	ChildPanel->AddChildToHorizontalBox(CharacterPanel);
	return true;
}

bool UGamingMainUI::CallCheatPanel()
{
	if (UMG_CheatPanel)
	{
		if (!UMG_CheatPanel->GetEditableText()->HasUserFocus(GetOwningPlayer()))
		{
			FInputModeUIOnly ModeParams;
			ModeParams.SetWidgetToFocus(UMG_CheatPanel->GetEditableText()->GetCachedWidget());
			GetOwningPlayer()->SetInputMode(ModeParams);
			//UMG_CheatPanel->GetEditableText()->SetUserFocus(GetOwningPlayer());
			return true;
		}
		
	}
	return false;
}

void UGamingMainUI::AddChild(UWidget* InWidget)
{
	ChildPanel->AddChild(InWidget);
}

void UGamingMainUI::RemoveChild(UWidget* InWidget)
{
	ChildPanel->RemoveChild(InWidget);
}

void UGamingMainUI::AddBuff(class UPBuff* BuffInfo)
{
	UMG_BuffPanel->AddBuff(BuffInfo);
}

void UGamingMainUI::RemoveBuff(UPBuff* BuffInfo)
{
	UMG_BuffPanel->RemoveBuff(BuffInfo);
}
