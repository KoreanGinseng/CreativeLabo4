#pragma once

#include	<vector>
#include	<algorithm>
#include	"Observable.h"

namespace Sample {

	template <class... Args>
	class Subject : public IObservable<Args...> {
	private:
		/** 通知を受けるオブザーバーリスト */
		std::vector<std::shared_ptr< IObserver<Args...> >> observerList;
	public:
		/**
		 * コンストラクタ
		 */
		Subject()
			: observerList()
		{
		}
		/**
		 * デストラクタ
		 */
		virtual ~Subject()
		{
		}

		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		void Subscribe(std::shared_ptr < IObserver<Args...> > pobs) override {
			observerList.push_back(pobs);
		}

		/**
		 * @brief	通知を受けるオブザーバーの登録
		 */
		std::shared_ptr < ObserverFunction<Args...> > Subscribe(std::function<void(Args...)> f) override {
			auto func = std::make_shared< ObserverFunction<Args...> >(f);
			observerList.push_back(func);
			return func;
		}

		/**
		 * @brief	通知を受けるオブザーバーの削除
		 */
		void Dispose(std::shared_ptr < IObserver<Args...> > pobs) override {
			observerList.erase(std::remove_if(
				observerList.begin(), observerList.end(),
				[&](const std::shared_ptr < IObserver<Args...> >& o) {return o == pobs; }),
				observerList.end());
		}

		/**
		 * @brief	通知メソッド
		 */
		void Notify(Args... args) {
			for (auto& obj : observerList) {
				obj->Notify(args...);
			}
		}
	};
}