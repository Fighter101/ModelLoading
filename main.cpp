#include "Includes.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
//////////////////////Globals//////////////////////////////
//////////ScreenGLobals////////////////////////
GLint width, height;
GLFWwindow* window;
//////////////////Camera Control//////////////////////////
bool keys[1024];
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame
GLfloat lastX = 340, lastY = 240;
GLboolean firstMouse=true;
Camera camera(vec3(0.0f,0.0f,3.0f));
///////////////////////////////////////////////////////
glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
};

///////////////////////Event Call back//////////////////////////////
//////////Key Board/////////////
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
            keys[key] = true;
        else if(action == GLFW_RELEASE)
            keys[key] = false;
    }

}
void move ()
{
    // Camera controls
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(keys[GLFW_KEY_W])
        camera.processKeyBoard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.processKeyBoard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.processKeyBoard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.processKeyBoard(RIGHT, deltaTime);
}
/////////////////////////////////////////////


//////////////////Mouse////////////////////
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse) // this bool variable is initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);


}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}
////////////////////////////////////////////////////////////
int intialize()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(680, 480, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
   glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glfwGetFramebufferSize(window, &width, &height);
    glfwSetKeyCallback(window,key_callback);
    glViewport(0, 0, width, height);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glfwSetCursorPosCallback(window,mouse_callback);
    glfwSetScrollCallback(window,scroll_callback);

}
/////////////////Checks cuz i can't find the fuckin' error////////////////////
GLint getLocation(GLint location)
{
    if(location==-1)
        cout<<"Error"<<endl;
    return location;
}
////////////////////////////Setting Values for Light (TestOnly)///////////////
void lightItUp(Shader MyShader){
    ////////////////////1)Direcftional Light///////////////////////////////////////////
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"dirLight.direction")),-0.2f,-1.0f,-0.3f);
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"dirLight.ambient")),0.2f,0.2f,0.2f);
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"dirLight.specular")),0.5f,0.5f,0.5f);
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"dirLight.diffuse")),1.0f,1.0f,1.0f);
    //////////////////2)Point Light//////////////////////////////////////////
    for (int i = 0; i < 4 ; ++i ) {
        string address="pointLights["+to_string(i)+"].";
        glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,(address+"position").c_str())),pointLightPositions[i].x,pointLightPositions[i].y,pointLightPositions[i].z);
        glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,(address+"constant").c_str())),1.0f);
        glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,(address+"linear").c_str())),0.09f);
        glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,(address+"quadratic").c_str())),0.032f);
        glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,(address+"ambient").c_str())),0.2f,0.2f,0.2f);
        glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,(address+"specular").c_str())),0.5f,0.5f,0.5f);
        glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,(address+"diffuse").c_str())),1.0f,1.0f,1.0f);
    }
    ////////////////////////////////3)SpotLight//////////////////////////////
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.position")),camera.cameraPos.x,camera.cameraPos.y,camera.cameraPos.z);
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.direction")),camera.cameraFront.x,camera.cameraFront.y,camera.cameraFront.z);
    glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.innerCutOff")),glm::cos(glm::radians(12.5f)));
    glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.outerCutOff")),glm::cos(glm::radians(17.5f)));
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.ambient")),0.2f,0.2f,0.2f);
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.specular")),0.5f,0.5f,0.5f);
    glUniform3f(getLocation(glGetUniformLocation(MyShader.Program,"spotLight.diffuse")),1.0f,1.0f,1.0f);
    glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,("spotLight.constant"))),1.0f);
    glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,("spotLight.linear"))),0.09f);
    glUniform1f(getLocation(glGetUniformLocation(MyShader.Program,("spotLight.quadratic"))),0.032f);
    glUniform1f(glGetUniformLocation(MyShader.Program,"material.shininess"),1.0f);
}

int main() {
    if(intialize()==-1)
        return -1;
    Shader MyShader("VertexShader.vs.glsl","FragmentShader.fs.glsl");
    Model nanoSuit("nanosuit/nanosuit.obj");
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        move();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        MyShader.Use();
        lightItUp(MyShader);
        mat4 projection = glm::perspective(radians(camera.Zoom),(GLfloat) width/ (GLfloat) height, 0.1f, 100.0f);
        mat4 model =glm::mat4(1.0f);
        model=glm::scale(model,glm::vec3(0.2,0.2,0.2));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "viewMatrix"),1,GL_FALSE,value_ptr(camera.getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "projectionMatrix"),1,GL_FALSE,value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(MyShader.Program, "modelMatrix"),1,GL_FALSE,value_ptr(model));
        glUniform3f(glGetUniformLocation(MyShader.Program,"viewPos"),camera.cameraPos.x,camera.cameraPos.y,camera.cameraPos.z);
        nanoSuit.Draw(MyShader);
        glfwSwapBuffers(window);
        glBindVertexArray(0);
    }
        return 0;
}