#pragma once

#include	"Sprite.h"

namespace Sample {

	class SpriteBatch {
	protected:
		/** p·éVF[_[ */
		ShaderPtr			shader_;

		/** `æpobt@ */
		Buffer				vertexBuffer_;
		/** `æpobt@ */
		Buffer				indexBuffer_;

		/** ¸_zñ */
		GLuint				vertexArrayID;

		/** `æp¸_îñ */
		struct Vertex {
			glm::vec3		pos;
			glm::vec2		uv;
			glm::vec4		color;
		};
		/** `æ¸_zñ */
		std::vector<Vertex>	vertices;

		/**
		 * @brief		`æo^
		 */
		struct Register {
			/** `æ·é */
			size_t			count;
			/** p·éeNX` */
			TexturePtr		texture;
		};
		/** `æeNX`zñ */
		std::vector<Register> renders;

		/** `æeNX`o^ */
		void RegisterTexture(TexturePtr& texture)
		{
			//`æo^
			if (renders.empty())
			{
				renders.push_back({ 1, texture });
			}
			else
			{
				Register& data = renders.back();
				if (data.texture == texture)
				{
					data.count++;
				}
				else
				{
					renders.push_back({ 1, texture });
				}
			}
		}
		/** ¸_ÉÀWo^ */
		void RegisterVertexPosition(Vertex* out, const Vector3F& pos, float tw, float th)
		{
			out[0].pos = glm::vec4(pos.x, -th - pos.y, pos.z, 1);
			out[1].pos = glm::vec4(tw + pos.x, -th - pos.y, pos.z, 1);
			out[2].pos = glm::vec4(pos.x, -pos.y, pos.z, 1);
			out[3].pos = glm::vec4(tw + pos.x, -pos.y, pos.z, 1);
		}
		/** ¸_ÉFo^ */
		void RegisterVertexColor(Vertex* out, const glm::vec4& color)
		{
			out[0].color = color;
			out[1].color = color;
			out[2].color = color;
			out[3].color = color;
		}
		/** ¸_ÉFo^ */
		void RegisterVertexColor(Vertex* out, const Vector4F& color)
		{
			RegisterVertexColor(out, glm::vec4(color.r, color.g, color.b, color.a));
		}
		/** ¸_ÉUVo^ */
		void RegisterVertexColor(Vertex* out, float lt, float rt, float ut, float bt)
		{
			out[0].uv[0] = lt;	out[0].uv[1] = bt;
			out[1].uv[0] = rt;	out[1].uv[1] = bt;
			out[2].uv[0] = lt;	out[2].uv[1] = ut;
			out[3].uv[0] = rt;	out[3].uv[1] = ut;
		}
	public:
		/**
		 * @brief		RXgN^
		 */
		SpriteBatch()
			: shader_()
			, vertexBuffer_()
			, indexBuffer_()
			, vertexArrayID(0)
			, vertices()
			, renders() {
		}
		SpriteBatch(const SpriteBatch& obj) = delete;

		/**
		 * @brief		fXgN^
		 */
		~SpriteBatch() {
			Release();
		}

