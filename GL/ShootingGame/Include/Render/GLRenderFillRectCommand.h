#pragma once
#include "RenderFillRectCommand.h"

#ifdef __GLLIB
#include "../../Framework/Graphics/Buffer.h"

namespace sip {

	class GLRenderFillRectCommand : public RenderFillRectCommand {
	private:

	public:
		using RenderFillRectCommand::RenderFillRectCommand;
		void Exec() override;
	};

	inline RenderCommandPtr RenderFillRectCommand::Create(const sip::Rectangle& rect, const sip::Vector4& color) {
		return std::make_shared< sip::GLRenderFillRectCommand >(rect, color);
	}
}

#endif //__GLLIB