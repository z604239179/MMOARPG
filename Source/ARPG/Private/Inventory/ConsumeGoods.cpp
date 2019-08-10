// Fill out your copyright notice in the Description page of Project Settings.

#include "ConsumeGoods.h"
#include "PrimaryConsume.h"

UConsumeGoods::UConsumeGoods()
{
	m_GoodsType = EGoodsType::Consume;
}

void UConsumeGoods::InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner, int32 Nums /*= 1*/)
{
	Super::InitGoods(_Info, Owner, Nums);
	ConsumeInfo = Cast<UPrimaryConsume>(_Info);
}

bool UConsumeGoods::UseItem()
{
	if (GoodsOwner)
	{
		for (auto& it : ConsumeInfo->PropertyAddList)
		{
			switch (it.Key)
			{
			case EPropertyName::Health:
				GoodsOwner->GetHealthComponent()->SetCurrentHealth(GoodsOwner->GetHealthComponent()->GetCurrentHealth() + it.Value);
				break;
			case EPropertyName::Mana:
				GoodsOwner->GetHealthComponent()->SetCurrentMana(GoodsOwner->GetHealthComponent()->GetCurrentMana() + it.Value);
			default:
				break;
			}
		}
		return true;
	}

	return false;
}
