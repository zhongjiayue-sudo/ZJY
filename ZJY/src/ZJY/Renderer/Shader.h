#pragma once

#include <string>
#include"glm/glm.hpp"

namespace ZJY
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name,const glm::mat4& martix);
	private:
		uint32_t m_RendererID;
	};
}
