#pragma once

#include	"AnimationState.h"

#ifdef __MOFLIB
#include	<Mof.h>

namespace Sample {

	/**
	 * @brief		Mofの機能を使ったアニメーション
	 */
	class MofAnimationState : public AnimationState
	{
	protected:
		/** Mofのモーションコントローラー */
		CSpriteMotionController		motion_;
		/** Mofのモーション対応 */
		using MotionMap = std::unordered_map<std::string, MofU32 >;
		MotionMap					motionMap_;

		/**
		 * @brief		アニメーションデータのMof変換
		 */
		SpriteAnimationCreate Convert(AnimationData data) {
			SpriteAnimationCreate re{
				data.Name.c_str(),
				data.OffsetX,	data.OffsetY,
				data.Width,		data.Height,
				data.bLoop,
				{0}
			};
			for (MofU32 i = 0; i < data.Pattern.size(); i++)
			{
				re.Pattern[i].Wait = data.Pattern[i].Wait;
				re.Pattern[i].No = data.Pattern[i].No;
				re.Pattern[i].Step = data.Pattern[i].Step;
			}
			return re;
		}

	public:
		/**
		 * @brief		コンストラクタ
		 */
		MofAnimationState()
			: AnimationState()
			, motion_()
			, motionMap_() {
		}

		/**
		 * @brief		Mofのアニメーションコントローラー生成
		 * @param[in]	pattern			アニメーション生成情報
		 * @return		true			成功
		 *				false			失敗
		 */
		bool Create(const std::vector< AnimationData >& pattern) override {
			std::vector< SpriteAnimationCreate > pac(pattern.size());
			for (MofU32 i = 0; i < pattern.size(); i++)
			{
				pac[i] = Convert(pattern[i]);
				motionMap_[pattern[i].Name] = i;
			}
			return motion_.Create(&pac[0], pattern.size());
		}

		/**
		 * @brief		更新
		 */
		void Update() override {
			constexpr float frameTime = 0.017f;
			motion_.AddTimer(frameTime);
			srcRect_ = motion_.GetSrcRect();
		}

		/**
		 * @brief		現在のモーションを変更
		 * @param[in]	name	登録モーション名
		 * @param[in]	isSame	同一モーションでの更新フラグ
		 * @return		true	指定モーション実行中
		 *				false	違う
		 */
		bool ChangeMotion(const std::string& name, bool isSame = true) override {
			return motion_.ChangeMotion(motionMap_[name], isSame) == TRUE;
		}


		/**
		 * @brief		指定名称の登録モーションが実行されているかどうか
		 * @param[in]	name	登録モーション名
		 * @return		true	指定モーション実行中
		 *				false	違う
		 */
		bool IsMotion(const std::string& name) const override {
			const auto& v = motionMap_.find(name);
			if (v == motionMap_.end()) { return false; }
			return motion_.GetMotionNo() == v->second;
		}

		/**
		 * @brief		現在のモーションが終了しているかを判定する。
		 *				モーションがループする場合はTRUEになることはない
		 * @return		true	終了済み
		 *				false	まだ終了していない
		 */
		bool IsEndMotion() override {
			return motion_.IsEndMotion() == TRUE;
		}
	};
	using CreateAnimationState = MofAnimationState;

}

#endif