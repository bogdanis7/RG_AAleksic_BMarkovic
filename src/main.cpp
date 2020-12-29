#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/model.h>
#include <iostream>
#include "Figure.h"
#include "Figure.cpp"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback1(GLFWwindow* window, int key, int scancode, int action, int mods);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mod);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

static Figure *f;
static Figure *f2;
//vector<Field> fields;

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 10.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 1.0f, -3.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


bool firstMouse = true;
float yaw = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

map<string,vector<float>> mapa;
map<string,Figure*> mapafigurica;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(7.0f, 4.0f, 2.0f);

glm::vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(-2.0f, 0.0f, 0.0f),
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 0.0f, 0.0f),
            glm::vec3(3.0f, 0.0f, 0.0f),
            glm::vec3(4.0, 0.0f, 0.0f),
            glm::vec3(-3.0f, 0.0f, 0.0f),

            glm::vec3(1.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(-1.0f, 0.0f, 1.0f),
            glm::vec3(-2.0f, 0.0f, 1.0f),
            glm::vec3(3.0f, 0.0f, 1.0f),
            glm::vec3(2.0f, 0.0f, 1.0f),
            glm::vec3(-3.0f, 0.0f, 1.0f),
            glm::vec3(4.0, 0.0f, 1.0f),


            glm::vec3(0.0f, 0.0f, 2.0f),
            glm::vec3(1.0f, 0.0f, 2.0f),
            glm::vec3(-2.0f, 0.0f, 2.0f),
            glm::vec3(-1.0f, 0.0f, 2.0f),
            glm::vec3(2.0f, 0.0f, 2.0f),
            glm::vec3(3.0f, 0.0f, 2.0f),
            glm::vec3(4.0, 0.0f, 2.0f),
            glm::vec3(-3.0f, 0.0f, 2.0f),

            glm::vec3(1.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(-1.0f, 0.0f, 3.0f),
            glm::vec3(-2.0f, 0.0f, 3.0f),
            glm::vec3(3.0f, 0.0f, 3.0f),
            glm::vec3(2.0f, 0.0f, 3.0f),
            glm::vec3(-3.0f, 0.0f, 3.0f),
            glm::vec3(4.0, 0.0f, 3.0f),

            glm::vec3(0.0f, 0.0f, 4.0f),
            glm::vec3(1.0f, 0.0f, 4.0f),
            glm::vec3(-2.0f, 0.0f, 4.0f),
            glm::vec3(-1.0f, 0.0f, 4.0f),
            glm::vec3(2.0f, 0.0f, 4.0f),
            glm::vec3(3.0f, 0.0f, 4.0f),
            glm::vec3(4.0, 0.0f, 4.0f),
            glm::vec3(-3.0f, 0.0f, 4.0f),

            glm::vec3(1.0f, 0.0f, 5.0f),
            glm::vec3(0.0f, 0.0f, 5.0f),
            glm::vec3(-1.0f, 0.0f, 5.0f),
            glm::vec3(-2.0f, 0.0f, 5.0f),
            glm::vec3(3.0f, 0.0f, 5.0f),
            glm::vec3(2.0f, 0.0f, 5.0f),
            glm::vec3(-3.0f, 0.0f, 5.0f),
            glm::vec3(4.0, 0.0f, 5.0f),

            glm::vec3(0.0f, 0.0f, 6.0f),
            glm::vec3(1.0f, 0.0f, 6.0f),
            glm::vec3(-2.0f, 0.0f, 6.0f),
            glm::vec3(-1.0f, 0.0f, 6.0f),
            glm::vec3(2.0f, 0.0f, 6.0f),
            glm::vec3(3.0f, 0.0f, 6.0f),
            glm::vec3(4.0, 0.0f, 6.0f),
            glm::vec3(-3.0f, 0.0f, 6.0f),

            glm::vec3(1.0f, 0.0f, 7.0f),
            glm::vec3(0.0f, 0.0f, 7.0f),
            glm::vec3(-1.0f, 0.0f, 7.0f),
            glm::vec3(-2.0f, 0.0f, 7.0f),
            glm::vec3(3.0f, 0.0f, 7.0f),
            glm::vec3(2.0f, 0.0f, 7.0f),
            glm::vec3(-3.0f, 0.0f, 7.0f),
            glm::vec3(4.0, 0.0f, 7.0f)
    };

    int main() {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        vector<char> s = {'A','B','C','D','E','F','G','H'};
        string pom = "";
        f = new Figure("G6");
        f2 = new Figure("H2");
        mapafigurica["G6"] = f;
        mapafigurica["H2"] = f2;
        vector<float> vec(3);
        float x = -0.1f;
        float y = 0.3f;
        float z = 0.3f;
        int j = 2.3f;
        for(char c : s){
            z = j;
            j++;
            x = 0;
            for(float i = -0.1 ; i < 7.0f; i++){
                x = i;
                vec = {x,y,z};
                pom += c;
                char p = i + '0';
                pom+=p;
                mapa[pom]=vec;

                pom = "";
            }
        }

           cout << mapa["A1"][0] << mapa["A1"][1] << mapa["A1"][2] << endl;
           cout << mapa["G6"][0] << mapa["G6"][1] << mapa["G6"][2] << endl;


#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwSetKeyCallback(window, key_callback);
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetKeyCallback(window, key_callback1);

        glfwSetScrollCallback(window, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
        // stbi_set_flip_vertically_on_load(true);
        // build and compile our shader zprogram
        //tekstura i svetlo
        Shader boardShader("resources/shaders/board.vs", "resources/shaders/board.fs");
        Shader lightShader("resources/shaders/light.vs", "resources/shaders/light.fs");

        // ------------------------------------
        Shader figureShader("resources/shaders/1.model_loading.vs", "resources/shaders/1.model_loading.fs");
        Shader ourShader("resources/shaders/field.vs", "resources/shaders/field.fs");
        Model figurica(FileSystem::getPath("resources/objects/WoodenChess/12930_WoodenChessKnightSideA_v1_l3.obj"));
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
                -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, //A
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,//B
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,//C
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // D
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,//F
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f//E
        };
        // world space positions of our cubes

        float texture_vertices[] = {
                //pozicije            //normale            //koordinate teksture
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        };


        unsigned int VBO1, fieldsVAO;
        glGenVertexArrays(1, &fieldsVAO);
        glGenBuffers(1, &VBO1);

        glBindVertexArray(fieldsVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int lightVAO;
        glGenVertexArrays(1, &lightVAO);
        glBindVertexArray(lightVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        //tekstura za veliki kvadrat

        unsigned int VBO2, boardVAO;
        glGenVertexArrays(1, &boardVAO);
        glGenBuffers(1, &VBO2);

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texture_vertices), texture_vertices, GL_STATIC_DRAW);

        glBindVertexArray(boardVAO);
        // pozicija
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normale
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //tekstura
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);





        // load and create a texture
        // -------------------------

        //TODO funkcija za ucitavanje tekstura
        unsigned int diffuseMap;
        // texture 1
        // ---------
        glGenTextures(1, &diffuseMap);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/chess4.png").c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);



        boardShader.use();
        boardShader.setInt("diffuse", 0);

        //tekstura za podlogu
        unsigned int texture2;
        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        data = stbi_load(FileSystem::getPath("resources/textures/chess4.png").c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);


        ourShader.use();
        ourShader.setInt("texture2", 1);



        // render loop
        // -----------
        while (!glfwWindowShouldClose(window)) {
            // per-frame time logic
            // --------------------
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //aktiviranje shadera za veliki kvadrat
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);
            boardShader.use();

            boardShader.setVec3("light.position", lightPos);
            boardShader.setVec3("viewPos", cameraPos);

            boardShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            boardShader.setVec3("light.diffuse", 0.5, sin(glfwGetTime())/2.0+0.5, sin(glfwGetTime())/2.0+0.5);
            boardShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

            boardShader.setVec3("material.specular", 0.2f, 0.2f, 0.2f);
            boardShader.setFloat("material.shininess", 32.0f);

            // create transformations
            glm::mat4 model = glm::mat4(1.0f);

            glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 projection = glm::mat4(1.0f);


            //ovde se salje globalna promenljiva fov koja se menja na scroll preko callbacka
            projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);

            model=glm::scale(model, glm::vec3(9.6f, 0.2f, 9.6f));
            model=glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
            model = glm::translate(model, glm::vec3(0.058f, -0.34f, 2.2f));

            // saljemo matrice shaderu
            boardShader.setMat4("projection", projection);
            boardShader.setMat4("view", view);
            boardShader.setMat4("model", model);




            glBindVertexArray(boardVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //svetlo
            lightShader.use();
            lightShader.setVec3("color", 0.5, sin(glfwGetTime())/2.0+0.5, sin(glfwGetTime())/2.0+0.5);
            lightShader.setMat4("projection", projection);
            lightShader.setMat4("view", view);
            model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(2.0f));
            lightShader.setMat4("model", model);

            glBindVertexArray(lightVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);


            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);
            // activate shader
            ourShader.use();

            // pass projection matrix to shader (note that in this case it could change every frame)
            //glm::mat4 projection = glm::perspective(glm::radians(fov), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
             //                                       100.0f);
            ourShader.setMat4("projection", projection);

            // camera/view transformation
            //glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            ourShader.setMat4("view", view);



            // render boxes
            glBindVertexArray(fieldsVAO);
            for (unsigned int i = 0; i < 64; i++) {
                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(0.5f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                ourShader.setMat4("model", model);
                if (i % 2)
                    ourShader.setVec3("color", 0.0f, 0.0f, 0.0f);
                else
                    ourShader.setVec3("color", 0.0f, 0.0f, 0.0f);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, texture2);
                glDrawArrays(GL_TRIANGLES, 0, 36);




            }

            //for figure in figures OVDE CE DA IDE
            string field1 = f->getField();
            string field2 = f2->getField();

           // cout << cords[0] << " " << cords[1] << " " << cords[2] << endl;

            // world transformation
            model = glm::mat4(1.0f);
            model = translate(model, glm::vec3(0.0f, -2.0f, -1.0f));
            model = scale(model, glm::vec3(8.0f, 2.0f, 6.0f));

            figureShader.use();

            figureShader.setMat4("projection", projection);
            figureShader.setMat4("view", view);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field1][0], mapa[field1][1]+0.2f, mapa[field1][2])); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            figureShader.setMat4("model", model);
            // std::cout <<
            figurica.Draw(figureShader);

            model = glm::mat4(1.0f);
            //ovde dodaj 0.2f na y koordinatu
            model = glm::translate(model,glm::vec3(mapa[field2][0], mapa[field2][1]+0.2f, mapa[field2][2])); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            figureShader.setMat4("model", model);
            figurica.Draw(figureShader);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &fieldsVAO);
        glDeleteBuffers(1, &VBO1);
        glDeleteVertexArrays(2, &boardVAO);
        glDeleteBuffers(2, &VBO2);


        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwTerminate();
        return 0;
    }

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);


        float cameraSpeed = 2.5 * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
                cubePositions[0].x = 8.0;
            }
        }
    }

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
    void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f; // change this value to your liking
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);


    }
    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            cout << "Cursor Position at (" << xpos << " : " << ypos << endl;
        }
    }


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        fov -= (float) yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    }
    std::string src;
    std::string dest;
    bool ind = true;

    void key_callback1(GLFWwindow* window, int key, int scancode, int action, int mods) {

        if (ind == true) { //ako je true, treba nam src
            if (key == GLFW_KEY_A and action == GLFW_PRESS) {
                src = "A";
            }
            if (key == GLFW_KEY_B and action == GLFW_PRESS) {
                src = "B";
            }
            if (key == GLFW_KEY_C and action == GLFW_PRESS) {
                src = "C";
            }
            if (key == GLFW_KEY_D and action == GLFW_PRESS) {
                src = "D";
            }
            if (key == GLFW_KEY_E and action == GLFW_PRESS) {
                src = "E";
            }
            if (key == GLFW_KEY_F and action == GLFW_PRESS) {
                src = "F";

            }
            if (key == GLFW_KEY_G and action == GLFW_PRESS) {
                src = "G";
            }
            if (key == GLFW_KEY_H and action == GLFW_PRESS) {
                src = "H";
            }
            if (key == GLFW_KEY_1 and action == GLFW_PRESS) {
                src += "1";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_2 and action == GLFW_PRESS) {
                src += "2";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_3 and action == GLFW_PRESS) {
                src += "3";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_4 and action == GLFW_PRESS) {
                src += "4";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_5 and action == GLFW_PRESS) {
                src += "5";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_6 and action == GLFW_PRESS) {
                src += "6";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_7 and action == GLFW_PRESS) {
                src += "7";
                std::cout << src << std::endl;
                ind = false;
            }
            if (key == GLFW_KEY_8 and action == GLFW_PRESS) {
                src += "8";
                std::cout << src << std::endl;
                ind = false;
            }
        }
//---------------------------------------------------
        else { //ako je false, treba nam dest
            if (key == GLFW_KEY_A and action == GLFW_PRESS) {
                dest = "A";
            }
            if (key == GLFW_KEY_B and action == GLFW_PRESS) {
                dest = "B";
            }
            if (key == GLFW_KEY_C and action == GLFW_PRESS) {
                dest = "C";
            }
            if (key == GLFW_KEY_D and action == GLFW_PRESS) {
                dest = "D";
            }
            if (key == GLFW_KEY_E and action == GLFW_PRESS) {
                dest = "E";
            }
            if (key == GLFW_KEY_F and action == GLFW_PRESS) {
                dest = "F";

            }
            if (key == GLFW_KEY_G and action == GLFW_PRESS) {
                dest = "G";
            }
            if (key == GLFW_KEY_H and action == GLFW_PRESS) {
                dest = "H";
            }
            if (key == GLFW_KEY_1 and action == GLFW_PRESS) {
                dest += "1";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);

                ind = true;
            }
            if (key == GLFW_KEY_2 and action == GLFW_PRESS) {
                dest += "2";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);
                ind = true;
            }
            if (key == GLFW_KEY_3 and action == GLFW_PRESS) {
                dest += "3";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);
                ind = true;
            }
            if (key == GLFW_KEY_4 and action == GLFW_PRESS) {
                dest += "4";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);
                ind = true;
            }
            if (key == GLFW_KEY_5 and action == GLFW_PRESS) {
                dest += "5";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);
                ind = true;
            }
            if (key == GLFW_KEY_6 and action == GLFW_PRESS) {
                dest += "6";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);
                ind = true;
            }
            if (key == GLFW_KEY_7 and action == GLFW_PRESS) {
                dest += "7";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);
                ind = true;
            }
            if (key == GLFW_KEY_8 and action == GLFW_PRESS) {
                dest += "8";
                std::cout << dest << std::endl;
                mapafigurica[src]->setField(dest);

                ind = true;
            }
        }

    }

    // kad je dest postavljne tebi treba da ovome iz srca postavis dest
