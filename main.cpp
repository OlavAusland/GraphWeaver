#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include <GLES2/gl2.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui_impl_opengl3.h"

// Custom libraries
#include "PluginManager.hpp"
#include "Hierarchy.hpp"
#include "Inspector.hpp"
#include "Canvas.hpp"
#include "Script.hpp"
#include "Graphics.hpp"
#include "Console.hpp"
#include "EventManager.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Python.h"
#include "ShaderManager.hpp"
#include "DrawManager.hpp"
#include "PlaneObject.hpp"
#include "Camera.hpp"
#include "PointObject.hpp"
#include "LineObject.hpp"
#include "Utils.hpp"
#include <chrono>
#include <thread>

static bool dragging;
static Vec3 last_position;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    static Camera& camera = GetActiveCamera();
    
    //camera.Move({0, 0, yoffset});
    Canvas::Zoom({(float)yoffset, (float)yoffset, 0});
    camera.Move({0, 0, yoffset});

}

static void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    printf("Dropped paths:\n");
    for(int i = 0; i < count; i++)
    {
        printf("%s\n", paths[i]);

        if(Inspector::GetActiveEntity() != nullptr)
        {
            Inspector::GetActiveEntity()->AddScript(paths[i]);
        }
    }
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (!ImGui::GetIO().WantCaptureMouse)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            dragging = true;
            EventManager::Notify(EventType::OnDragBegin);
        }

        if(dragging)
        {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos); 
            last_position = {(float)xpos, (float)ypos, 0};
        }

        if(action == GLFW_RELEASE)
        {
            dragging = false;
            EventManager::Notify(EventType::OnDragStop);
        }
    }
}

static void mouse_cursor_callback(GLFWwindow* window, double posX, double posY)
{
    static Vec3& origo = Canvas::GetOrigo();

    if(ImGui::GetIO().WantCaptureMouse)
        return;

    if(dragging)
    {
        Vec2& bounds= Canvas::GetBounds();
        Vec3& scale = Canvas::GetScale();
        
        float dx = last_position.x - posX;
        float dy = last_position.y - posY;

        last_position.x = posX;
        last_position.y = posY;
        
        origo.x -= (dx / bounds.x * scale.x) * Canvas::GetAspect();
        origo.y += (dy / bounds.y * scale.y);
    }
}

void processInput(GLFWwindow *window)
{
    static GraphWeaver::Vec3& origo = Canvas::GetOrigo();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        origo.y -= 0.1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        origo.y += 0.1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        origo.x += 0.1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        origo.x -= 0.1;
}

// Main code
int main(int, char**)
{
    PyConfig config;
    PyConfig_InitPythonConfig(&config);
    Py_InitializeFromConfig(&config);
    
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "GraphWeaver", nullptr, nullptr);
    if (window == nullptr)
        return 1;



    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    glfwSwapInterval(0); // Enable vsync
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_cursor_callback);
    glfwSetDropCallback(window, drop_callback);
    glEnable(GL_MULTISAMPLE);

    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
        
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    
    ImFont* font = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf", 20 * 0.75f);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.1, 0.1f, 0.1f, 1.00f);
    
    Camera camera;
    SetActiveCamera(camera);



    ShaderManager::AddShader("default", "/home/olav/Documents/C++/GraphWeaver/shaders/default_vertex_shader.glsl",
            "/home/olav/Documents/C++/GraphWeaver/shaders/default_fragment_shader.glsl");
    ShaderManager::AddShader("grid", "/home/olav/Documents/C++/GraphWeaver/shaders/grid_vertex.glsl",
            "/home/olav/Documents/C++/GraphWeaver/shaders/grid_fragment.glsl");
    ShaderManager::AddShader("point", "/home/olav/Documents/C++/GraphWeaver/shaders/point_vertex.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/point_fragment.glsl");
    ShaderManager::AddShader("canvas", "/home/olav/Documents/C++/GraphWeaver/shaders/canvas_vertex.glsl",
                           "/home/olav/Documents/C++/GraphWeaver/shaders/canvas_fragment.glsl");

    Hierarchy::AddEntity("Test");
    Hierarchy::GetEntity("Test")->AddScript("/home/olav/Documents/C++/GraphWeaver/scripts/circle.py");
    
    PluginManager::LoadPlugins();
    Canvas::SetScale({10, 10, 0});
    Canvas::SetOrigo({0.0f, 0.0f, 0.0f});
    const Vec3& scale = Canvas::GetScale();
    const Vec3& origo = Canvas::GetOrigo();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        processInput(window);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);
        GetActiveCamera().Update();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Canvas::SetBounds({(float)display_w, (float)display_h});
        Canvas::SetAspect((float)display_w / display_h);

        Canvas::Draw();
        Console::Update();
        Hierarchy::Update();
        Inspector::Update();
        PluginManager::Update();

        DrawManager::Draw();

        ImGui::Begin("Control Panel");


        ImGui::InputFloat2("SCALE", &Canvas::GetScale().x);
        ImGui::Text("%.1f", ImGui::GetIO().Framerate);
        
        if(ImGui::Button("Change Perspective", ImVec2(-1, 25)))
        {
            if(camera.GetPerspectiveType() == ProjectionType::Perspective)
            {
                camera.SetPerspectiveType(ProjectionType::Orthogonal);
            }
            else
            {
                camera.SetPerspectiveType(ProjectionType::Perspective);
            }
        }

        ImGui::End();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
