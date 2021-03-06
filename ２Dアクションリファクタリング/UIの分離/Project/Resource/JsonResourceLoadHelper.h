#pragma once

#include	"ResourceContainer.h"
#include	"../External/nlohmann/json.hpp"

namespace Sample {

	/**
	 * 読み込み用ヘルパー
	 */
	template < class Type >
	struct JsonResourceLoadHelper {
		static void Load(ResourceContainerPtr<Type>& bases_, nlohmann::json& os)
		{
			static_assert(false, "Unknown Resources!!");
		}
	};

}