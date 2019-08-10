// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_CheatPanel.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "UI_MessageItem.h"

void UUI_CheatPanel::CommitMessage(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
	case ETextCommit::Default:
		break;
	case ETextCommit::OnEnter:
		GetOwningPlayer<AMyPlayerController>()->SendMessage(Text.ToString());
		break;
	case ETextCommit::OnUserMovedFocus:
		break;
	case ETextCommit::OnCleared:
		InputBox->SetText(FText());
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		break;
	default:
		break;
	}
	
}

void UUI_CheatPanel::AddMessage(const FString& msg, const FString& Instigater)
{
	UUI_MessageItem* SpawnedText = CreateWidget<UUI_MessageItem>(this, MessageItemClass);
	SpawnedText->MessageText->SetText(FText::FromString(Instigater + ": " + msg));
	CheatBox->AddChild(SpawnedText);
	CheatBox->ScrollToEnd();
	//达到最大消息数
	if (CheatBox->GetChildrenCount() > MaxMessageNums)
	{
		CheatBox->RemoveChildAt(0);
	}
}

bool UUI_CheatPanel::Initialize()
{
	Super::Initialize();
	InputBox->OnTextCommitted.AddDynamic(this, &UUI_CheatPanel::CommitMessage);
	MaxMessageNums = 50;
	return true;
}
