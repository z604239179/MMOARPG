// Fill out your copyright notice in the Description page of Project Settings.

#include "PBuff.h"
#include "MyAssetManager.h"
UPBuff::UPBuff()
{
	m_Type = UMyAssetManager::PBuffType;
	PersistentTime = 0;
}
