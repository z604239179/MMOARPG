// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_SlotBase.h"

#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Styling/SlateBrush.h"
#include "PrimaryGoods.h"
#include "DragWidget.h"
#include "DragDropOperation.h"


bool UUI_SlotBase::Initialize()
{
	Super::Initialize();
	if (BorderMaterial)
	{
		MatInstance = UMaterialInstanceDynamic::Create(BorderMaterial, this);
		Border_Item->Background.SetResourceObject(MatInstance);
	}
	if (DefaultBackground)
	{
		Image_Item->Brush.SetResourceObject(DefaultBackground);
	}
// 	Image_Item->BrushDelegate.BindUFunction(this, FName("Image_Delegate"));
// 	Block_Nums->TextDelegate.BindUFunction(this, FName("Block_Delegate"));
// 	Border_Item->BackgroundDelegate.BindUFunction(this, FName("Border_Delegate"));
	return true;
}


FReply UUI_SlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (SlotPtr)
	{
		/*按下左键*/
		if (InMouseEvent.GetEffectingButton() == TEXT("LeftMouseButton"))
		{
			return FReply::Handled().DetectDrag(this->GetCachedWidget().ToSharedRef(), EKeys::LeftMouseButton);
			OnMouseLeftButtonUp();
		}
		
		/*按下右键*/
		if (InMouseEvent.GetEffectingButton() == TEXT("RightMouseButton"))
		{
			OnMouseRightButtonDown();
		}
	}
	return FReply::Handled();
}

FReply UUI_SlotBase::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	if (SlotPtr)
	{
		/*按下左键*/
		if (InMouseEvent.GetEffectingButton() == TEXT("LeftMouseButton"))
		{
			OnMouseLeftButtonUp();
		}

		/*按下右键*/
		if (InMouseEvent.GetEffectingButton() == TEXT("RightMouseButton"))
		{
			OnMouseRightButtonUp();
		}
	}
	return FReply::Handled();
}

void UUI_SlotBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (SlotPtr&&IntroductClass)
	{

		IntroductionPanle = CreateWidget<UUI_Introduction, APlayerController>(GetOwningPlayer(), IntroductClass);
		IntroductionPanle->SetLocalItem(SlotPtr);
		IntroductionPanle->SetDesiredSizeInViewport(IntroductionPanle->GetDesiredSize());
		IntroductionPanle->AddToViewport(1);

	}
}

void UUI_SlotBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (IntroductionPanle)
	{
		IntroductionPanle->RemoveFromViewport();
		IntroductionPanle = nullptr;
	}

}


FReply UUI_SlotBase::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (IntroductionPanle)
	{
		FVector2D CursorLoc;
		GetOwningPlayer()->GetMousePosition(CursorLoc.X, CursorLoc.Y);
		IntroductionPanle->SetPositionInViewport(CursorLoc, true);
	}
	return FReply::Unhandled();
}

void UUI_SlotBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	UClass* DragClass = StaticLoadClass(UDragWidget::StaticClass(), nullptr, TEXT("WidgetBlueprint'/Game/UI/UMG/Slot/UMG_DragWidget.UMG_DragWidget_C'"));
	if (DragClass)
	{
		UDragWidget* DragIns = CreateWidget<UDragWidget, APlayerController>(GetOwningPlayer(), DragClass);
		if (DragIns)
		{
			DragIns->InitDragWidget(SlotPtr->ItemIcon);
			UDragDropOperation* TempOperation= NewObject<UDragDropOperation>();
			TempOperation->Payload = this;
			TempOperation->Pivot = EDragPivot::CenterCenter;
			TempOperation->DefaultDragVisual = DragIns;
			OutOperation = TempOperation;
		}
	}
}

