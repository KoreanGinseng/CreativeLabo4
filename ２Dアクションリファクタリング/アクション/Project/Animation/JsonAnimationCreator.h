#pragma once

#include	"IAnimationCreator.h"
#include	"MofAnimationState.h"
#include	"../External/nlohmann/json.hpp"

namespace Sample {

	/**
	 * @brief		�A�j���[�V�����C���^�[�t�F�C�X
	 */
	class JsonAnimationCreator : public IAnimationCreator
	{
	private:
		/** �A�j���[�V���� */
		std::vector<AnimationState::AnimationData>	animations_;
	public:
		/**
		 * @brief		JSon�t�@�C������̐���
		 */
		static AnimationCreatorPtr Create(const std::string& name) {
			std::ifstream ifs(name);
			if (ifs.fail())
			{
				return AnimationCreatorPtr();
			}
			nlohmann::json os = nlohmann::json::parse(ifs);
			return std::make_shared<JsonAnimationCreator>(os);
		}

		/**
		 * @brief		�R���X�g���N�^
		 */
		JsonAnimationCreator(nlohmann::json& os)
		{
			auto& anims = os["Animations"];
			for (auto& anim : anims)
			{
				AnimationState::AnimationData acreate{};
				anim["Name"].get_to(acreate.Name);
				anim["OffsetX"].get_to(acreate.OffsetX);
				anim["OffsetY"].get_to(acreate.OffsetY);
				anim["Width"].get_to(acreate.Width);
				anim["Height"].get_to(acreate.Height);
				anim["Loop"].get_to(acreate.bLoop);

				int n = 0;
				auto& frames = anim["Frames"];
				for (auto& frame : frames)
				{
					AnimationState::AnimationPattern pattern;
					frame["Wait"].get_to(pattern.Wait);
					frame["No"].get_to(pattern.No);
					frame["Step"].get_to(pattern.Step);
					acreate.Pattern.push_back(pattern);
					n++;
				}

				animations_.push_back(acreate);
			}
		}

		/**
		 * @brief		����
		 */
		AnimationStatePtr Create() override {
			std::shared_ptr< CreateAnimationState > state = std::make_shared< CreateAnimationState >();
			state->Create(animations_);
			return state;
		}
	};

}