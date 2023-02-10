#pragma once

#include"ZJY/Renderer/Shader.h"
#include"glm/glm.hpp"

//todo:remove
typedef unsigned int GLenum;

namespace ZJY
{
	class OpenGLShader:public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string GetName() override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& martix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& martix);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSource);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