void UUI_SlotBase::FlushSlot(UGoodsBase* InGoods)
{
	if (InGoods)
	{
		SlotPtr = InGoods->GetBasicItemInfo();
		Image_Item->Brush.SetResourceObject(SlotPtr->ItemIcon);
		if (InGoods->CurrentNum > 1)
		{
			Block_Nums->SetText(FText::AsNumber(InGoods->CurrentNum));
		}
		else
		{
			Block_Nums->SetText(FText());
		}

		if (MatInstance)
		{
			switch (SlotPtr->mQuality)
			{
			case EQuality::Normal:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 1.f, 1.f));
				break;

			case EQuality::Delicate:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 1.f, 0.f));
				break;

			case EQuality::Rare:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 1.f));
				break;
			case EQuality::Epic:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 0.f, 1.f));
				break;
			case EQuality::Legend:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 1.f, 0.f));
				break;
			default:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 0.f));
				break;
			}

		}
	}
	else
	{
		SlotPtr = nullptr;
		Image_Item->Brush.SetResourceObject(DefaultBackground);
		Block_Nums->SetText(FText());
		MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 0.f));
	}
}

void UUI_SlotBase::FlushSlot(UPrimaryGoods* InGoodsInfo, int32 Nums)
{
	SlotPtr = InGoodsInfo;
	if (InGoodsInfo)
	{
		Image_Item->Brush.SetResourceObject(SlotPtr->ItemIcon);
		if (Nums > 1)
		{
			Block_Nums->SetText(FText::AsNumber(Nums));
		}
		else
		{
			Block_Nums->SetText(FText());
		}

		if (MatInstance)
		{
			switch (SlotPtr->mQuality)
			{
			case EQuality::Normal:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 1.f, 1.f));
				break;

			case EQuality::Delicate:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 1.f, 0.f));
				break;

			case EQuality::Rare:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 1.f));
				break;
			case EQuality::Epic:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 0.f, 1.f));
				break;
			case EQuality::Legend:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 1.f, 0.f));
				break;
			default:
				MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 0.f));
				break;
			}

		}
	}
	else
	{
		Image_Item->Brush.SetResourceObject(DefaultBackground);
		Block_Nums->SetText(FText());
		MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 0.f));
	}
}

// FSlateBrush UUI_SlotBase::Image_Delegate()
// {
// 	if (*SlotPtr)
// 	{
// 		ItemBrush.SetResourceObject((*SlotPtr)->GetBasicItemInfo()->ItemIcon);
// 
// 	}
// 	else
// 	{
// 		ItemBrush.SetResourceObject(DefaultBackground);
// 	}
// 	return ItemBrush;
// }
// 
// FText UUI_SlotBase::Block_Delegate()
// {
// 	if (*SlotPtr)
// 	{
// 		if ((*SlotPtr)->CurrentNum > 1)
// 		{
// 			return FText::AsNumber((*SlotPtr)->CurrentNum);
// 		}
// 	}
// 	return FText();
// }
// 
// FSlateBrush UUI_SlotBase::Border_Delegate()
// {
// 
// 	FSlateBrush RetBrush = FSlateBrush();
// 	if (*SlotPtr&&MatInstance)
// 	{
// 		switch ((*SlotPtr)->GetBasicItemInfo()->mQuality)
// 		{
// 		case EQuality::Normal:
// 			MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 1.f, 1.f));
// 			break;
// 
// 		case EQuality::Delicate:
// 			MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 1.f, 0.f));
// 			break;
// 
// 		case EQuality::Rare:
// 			MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 1.f));
// 			break;
// 		case EQuality::Epic:
// 			MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 0.f, 1.f));
// 			break;
// 		case EQuality::Legend:
// 			MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(1.f, 1.f, 0.f));
// 			break;
// 		default:
// 			MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 0.f));
// 			break;
// 		}
// 
// 	}
// 	else
// 	{
// 		MatInstance->SetVectorParameterValue(FName("BorderColor"), FLinearColor(0.f, 0.f, 0.f));
// 	}
// 	RetBrush.SetResourceObject(MatInstance);
// 	return RetBrush;
// }



