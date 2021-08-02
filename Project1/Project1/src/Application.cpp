#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/TestClearColor.h"

//struct ShaderProgramSource
//{
//    std::string VertexSource;
//    std::string FragmentSource;
//};
// 
//static ShaderProgramSource ParseShader(const std::string& filePath)
//{
//    std::ifstream stream(filePath);
//
//    enum class ShaderType
//    {
//        NONE = -1,
//        VERTEX = 0,
//        FRAGMENT = 1
//    };
//
//    std::string line;
//    std::stringstream ss[2];
//    ShaderType type = ShaderType::NONE;
//    while (getline(stream, line))
//    {
//        if (line.find("#shader") != std::string::npos)
//        {
//            if (line.find("vertex") != std::string::npos)
//            {
//                type = ShaderType::VERTEX;
//            }
//            else if (line.find("fragment") != std::string::npos)
//            {
//                type = ShaderType::FRAGMENT;
//            }
//        }
//        else
//        {
//            ss[(int)type] << line << "\n";
//        }
//    }
//    return { ss[0].str(), ss[1].str() };
//}

//static unsigned int CompileShader(unsigned int type, const std::string& source)
//{
//    unsigned int id = glCreateShader(type);
//    const char* src = source.c_str();
//    //���� const char& src = &source[0];
//    glShaderSource(id, 1, &src, nullptr);
//    glCompileShader(id);
//
//    //Error handling
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//    {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//        char* message = (char*)alloca(length * sizeof(char));
//        glGetShaderInfoLog(id, length, &length, message);
//        std::cout << "Failed to complie " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader:  " << message << std::endl;
//        glDeleteShader(id);
//        return 0;
//    }
//
//    return id;
//
//}

//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    unsigned int program = glCreateProgram();
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//    glLinkProgram(program);
//    glValidateProgram(program);
//
//    glDeleteShader(vs); //shader��Ϣ�Ѿ���������program��
//    glDeleteShader(fs);
//
//    return program;
//}

