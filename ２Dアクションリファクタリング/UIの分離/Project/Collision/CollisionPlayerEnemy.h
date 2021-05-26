#pragma once

#include	"CollisionManager.h"
#include	"../Player.h"
#include	"../Enemy.h"

namespace Sample {

	template< >
	inline bool CollisionManager::Collision<CPlayer, CEnemy>(CPlayer& obj1, CEnemy& obj2) {
		//敵が非表示
		if (!obj2.GetShow())
		{
			return false;
		}
		//HPがなくなると当たり判定しない
		if (obj1.GetHP() <= 0)
		{
			return false;
		}
		//ダメージ中のため当たり判定をおこなわない
		if (obj1.GetDamageWait() > 0 || obj2.GetDamageWait() > 0)
		{
			return false;
		}
		//敵の矩形と自分の矩形でダメージ
		CRectangle prec = obj1.GetRect();
		CRectangle erec = obj2.GetRect();
		if (prec.CollisionRect(erec))
		{
			obj1.Damage(5, 60, prec.Left < erec.Left);
			return true;
		}
		//攻撃中の場合のみ攻撃との当たり判定を実行
		if (!obj1.IsAttack())
		{
			return false;
		}
		//敵の矩形と自分の攻撃矩形で敵がダメージ
		prec = obj1.GetAttackRect();
		if (prec.CollisionRect(erec))
		{
			obj2.Damage(5, obj1.IsReverse());
			return true;
		}
		return false;
	}

	template< >
	inline bool CollisionManager::Collision<CEnemy, CPlayer>(CEnemy& obj1, CPlayer& obj2) {
		return Collision(obj2, obj1);
	}
}