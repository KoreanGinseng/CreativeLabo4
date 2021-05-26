#pragma once
#include    "IAnimationCreator.h"
#include	"MofAnimationState.h"

namespace sip {

    /**
        * @brief		アニメーションインターフェイス
        */
    class AniMakeAnimationCreator : public IAnimationCreator {
    private:
        /** アニメーション */
        std::vector<AnimationState::AnimationData>	animations_;

    public:
        /**
            * @brief		JSonファイルからの生成
            */
        static AnimationCreatorPtr Create(const std::string& name) {
            std::ifstream ifs(name);
            if (ifs.fail()) {
                return AnimationCreatorPtr();
            }
            std::string buff((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
            return std::make_shared<AniMakeAnimationCreator>(buff);
        }

        /**
            * @brief		コンストラクタ
            */
        AniMakeAnimationCreator(const std::string& buff) {
            auto to_bool = [&](const std::string& s, int& index) {
                char re = s[index];
                index += sizeof(char);
                return static_cast<bool>(re);
            };
            auto to_int = [&](const std::string& s, int& index) {
                unsigned char tmp[sizeof(int)] = { s[index + 3], s[index + 2], s[index + 1], s[index] };
                index += sizeof(int);
                int re = (tmp[0] << 24) | (tmp[1] << 16) | (tmp[2] << 8) | tmp[3];
                return re;
            };
            auto to_float = [&](const std::string& s, int& index) {
                unsigned char tmp[sizeof(float)] = { s[index], s[index + 1], s[index + 2], s[index + 3] };
                index += sizeof(float);
                float test = *reinterpret_cast<float*>(&tmp[0]);
                return test;
            };
            std::function<std::string(const std::string&, int, int&)> to_string = [&](const std::string& s, int length, int& index) {
                std::string re = s.substr(index, length);
                index += length;
                return re;
            };
            int  index = 0;
            int  tex_file_name_length = to_int(buff, index);
            auto tex_file_name        = to_string(buff, tex_file_name_length, index);
            int  anim_count           = to_int(buff, index);
            for (int i = 0; i < anim_count; i++) {
                AnimationState::AnimationData acreate{};
                int name_length = to_int(buff, index);
                acreate.Name    = to_string(buff, name_length, index);
                acreate.OffsetX = to_float(buff, index);
                acreate.OffsetY = to_float(buff, index);
                acreate.Width   = to_float(buff, index);
                acreate.Height  = to_float(buff, index);
                acreate.bLoop   = to_bool(buff, index);

                int pattern_count = to_int(buff, index);
                for (int j = 0; j < pattern_count; j++) {
                    AnimationState::AnimationPattern pattern;
                    pattern.Wait = to_float(buff, index);
                    pattern.No   = to_int(buff, index);
                    pattern.Step = to_int(buff, index);
                    acreate.Pattern.push_back(pattern);
                }

                animations_.push_back(acreate);
            }
        }

        /**
            * @brief		生成
            */
        AnimationStatePtr Create() override {
            std::shared_ptr< CreateAnimationState > state = std::make_shared< CreateAnimationState >();
            state->Create(animations_);
            return state;
        }
    };
}

