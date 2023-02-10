#include<ZJY.h>
#include"Platform/OpenGL/OpenGLShader.h"

#include"imgui/imgui.h"

#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

class ExampleLayer : public ZJY::Layer
{
public:
	ExampleLayer() :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		/*
		#############################################################################
		###################################三角形####################################
		#############################################################################
		*/

		m_VertexArray.reset(ZJY::VertexArray::Creat());

		float vertives[3 * 7] = {
			-0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f , 1.0f,
			 0.5f , -0.5f , 0.0f , 0.0f , 0.0f , 1.0f , 1.0f,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f , 1.0f
		};

		ZJY::Ref<ZJY::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(ZJY::VertexBuffer::Creat(vertives, sizeof(vertives)));
		ZJY::BufferLayout layout = {
			{ZJY::ShaderDataType::Float3,"a_Position"},
			{ZJY::ShaderDataType::Float4,"a_Color"}
		};

		m_VertexBuffer->SetLayeout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		//glEnableVertexAttribArray(1);
		////顶点属性实际上存储在顶点数组中，而不是顶点缓冲区
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)12);//4下标，4个浮点数,布局是3个浮点数和4个浮点数相加，偏移从0结束的地方开始

		//索引缓冲区也就是元素缓冲区,索引就是点的连接顺序等
		unsigned int indices[3] = { 0,1,2 };
		ZJY::Ref<ZJY::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(ZJY::IndexBuffer::Creat(indices, sizeof(indices) / sizeof(uint32_t)));//sizeof(indices) / sizeof(uint32_t)=3
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		/*
		#############################################################################
		###################################三角形####################################
		#############################################################################
		*/

		/*
		#############################################################################
		###################################正方形####################################
		#############################################################################
		*/

		m_SquareVA.reset(ZJY::VertexArray::Creat());

		float squarevertives[5 * 4] = {
	//     ---- 位置 ----        - 纹理坐标 -
			-0.5f , -0.5f , 0.0f , 0.0f, 0.0f,
			 0.5f , -0.5f , 0.0f , 1.0f, 0.0f,
			 0.5f ,  0.5f , 0.0f , 1.0f, 1.0f,
			-0.5f ,  0.5f , 0.0f , 0.0f, 1.0f
		};

		ZJY::Ref<ZJY::VertexBuffer> SquareVB;
		SquareVB.reset(ZJY::VertexBuffer::Creat(squarevertives, sizeof(squarevertives)));
		SquareVB->SetLayeout({
			{ZJY::ShaderDataType::Float3, "a_Position"},
			{ZJY::ShaderDataType::Float2, "a_TexCoord"}
		});
		m_SquareVA->AddVertexBuffer(SquareVB);

		uint32_t squareindices[6] = { 0,1,2,2,3,0 };
		ZJY::Ref<ZJY::IndexBuffer> SquareIB;
		SquareIB.reset(ZJY::IndexBuffer::Creat(squareindices, sizeof(squarevertives) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		/*
		#############################################################################
		###################################正方形####################################
		#############################################################################
		*/


		//uniform 从cpu端将数据传入,通过shader类的方法设置这些uniform

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjuection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjuection * u_Transform * vec4(a_Position, 1.0 );
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5,1.0);
				color = v_Color;
			}
		)";
		m_Shader = ZJY::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string SquareSrc = R"(
			#version 330 core
		
			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ViewProjuection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				gl_Position = u_ViewProjuection * u_Transform * vec4(a_Position, 1.0 );
			}
		)";

		std::string SquareFSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;
			
			uniform vec3 u_color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(u_color,1.0);
			}
		)";
		m_FlatColorShader = ZJY::Shader::Create("FlatColor", SquareSrc, SquareFSrc);

		auto TexCoordShader = m_ShaderLibrary.Load("Asset/shaders/Texture.glsl");

		m_Texture = ZJY::Texture2D::Create("Asset/textures/container.jpg");
		m_PNGTexture = ZJY::Texture2D::Create("Asset/textures/star.png");

		std::dynamic_pointer_cast<ZJY::OpenGLShader>(TexCoordShader)->Bind();
		std::dynamic_pointer_cast<ZJY::OpenGLShader>(TexCoordShader)->UploadUniformInt("u_Texture", 0);//0号插槽
	}

	/// <summary>
	/// 设置Delta Time来解决不同帧率限制下的相同帧率
	/// </summary>
	/// <param name="ts">Delta Time</param>
	void OnUpdate(ZJY::Timestep ts) override
	{
		//Z_CORE_TRACE("Delta timr:{0}s ({1}ms)", ts.GetSecond(), ts.GetMilliseSecond());

		if (ZJY::Input::IsKeyPressed(ZJY::Key::A))
		{
			m_CameraPosition.x -= speed * ts;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::D))
		{
			m_CameraPosition.x += speed * ts;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::W))
		{
			m_CameraPosition.y += speed * ts;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::S))
		{
			m_CameraPosition.y -= speed * ts;
		}

		if (ZJY::Input::IsKeyPressed(ZJY::Key::Q))
		{
			m_CameraRotation -= speed * ts;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::E))
		{
			m_CameraRotation += speed * ts;
		}

		#pragma region 移动物体
		/*if (ZJY::Input::IsKeyPressed(ZJY::Key::I))
				{
					m_SquarePosition.y += m_SquareSpeed * ts;
				}
				else if (ZJY::Input::IsKeyPressed(ZJY::Key::K))
				{
					m_SquarePosition.y -= m_SquareSpeed * ts;
				}
				else if (ZJY::Input::IsKeyPressed(ZJY::Key::J))
				{
					m_SquarePosition.x -= m_SquareSpeed * ts;
				}
				else if (ZJY::Input::IsKeyPressed(ZJY::Key::L))
				{
					m_SquarePosition.x += m_SquareSpeed * ts;
				}*/
		#pragma endregion

		ZJY::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
		ZJY::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ZJY::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ZJY::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ZJY::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_color", m_Color);

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ZJY::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto TexCoordShader = m_ShaderLibrary.Get("Texture");

		//层级，第一个在后面的层 
		m_Texture->Bind();
		ZJY::Renderer::Submit(TexCoordShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_PNGTexture->Bind();
		ZJY::Renderer::Submit(TexCoordShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//ZJY::Renderer::Submit(m_Shader, m_VertexArray);

		ZJY::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Shader Setting");
		ImGui::ColorEdit3("color", glm::value_ptr(m_Color));
		ImGui::End();
	}
	void OnEvent(ZJY::Event& event) override
	{
		//ZJY::EventDispatcher dispatcher(event);//事件调度
		//dispatcher.Dispatch<ZJY::KeyPressedEvent>(Z_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}
	/*bool OnKeyPressedEvent(ZJY::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == ZJY::Key::A)
		{
			m_CameraPosition.x -= speed;
		}
		else if (event.GetKeyCode() == ZJY::Key::D)
		{
			m_CameraPosition.x += speed;
		}
		else if (event.GetKeyCode() == ZJY::Key::W)
		{
			m_CameraPosition.y += speed;
		}
		else if (event.GetKeyCode() == ZJY::Key::S)
		{
			m_CameraPosition.y -= speed;
		}
		return false;
	}*/


private:
	ZJY::ShaderLibrary m_ShaderLibrary;
	//画出一个图形，只需要声明shader和VA，VB和IB在内部实现
	ZJY::Ref<ZJY::Shader> m_Shader;
	ZJY::Ref<ZJY::VertexArray> m_VertexArray;

	ZJY::Ref<ZJY::Shader> m_FlatColorShader;
	ZJY::Ref<ZJY::VertexArray> m_SquareVA;

	ZJY::Ref<ZJY::Texture2D> m_Texture, m_PNGTexture;

	ZJY::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float speed = 1.0f;

	float m_CameraRotation = 0.0f;

	glm::vec3 m_Color = { 1,1,1 };
};

class Sandbox :public ZJY::Application
{
public:
	Sandbox();
	~Sandbox();

private:

};

Sandbox::Sandbox()
{
	PushLayer(new ExampleLayer());
}

Sandbox::~Sandbox()
{

}

ZJY::Application* ZJY::CreatApplication() {
	return new Sandbox();
}