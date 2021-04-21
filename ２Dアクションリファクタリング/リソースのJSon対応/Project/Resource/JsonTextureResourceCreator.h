#pragma once

#include	"JsonResourceLoadHelper.h"
#include	"Texture.h"

namespace Sample {

	/**
	 * @brief		���\�[�X�p�b�N��Json���琶������
	 */
	class JsonTextureResourceCreator
	{
	public:
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		static ResourceContainerPtr<Texture> Create(const std::string& name) {
			std::ifstream ifs(name);
			if (ifs.fail())
			{
				return ResourceContainerPtr<Texture>();
			}
			nlohmann::json os = nlohmann::json::parse(ifs);
			auto re = std::make_shared<ResourceContainer<Texture>>();
			Create(re, os);
			return re;
		}

		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		static void Create(ResourceContainerPtr<Texture>& bases_, nlohmann::json& os)
		{
			auto& texs = os["Textures"];
			for (auto& tex : texs)
			{
				ResourceContainerKeyType key;
				tex["Key"].get_to(key);
				std::string name;
				tex["File"].get_to(name);
				auto tex = bases_->Add(key);
				tex->Load(name.c_str());
			}
		}
	};

	/**
	 * �ǂݍ��ݗp�w���p�[
	 */
	template < >
	struct JsonResourceLoadHelper<Texture> {
		static void Load(ResourceContainerPtr<Texture>& bases_, nlohmann::json& os)
		{
			JsonTextureResourceCreator::Create(bases_, os);
		}
	};

}