const char* glsl_version = "#version 130";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //����openglΪ3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    //setting opengl profile to be core����glEnableVertexAttribArray(0)������Ϊû��vertex array
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //������������

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        //������
        //float positions[6] =
        //{
        //    -0.5f, -0.5f,
        //    0.0f, 0.5f,
        //    0.5f, -0.5f
        //};

        //�ı���
        //float pos[] =
        //{
        //    -50.0f, -50.0f, 0.0f, 0.0f,
        //     50.0f, -50.0f, 1.0f, 0.0f,
        //     50.0f,  50.0f, 1.0f, 1.0f,
        //    -50.0f,  50.0f, 0.0f, 1.0f
        //};

        //unsigned int indices[] =
        //{
        //    0, 1, 2,
        //    2, 3, 0
        //};

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //VertexArray va;
        ////unsigned int vao;//vertex array object
        ////GLCall(glGenVertexArrays(1, &vao));
        ////GLCall(glBindVertexArray(vao));

        //VertexBuffer vb(pos, 4 * 4 * sizeof(float)); //����ÿ��vertex��4��float����4��vertex��������4 * 4
        ////unsigned int buffer;
        ////glGenBuffers(1, &buffer);
        ////glBindBuffer(GL_ARRAY_BUFFER, buffer); //bind�ͺ�����ѡ����һ��ͼ��Ĳ��裬�������ử�����ͼ���ϣ���ţ���
        ////glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), pos, GL_STATIC_DRAW);

        //VertexBufferLayout layout;
        //layout.Push<float>(2);
        //layout.Push<float>(2);
        //va.AddBuffer(vb, layout);
        ////glEnableVertexAttribArray(0); //��סһ��Ҫдenable
        ////glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); //ȷ��vertex layout. 
        ////ͬʱ����������vertex array��Ҳ�������뽫buffer��vao���������ġ���������ĵ�һ�������������vertex array���±ꣿ

        //IndexBuffer ib(indices, 6);
        ////unsigned int ibo; // index buffer object ������unsigned����
        ////glGenBuffers(1, &ibo);
        ////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        ////glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


        //glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        //glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); //��ͷ������
        ////glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0)); //����ͷ�����ƶ�100����
        ////glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0)); //�����������Ҹ��ƶ�200

        ////glm::mat4 mvp = proj * view * model;

        ////glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); 
        ////��ʵ��������boundaries left right bottom top near far �����������Χ���λ�ö����ɼ�
        //// proj������������0��0��0��
        ////��pos����ʾ��������ı��ο����1����proj�ж���Ŀ����4��proj(projection matrix)��Ҫ����ӳ�䵽-1��1֮�䣬Ҳ����ͼ���Ȼ�ռ�������ڵ�1/4
        //
        ////���Դ��� �������projection matrix
        ////glm::vec4 vp(-0.5f, -0.5f, 0.0f, 1.0f);
        ////glm::vec4 result = proj * vp;


        //Shader shader("res/shaders/Basic.shader");
        ////ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        ////std::cout << "VERTEX" << std::endl;
        ////std::cout << source.VertexSource << std::endl;
        ////std::cout << "FRAGMENT" << std::endl;
        ////std::cout << source.FragmentSource << std::endl;

        ////ֱ��дstring����ʽ
        ////std::string vertexShader =
        ////    "#version 330 core\n"
        ////    "\n"
        ////    "layout(location = 0) in vec4 position;\n"
        ////    "\n"
        ////    "void main()\n"
        ////    "{\n"
        ////    "    gl_Position = position;\n"
        ////    "}\n";

        ////std::string fragmentShader =
        ////    "#version 330 core\n"
        ////    "\n"
        ////    "layout(location = 0) out vec4 color;"
        ////    "\n"
        ////    "void main()\n"
        ////    "{\n"
        ////    "    color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        ////    "}\n";

        //shader.Bind();
        ////unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        ////glUseProgram(shader);

        //shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        ////int location = glGetUniformLocation(shader, "u_Color"); //����һһ��Ӧ
        ////ASSERT(location != -1);
        ////GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

        //Texture texture("res/textures/logo.png");
        //texture.Bind();
        //shader.SetUniform1i("u_Texture", 0); //��Ϊ������texture.Bind()�ｫ���������0�����Եڶ���������0

        ////unbind everything
        //va.UnBind();
        ////glBindVertexArray(0);
        //shader.UnBind();
        ////glUseProgram(0);
        //vb.UnBind();
        ////glBindBuffer(GL_ARRAY_BUFFER, 0);
        //ib.UnBind();
        ////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        Renderer renderer;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");

        //test::TestClearColor test;

        //glm::vec3 translationA(200, 200, 0);
        //glm::vec3 translationB(400, 200, 0);

        //float r = 0.0f;
        //float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            renderer.Clear();
            //glClear(GL_COLOR_BUFFER_BIT);

            //test.OnUpdate(0.0f);
            //test.OnRender();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->OnImGuiRender();

                ImGui::End();
            }

            //test.OnImGuiRender();

            //ԭ��openglд������
            //glBegin(GL_TRIANGLES);
            //glVertex2d(-0.5f, -0.5f);
            //glVertex2d( 0.0f,  0.5f);
            //glVertex2d( 0.5f, -0.5f);
            //glEnd();

            //modern opengl
            //glDrawArrays(GL_TRIANGLES, 0, 3); 

            //��ʽ1 ��draw֮ǰbind
            //shader.Bind();
            //GLCall(glUseProgram(shader));

            //{
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
            //    glm::mat4 mvp = proj * view * model;
            //    shader.Bind();
            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    renderer.Draw(va, ib, shader);
            //}

            //{
            //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
            //    glm::mat4 mvp = proj * view * model;
            //    shader.Bind();
            //    shader.SetUniformMat4f("u_MVP", mvp);
            //    renderer.Draw(va, ib, shader);
            //}

 
            ////shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            ////GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

            ////GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            ////��ʽ2 ������unsigned���� ���ٸ�indexȥdraw ��Ϊǰ���Ѿ�bind�ˣ��������һ����nullptr

            ////va.Bind();
            ////GLCall(glBindVertexArray(vao));
            ////ib.Bind();
            ////GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

            ////renderer.Draw(va, ib, shader);
            ////GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


            //if (r > 1.0f)
            //    increment = -0.05f;
            //else if (r < 0.0f)
            //    increment = 0.05f;

            //r += increment;

            //// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            //{
            //    static float f = 0.0f;
            //    static int counter = 0;

            //    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            //    //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //    //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            //    //ImGui::Checkbox("Another Window", &show_another_window);

            //    //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //    //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //    //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //    //    counter++;
            //    //ImGui::SameLine();
            //    //ImGui::Text("counter = %d", counter);

            //    ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f); //��0~960֮��
            //    ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
            //    //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            //    ImGui::End();
            //}

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            //glViewport(0, 0, display_w, display_h);
            //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            //glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;

        //glDeleteProgram(shader); //����shader��֮�󣬾Ͳ���Ҫ�������ˣ���ΪShader������������д�����
        //�����scope��Ŀ���ǣ��ر��˴��ں�glGetError�ж�û��context���޷�ֹͣ����Ϊ����IndexBuffer���࣬û������֮ǰ����������ţ�
    }
 

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}