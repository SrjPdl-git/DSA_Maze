#include "Application.h"

Application::Application()
	:WINDOW_WIDTH(1024),
	 WINDOW_HEIGHT(710),
	 WINDOW_POSITION(glm::vec2(100,30)),
     graphWidth(8),
     graphHeight(8),
     graphWidthSlider(8),
     graphHeightSlider(8),
     isGeneratePressed(false),
     renderingSpeed(500)
{
    projection = glm::ortho<float>(0.f, WINDOW_WIDTH, WINDOW_HEIGHT,0.f, -1.f, 1.f);

    glm::vec4 vp = glm::vec4(-50.f, -50.f, 0.f, 1.f);
    auto res = projection * vp;
	setup();
}

Application::~Application()
{
}


void Application::setup()
{    
    window.create("MazeGeneratorSolver", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_POSITION);


    /*Initialize GLEW*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::FAILED_TO_INITIALIZE_GLEW" << std::endl;
        glfwTerminate();
    }
    glewExperimental = GL_TRUE;

    
    //creating Imgui context
    ImGui::CreateContext();

    //Imgui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);
    

    //Setting buffer swap interval
    glfwSwapInterval(1);

    //creating shader
    shader.create("vertexShader.glsl", "fragmentShader.glsl");
}
void Application::guiSetup()
{
    ImGui::Begin("Maze Generation Settings");
    ImGui::SliderInt("Maze Width", &graphWidthSlider, 4, 25);
    ImGui::SliderInt("Maze Height", &graphHeightSlider, 4, 20);
    ImGui::Text("Number of nodes = %d", graphHeightSlider * graphWidthSlider);
    ImGui::SliderInt("Speed", &renderingSpeed,1,500);

    if (ImGui::Button("Generate Maze"))                            
        isGeneratePressed = true;
    
    ImGui::End();

}


void Application::update()
{   
    /*Pre-update settings*/
    MazeGenerator mazeGenerator(graphWidth,graphHeight);
   
    Camera2D camera(shader.getProgram());
    glm::mat4 view(1.f);
    view = glm::lookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));


    glm::vec3 translate(0.f);

    /*main loop*/
    while (window.isOpen())
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
        }


        //updating projection matrix to account for window resize
        glm::vec2 viewportSize = window.getViewportSize();
        projection = glm::ortho<float>(0.f, viewportSize.x, viewportSize.y, 0.f, -1.f, 1.f);

        /* Poll for and process events */
        glfwPollEvents();

        /*Imgui Code */
        guiSetup();

        /* Render here */
        glClearColor(0.4f, 1.f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);


        //updating camera
        camera.update(&view, &projection);

        if (isGeneratePressed)
        {
            oldGraphHeight = graphHeight;
            graphWidth = graphWidthSlider;
            graphHeight = graphHeightSlider;
            mazeGenerator.generate(shader.getProgram(),graphWidth,graphHeight,oldGraphHeight);
            isGeneratePressed = false;
        }
        

        mazeGenerator.render(shader.getProgram(),renderingSpeed);

        

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window.getWindow());

    }

    //Cleanup Imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

Application& Application::Get()
{
    static Application instance;
    return instance;
}