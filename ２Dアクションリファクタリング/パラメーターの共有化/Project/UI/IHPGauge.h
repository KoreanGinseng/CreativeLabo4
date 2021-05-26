#pragma once

#include	"../Common/Common.h"
#include	"../Common/Observer.h"

namespace Sample {

	/**
	 * @brief		HP
	 */
	template < typename T >
	class IHPGauge : public IObserver<T>
	{
	public:
		virtual void Set(const T& v) = 0;
		virtual const T Get() const = 0;
		virtual const float GetPercent() const = 0;
	};
	//ポインタ置き換え
	using HPGaugePtr = std::shared_ptr<IHPGauge<int>>;

}