		/**
		 * @brief		ú¶¬
		 * @param[in]	s	g¤VF[_[
		 */
		void Create(const ShaderPtr s, const GLuint polygonCount = 1000) {
			//VF[_[o^
			shader_ = s;

			//|SpÌf[^¶¬
			vertices.resize(polygonCount * 4);
			vertexBuffer_.Create(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STREAM_DRAW);
			vertices.clear();

			std::vector<GLuint> idx;
			idx.resize(polygonCount * 6);
			for (GLuint i = 0; i < polygonCount; i++)
			{
				idx[i * 6 + 0] = (i * 4) + 0;
				idx[i * 6 + 1] = (i * 4) + 1;
				idx[i * 6 + 2] = (i * 4) + 2;
				idx[i * 6 + 3] = (i * 4) + 1;
				idx[i * 6 + 4] = (i * 4) + 3;
				idx[i * 6 + 5] = (i * 4) + 2;
			}
			indexBuffer_.Create(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

			//¸_f[^zñì¬
			glGenVertexArrays(1, &vertexArrayID);
			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_.ID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_.ID());
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_.ID());

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(12));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(20));

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/**
		 * @brief		¸_îñÌXV
		 */
		void RefreshVertex() {
			vertexBuffer_.SubData(0, sizeof(Vertex) * vertices.size(), vertices.data());
		}

		/**
		 * @brief		Äo^pZbg
		 */
		void Reset() {
			vertices.clear();
			renders.clear();
		}

		/**
		 * @brief		eNX`Åo^
		 *				wèÍÀWÌÝ
		 * @param[in]	texture			p·éeNX`
		 * @param[in]	pos				`æÀW
		 */
		void RenderRegister(TexturePtr& texture, const Vector3F& pos) {
			//ÇÁÅÅåð´¦é
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "`æÂ\Ååð´ßµÜ·...\n";
				return;
			}
			//¸_ãü
			Vertex out[4];
			RegisterVertexPosition(out, pos, (float)texture->Width(), (float)texture->Height());
			RegisterVertexColor(out, glm::vec4(1));
			RegisterVertexColor(out, 0, 1, 0, 1);

			vertices.insert(vertices.end(), out, out + 4);

			//o^
			RegisterTexture(texture);
		}

		/**
		 * @brief		eNX`Åo^
		 *				wèÍÀWÆFÌÝ
		 * @param[in]	texture			p·éeNX`
		 * @param[in]	pos				`æÀW
		 * @param[in]	color			`æF
		 */
		void RenderRegister(TexturePtr& texture, const Vector3F& pos, const Vector4F& color) {
			//ÇÁÅÅåð´¦é
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "`æÂ\Ååð´ßµÜ·...\n";
				return;
			}
			//¸_ãü
			Vertex out[4];
			RegisterVertexPosition(out, pos, (float)texture->Width(), (float)texture->Height());
			RegisterVertexColor(out, color);
			RegisterVertexColor(out, 0, 1, 0, 1);

			vertices.insert(vertices.end(), out, out + 4);

			//o^
			RegisterTexture(texture);
		}

		/**
		 * @brief		eNX`Åo^
		 *				wèÍÀWÆFÆé`
		 * @param[in]	texture			p·éeNX`
		 * @param[in]	pos				`æÀW
		 * @param[in]	color			`æF
		 * @param[in]	rect			`æé`
		 */
		void RenderRegister(TexturePtr& texture, const Vector3F& pos, const Vector4F& color, const RectangleF& rect) {
			//ÇÁÅÅåð´¦é
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "`æÂ\Ååð´ßµÜ·...\n";
				return;
			}
			//¸_ãü
			Vertex out[4];
			float tw = (float)texture->Width();
			float th = (float)texture->Height();
			RegisterVertexPosition(out, pos, tw, th);
			RegisterVertexColor(out, color);
			float lt = rect.Left / tw;
			float rt = rect.Right / tw;
			float ut = rect.Top / th;
			float bt = rect.Bottom / th;
			RegisterVertexColor(out, lt, rt, ut, bt);

			vertices.insert(vertices.end(), out, out + 4);

			//o^
			RegisterTexture(texture);
		}

		/**
		 * @brief		XvCgÅo^
		 * @param[in]	sprite			p·éXvCg
		 */
		void RenderRegister(SpritePtr& sprite) {
			//ÇÁÅÅåð´¦é
			if (vertices.size() + 4 > vertices.capacity())
			{
				std::cerr << "`æÂ\Ååð´ßµÜ·...\n";
				return;
			}
			//æ
			TexturePtr texture = sprite->Texture();
			//|Sf[^ì¬
			float tw = (float)texture->Width();
			float th = (float)texture->Height();
			//UV
			const RectangleF& rect = sprite->SrcRect();
			float lt = rect.Left / tw;
			float rt = rect.Right / tw;
			float ut = rect.Top / th;
			float bt = rect.Bottom / th;
			if (sprite->XFlip())
			{
				float tmp = rt;
				rt = lt;
				lt = tmp;
			}
			if (sprite->YFlip())
			{
				float tmp = bt;
				bt = ut;
				ut = tmp;
			}
			//Êu
			const Vector3F& pivot = sprite->Pivot();
			float lx = pivot.x * -rect.Width();
			float rx = (1 - pivot.x) * rect.Width();
			float uy = pivot.y * rect.Height();
			float by = (1 - pivot.y) * -rect.Height();

			//Ï·sñvZ
			const Vector3F& position = sprite->Position();
			const Vector3F& rotation = sprite->Rotation();
			const Vector3F& scale = sprite->Scale();
			const Vector3F& anchor = sprite->Anchor();
			float tx = GraphicsController::GetInstance().ScreenWidth() * anchor.x;
			float ty = GraphicsController::GetInstance().ScreenHeight() * anchor.y;
			const glm::mat4 matT = glm::translate(glm::mat4(1), glm::vec3(tx + position.x, -ty + -position.y, position.z));
			const glm::mat4 matRY = glm::rotate(matT, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			const glm::mat4 matRXY = glm::rotate(matRY, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			const glm::mat4 matRZXY = glm::rotate(matRXY, glm::radians(-rotation.z), glm::vec3(0, 0, 1));
			const glm::mat4 matS = glm::scale(matRZXY, glm::vec3(scale.x, scale.y, scale.z));

			//¸_ãü
			Vertex out[4];
			const Vector3F* offset = sprite->VertexOffset();
			out[0].pos = matT * glm::vec4(lx + offset[0].x, by - offset[0].y, offset[0].z, 1);
			out[1].pos = matT * glm::vec4(rx + offset[1].x, by - offset[1].y, offset[1].z, 1);
			out[2].pos = matT * glm::vec4(lx + offset[2].x, uy - offset[2].y, offset[2].z, 1);
			out[3].pos = matT * glm::vec4(rx + offset[3].x, uy - offset[3].y, offset[3].z, 1);

			RegisterVertexColor(out, sprite->Color());
			RegisterVertexColor(out, lt, rt, ut, bt);

			vertices.insert(vertices.end(), out, out + 4);

			//o^
			RegisterTexture(texture);
		}

		/**
		 * @brief		XvCgð\¦³¹é
		 */
		void Render() {
			glBindVertexArray(vertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_.ID());
			shader_->Enable();

			auto mvp = GraphicsController::GetInstance().Camera()->ViewProjection();
			shader_->SetViewProjectionMatrix(&mvp[0][0]);

			//o^eNX`ðê`æ
			size_t offset = 0;
			for (const auto& r : renders)
			{
				shader_->BindTexture(0, r.texture->ID());
				glDrawElements(GL_TRIANGLES, r.count * 6, GL_UNSIGNED_INT,
					reinterpret_cast<const GLvoid*>(offset));
				offset += r.count * 6 * sizeof(GLuint);
			}
			shader_->BindTexture(0, 0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		/**
		 * @brief		ðú
		 */
		void Release() {
			if (vertexArrayID > 0)
			{
				glDeleteVertexArrays(1, &vertexArrayID);
				vertexArrayID = 0;
			}
		}

		/**
		 * @brief		ShaderÖÌAccessor
		 * @return		VF[_[
		 */
		const ShaderPtr Shader(void) const {
			return shader_;
		}

	};
	using SpriteBatchPtr = std::shared_ptr< SpriteBatch >;
}