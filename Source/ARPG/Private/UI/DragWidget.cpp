// Fill out your copyright notice in the Description page of Project Settings.

#include "DragWidget.h"
#include "Components/Image.h"
#include "GoodsBase.h"
void UDragWidget::InitDragWidget(UTexture2D* ToShowTexture)
{
	LocalImg->Brush.SetResourceObject(ToShowTexture);
}

