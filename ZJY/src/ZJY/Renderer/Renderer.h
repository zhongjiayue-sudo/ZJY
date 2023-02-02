#pragma once

#include"RenderCommand.h"

#include"ZJY/Renderer/OrthographicCamera.h"
#include"ZJY/Renderer/Shader.h"

namespace ZJY
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetRendererAPI() {
			return RendererAPI::GetAPI();
		}

	private:
		struct SceneData
		{
			glm::mat4 ViewPorjectionMatrix;
		};

		static SceneData* m_sceneData;
	};
}