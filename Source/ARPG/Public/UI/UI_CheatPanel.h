// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UIBase.h"
#include "UI_CheatPanel.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_CheatPanel : public UUIBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UScrollBox* CheatBox;

	UPROPERTY(meta = (BindWidget))
		class UEditableText* InputBox;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUI_MessageItem> MessageItemClass;

	UPROPERTY(EditDefaultsOnly)
		int32 MaxMessageNums;
public:

	FORCEINLINE  UEditableText* GetEditableText() { return InputBox; }

	UFUNCTION()
		void CommitMessage(const FText& Text, ETextCommit::Type CommitMethod);

	void AddMessage(const FString& msg,const FString& Instigater);

	virtual bool Initialize() override;
};
