#pragma once

#include	"../Common/Common.h"
#include	"../Common/Rectangle.h"

namespace sip {
    /**
        * @brief		アニメーションインターフェイス
        */
    class __declspec(novtable) IAnimationState {
    public:

        /**
            * @brief		アニメーションパターンデータ
            */
        struct AnimationPattern {
            int									Wait;						//!<フレームウェイト
            int									No;							//!<パターン番号
            int									Step;						//!<パターン段
        };
        /**
            * @brief		アニメーションデータ
            */
        struct AnimationData {
            std::string							Name;						//!<アニメーション名
            float								OffsetX;					//!<Xオフセット位置
            float								OffsetY;					//!<Yオフセット位置
            float								Width;						//!<幅
            float								Height;						//!<高さ
            bool								bLoop;						//!<ループフラグ(TRUEならループ、FALSEなら最終フレームで停止)
            std::vector< AnimationPattern >		Pattern;					//!<パターン
        };

        /**
            * @brief		デストラクタ
            */
        virtual ~IAnimationState() = default;

        /**
            * @brief		Mofのアニメーションコントローラー生成
            * @param[in]	pattern			アニメーション生成情報
            * @return		true			成功
            *				false			失敗
            */
        virtual bool Create(const std::vector< AnimationData >& pattern) = 0;

        /**
            * @brief		更新
            */
        virtual void Update() = 0;

        /**
            * @brief		現在のモーションを変更
            * @param[in]	name	登録モーション名
            * @param[in]	isSame	同一モーションでの更新フラグ
            * @return		true	指定モーション実行中
            *				false	違う
            */
        virtual bool ChangeMotion(const std::string& name, bool isSame = true) = 0;

        /**
            * @brief		指定名称の登録モーションが実行されているかどうか
            * @param[in]	name	登録モーション名
            * @return		true	指定モーション実行中
            *				false	違う
            */
        virtual bool IsMotion(const std::string& name) const = 0;

        /**
            * @brief		現在のモーションが終了しているかを判定する。
            *				モーションがループする場合はTRUEになることはない
            * @return		true	終了済み
            *				false	まだ終了していない
            */
        virtual bool IsEndMotion() = 0;

        /**
            * @brief	現在のアニメーション矩形取得
            * @return	現在のアニメーション矩形
            */
        virtual Rectangle& GetSrcRect() = 0;
        /**
            * @brief	現在のアニメーション矩形取得
            * @return	現在のアニメーション矩形
            */
        virtual const Rectangle& GetSrcRect() const = 0;
    };
    //ポインタ置き換え
    using AnimationStatePtr = std::shared_ptr<IAnimationState>;
}
