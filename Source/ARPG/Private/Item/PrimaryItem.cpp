// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryItem.h"

FPrimaryAssetId UPrimaryItem::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(m_Type,GetFName());
}
