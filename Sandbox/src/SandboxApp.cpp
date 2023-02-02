#include<ZJY.h>

#include"imgui/imgui.h"

class ExampleLayer : public ZJY::Layer
{
public:
	ExampleLayer() :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		/*
		##########################################################################################
		###################################三角形#################################################
		##########################################################################################
		*/

		m_VertexArray.reset(ZJY::VertexArray::Creat());

		float vertives[3 * 7] = {
			-0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 1.0f , 1.0f,
			 0.5f , -0.5f , 0.0f , 0.0f , 0.0f , 1.0f , 1.0f,
			 0.0f ,  0.5f , 0.0f , 1.0f , 1.0f , 0.0f , 1.0f
		};

		std::shared_ptr<ZJY::VertexBuffer> m_VertexBuffer;
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
		std::shared_ptr<ZJY::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(ZJY::IndexBuffer::Creat(indices, sizeof(indices) / sizeof(uint32_t)));//sizeof(indices) / sizeof(uint32_t)=3
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		/*
		##########################################################################################
		###################################三角形#################################################
		##########################################################################################
		*/

		/*
		##########################################################################################
		###################################正方形#################################################
		##########################################################################################
		*/

		m_SquareVA.reset(ZJY::VertexArray::Creat());

		float squarevertives[3 * 4] = {
			-0.75f , -0.75f , 0.0f ,
			 0.75f , -0.75f , 0.0f ,
			 0.75f ,  0.75f , 0.0f ,
			-0.75f ,  0.75f , 0.0f
		};

		std::shared_ptr<ZJY::VertexBuffer> SquareVB;
		SquareVB.reset(ZJY::VertexBuffer::Creat(squarevertives, sizeof(squarevertives)));
		SquareVB->SetLayeout({
			{ZJY::ShaderDataType::Float3,"a_Position"},
			});
		m_SquareVA->AddVertexBuffer(SquareVB);

		uint32_t squareindices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<ZJY::IndexBuffer> SquareIB;
		SquareIB.reset(ZJY::IndexBuffer::Creat(squareindices, sizeof(squarevertives) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		/*
		##########################################################################################
		###################################正方形#################################################
		##########################################################################################
		*/

		//uniform 从cpu端将数据传入,通过shader类的方法设置这些uniform

		std::string vertexSrc = R"(
			#version 330 core
		
			layout(location=0) in vec3 a_Position;
			layout(location=1) in vec4 a_Color;

			uniform mat4 u_ViewProjuection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjuection * vec4(a_Position, 1.0 );
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
		m_Shader.reset(new ZJY::Shader(vertexSrc, fragmentSrc));

		std::string SquareSrc = R"(
			#version 330 core
		
			layout(location=0) in vec3 a_Position;

			uniform mat4 u_ViewProjuection;

			out vec3 v_Position;

			void main()
			{
				gl_Position = u_ViewProjuection * vec4(a_Position, 1.0 );
			}
		)";

		std::string SquareFSrc = R"(
			#version 330 core
			
			layout(location=0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2,1.0,1.0,1.0);
			}
		)";

		m_BlueShader.reset(new ZJY::Shader(SquareSrc, SquareFSrc));//共享指针就不用设置唯一，相当于m_Shader=new std::unique_ptr<Shader>()
	}
	void OnUpdate() override
	{
		if (ZJY::Input::IsKeyPressed(ZJY::Key::A))
		{
			m_CameraPosition.x -= speed;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::D))
		{
			m_CameraPosition.x += speed;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::W))
		{
			m_CameraPosition.y += speed;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::S))
		{
			m_CameraPosition.y -= speed;
		}

		if (ZJY::Input::IsKeyPressed(ZJY::Key::Q))
		{
			m_CameraRotation -= speed;
		}
		else if (ZJY::Input::IsKeyPressed(ZJY::Key::E))
		{
			m_CameraRotation += speed;
		}


		ZJY::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 0.1f });
		ZJY::RenderCommand::Clear();

		ZJY::Renderer::BeginScene(m_Camera);

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ZJY::Renderer::Submit(m_BlueShader, m_SquareVA);
		ZJY::Renderer::Submit(m_Shader, m_VertexArray);

		ZJY::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{

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
	//画出一个图形，只需要声明shader和VA，VB和IB在内部实现
	std::shared_ptr<ZJY::Shader> m_Shader;
	std::shared_ptr<ZJY::VertexArray> m_VertexArray;

	std::shared_ptr<ZJY::Shader> m_BlueShader;
	std::shared_ptr<ZJY::VertexArray> m_SquareVA;

	ZJY::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float speed = -0.1f;

	float m_CameraRotation = 0.0f;
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