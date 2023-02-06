#pragma once

#include <string>

namespace ZJY
{
	/// <summary>
	/// 基类的设计，虚析构函数，然后纯虚函数让子类必须重写
	/// </summary>
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}
