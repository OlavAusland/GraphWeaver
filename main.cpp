#include "PointObject.hpp"
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

// custom libraries
#include "PluginManager.hpp"
#include "Hierarchy.hpp"
#include "Inspector.hpp"
#include "Canvas.hpp"
#include "Script.hpp"
#include "Graphics.hpp"
#include "EventManager.hpp"
#include "Shader.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Python.h"
#include "DrawManager.hpp"
#include "LineObject.hpp"
#include "Utils.hpp"
#include "PyScript.hpp"
#include "imgui_internal.h"

static bool dragging;
static Vec3 last_position;


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
        Vec3& bounds= Canvas::GetBounds();
        Vec3& scale = Canvas::GetScale();
        
        float dx = last_position.x - posX;
        float dy = last_position.y - posY;

        last_position.x = posX;
        last_position.y = posY;
        
        origo.x -= (dx / bounds.x * scale.x) * 1.5 * Canvas::GetAspect(); // WHY 1.5!?
        origo.y += (dy / bounds.y * scale.y) * 1.5; // WHY 1.5!?
    }
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

    glEnable(GL_PROGRAM_POINT_SIZE);  // <--- Add this!
    glfwSwapInterval(0); // Enable vsync
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_cursor_callback);
    glfwSetDropCallback(window, drop_callback);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    
    ImFont* font = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf", 20 * 0.75f);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }


    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.1, 0.1f, 0.1f, 1.00f);

    // do opengl things

    Shader shader("/home/olav/Documents/C++/GraphWeaver/shaders/default_vertex_shader.glsl",
                    "/home/olav/Documents/C++/GraphWeaver/shaders/default_fragment_shader.glsl");
   
    Shader canvas_shader("/home/olav/Documents/C++/GraphWeaver/shaders/canvas_vertex.glsl",
                            "/home/olav/Documents/C++/GraphWeaver/shaders/canvas_fragment.glsl");
    
    Shader point_shader("/home/olav/Documents/C++/GraphWeaver/shaders/point_vertex.glsl",
                            "/home/olav/Documents/C++/GraphWeaver/shaders/point_fragment.glsl");


    Canvas::SetOrigo({320,240});
    Canvas::SetScale({10, 10});
    Canvas::SetBounds({640, 480});
    PluginManager::LoadPlugins();
    EventManager::Subscribe(EventType::NewFrame, Hierarchy::Update);

    Canvas::SetOrigo({0.0f, 0.0f, 0.0f});

    const Vec3& origo = Canvas::GetOrigo();

    Hierarchy::AddEntity("Test");
    Hierarchy::GetEntity("Test")->AddScript("/home/olav/Documents/C++/GraphWeaver/scripts/circle.py");
    shader.SetActive();

    float angle = 0;
    
    bool use3D = false;
    Vec3& scale = Canvas::GetScale();
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        Canvas::SetAspect((float)display_w / display_h);
        //glViewport(0, 0, scale.x, scale.y);
        //Canvas::SetBounds({(float)display_w, (float)display_h, 0.0f});
        Canvas::SetBounds({(float)display_w, (float)display_h, 0.0f});
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        EventManager::Notify(EventType::NewFrame);
        PluginManager::Update();
        
        float aspect = (float)display_w / display_h;
        Hierarchy::GetEntity("Test")->ExecuteAll();
        
        glm::mat4 proj;
        glm::mat4 view(1.0f);
        if(!use3D)
        {
            proj = glm::ortho(0.0f, (float)(scale.x) * Canvas::GetAspect(), 0.0f, (float)(scale.y), -10.0f, 1000.0f);
        }
        else
        {
            proj = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100000.0f);
            glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 10.0f);
            glm::vec3 target = glm::vec3(0.0, 0.0, 0.0);
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        
            view = glm::lookAt(camera_pos, target, up);
        }
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(origo.x, origo.y, 0));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));        

        canvas_shader.Reload();
        canvas_shader.SetActive();
        canvas_shader.SetUniformMatrix4fv("u_MVP", proj);
        canvas_shader.SetUniform3f("u_color", GraphWeaver::Vec3{1.0f, 1.0f, 1.0f});
        
        Canvas::Draw();
        shader.Reload();
        shader.SetActive();
        shader.SetUniformMatrix4fv("u_MVP", proj * view * model);

       // shader.SetUniform3f("u_color", GraphWeaver::Vec3{1.0f, 0.5f, 0.2f});
        
        
        //DrawManager::Draw();
        GraphWeaver::Color color = DrawManager::GetActiveColor();
        //color = {1.0f, 0.0, 0.0, 1.0f};
        //shader.SetUniform3f("u_color", GraphWeaver::Vec3{1.0f, 0.5f, 0.2f});
        shader.SetUniform4f("u_color", *(GraphWeaver::Vec4*)&color);
        //Hierarchy::GetEntity("Test")->ExecuteAll();
        DrawManager::Draw();

        point_shader.Reload();
        point_shader.SetActive();
        point_shader.SetUniform3f("u_color", GraphWeaver::Vec3{1.0f, 0.5f, 0.2f});
        point_shader.SetUniformMatrix4fv("u_MVP", proj * view * model);
        Hierarchy::GetEntity("Test")->ExecuteAll();

        DrawManager::Draw();
        Inspector::Update();


        ImGui::Begin("Control Panel");
    
        ImGui::Text("%f", io.Framerate);

        ImGui::SliderFloat("Angle", &angle, 0, 360);
        ImGui::InputFloat3("Origo", &(Canvas::GetOrigo().x));
        ImGui::InputFloat3("Scale", &(Canvas::GetScale().x));

        if(ImGui::Button("Toggle 3D"))
        {
            use3D = !use3D;
        }

        ImGui::End();

        ImGui::Begin("Plugins");

        std::string name = "##";
        for(auto& entry : PluginManager::GetPlugins())
        {
            name.append("x");
            if(ImGui::Button(name.c_str(), ImVec2(25, 25)))
            {
                entry.enabled = !entry.enabled;

                if(!entry.enabled) { entry.Unload(); }
                else { entry.Load(); }
            }
            ImGui::SameLine();
            ImGui::Button(entry.plugin_name.c_str(), ImVec2(-1, 25));
            ImGui::Separator();
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
