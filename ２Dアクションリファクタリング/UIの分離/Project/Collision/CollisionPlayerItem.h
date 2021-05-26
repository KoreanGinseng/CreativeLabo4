#pragma once

#include	"CollisionManager.h"
#include	"../Player.h"
#include	"../Enemy.h"

namespace Sample {

	template< >
	inline bool CollisionManager::Collision<CPlayer, CItem>(CPlayer& obj1, CItem& obj2) {
		//アイテムが非表示
		if (!obj2.GetShow())
		{
			return false;
		}
		//アイテムの矩形と自分の矩形で当たり判定
		CRectangle prec = obj1.GetRect();
		CRectangle irec = obj2.GetRect();
		if (prec.CollisionRect(irec))
		{
			obj2.SetShow(false);
			switch (obj2.GetType())
			{
			case ITEM_RECOVER:
				obj1.Heal(30);
				break;
			case ITEM_GOAL:
				obj1.SetGoal(true);
				break;
			}
			return true;
		}
		return false;
	}

	template< >
	inline bool CollisionManager::Collision<CItem, CPlayer>(CItem& obj1, CPlayer& obj2) {
		return Collision(obj2, obj1);
	}
}