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
#include <learnopengl/camera.h>
#define Z_NEAR 0.1f
#define Z_FAR 500.f

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

//inicijalizacija

unsigned int loadCubemap(vector<string> vector);

static Figure *f;
static Figure *f2;
static Figure *f3;
static Figure *f4;
static Figure *f5;
static Figure *f6;
static Figure *f7;
static Figure *f8;
static Figure *f9;
static Figure *f10;
static Figure *f11;
static Figure *f12;
static Figure *f13;
static Figure *f14;
static Figure *f15;
static Figure *f16;
static Figure *f17;
static Figure *f18;
static Figure *f19;
static Figure *f20;
static Figure *f21;
static Figure *f22;
static Figure *f23;
static Figure *f24;
static Figure *f25;
static Figure *f26;
static Figure *f27;
static Figure *f28;
static Figure *f29;
static Figure *f30;
static Figure *f31;
static Figure *f32;


struct PointLight {
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


vector<int> translate_ind;
// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 10.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 1.0f, -3.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera camera(glm::vec3(0.0f, 0.0f, 10.0f));

bool firstMouse = true;
float yaw = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

map<string,vector<float>> mapa; // mapa koja pravi A1 - 7 0 9
map<string,Figure*> mapafigurica; // mapa koja cuva gde je kada koja figura

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(0.5f, 6.0f, 3.0f);
glm::vec3 lightDir(-0.2f, -1.0f, -0.3f);

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
        //MORA DA SE PRAVI ZA SVAKU FIGURU POSEBNO OVA MAPA JER SVE IMAJU RAZLICIT
        //koord pocetak -- ovo je za konja igraca A
        vector<char> s = {'A','B','C','D','E','F','G','H'};
        string pom = "";
        vector<float> vec(3);
        vector<string> niska;

        float x;
        float y = 0.5f;
        float z;
        int j = 9.0f;
        for(char c : s){  // A1 7 0.5 9
            z = j;
            j--;
            x = 0;
            for(float i = 1 ; i <= 8; i++){
                x = 8-i ;

                vec = {x,y,z};
                pom += c;
                char p = i + '0';
                pom+=p;
                mapa[pom]=vec;
                niska.push_back(pom);
                pom = "";
            }
        }


        f = new Figure("B1");
        f2 = new Figure("G1");
        f3 = new Figure("H1");
        f4 = new Figure("C1");
        f5 = new Figure("A1");
        f6 = new Figure("D1");
        f7 = new Figure("E1");
        f8 = new Figure("F1");
        f9 = new Figure("A2");
        f10 = new Figure("B2");
        f11 = new Figure("C2");
        f12 = new Figure("D2");
        f13 = new Figure("E2");
        f14 = new Figure("F2");
        f15 = new Figure("G2");
        f16 = new Figure("H2");
        f17 = new Figure("E8");
        f18= new Figure("D8");
        f19= new Figure("A7");
        f20= new Figure("B8");
        f21= new Figure("G8");
        f22= new Figure("F8");
        f23= new Figure("C8");
        f24= new Figure("B7");
        f25= new Figure("A8");
        f26 = new Figure("H8");
        f27 = new Figure("H7");
        f28 = new Figure("G7");
        f29 = new Figure("F7");
        f30 = new Figure("E7");
        f31 = new Figure("D7");
        f32 = new Figure("C7");



        mapafigurica["B1"] = f;
        mapafigurica["G1"] = f2;
        mapafigurica["H1"] = f3;
        mapafigurica["C1"] = f4;
        mapafigurica["A1"] = f5;
        mapafigurica["D1"] = f6;
        mapafigurica["E1"] = f7;
        mapafigurica["F1"]=f8;
        mapafigurica["A2"] = f9;
        mapafigurica["B2"] = f10;
        mapafigurica["C2"] = f11;
        mapafigurica["D2"] = f12;
        mapafigurica["E2"] = f13;
        mapafigurica["F2"] = f14;
        mapafigurica["G2"] = f15;
        mapafigurica["H2"]=f16;
        mapafigurica["E8"] = f17;
        mapafigurica["D8"] = f18;
        mapafigurica["A7"] = f19;
        mapafigurica["B8"] = f20;
        mapafigurica["G8"] = f21;
        mapafigurica["F8"] = f22;
        mapafigurica["C8"] = f23;
        mapafigurica["B7"]= f24;
        mapafigurica["A8"] = f25;
        mapafigurica["H8"] = f26;
        mapafigurica["H7"] = f27;
        mapafigurica["G7"] = f28;
        mapafigurica["F7"] = f29;
        mapafigurica["E7"] = f30;
        mapafigurica["D7"] = f31;
        mapafigurica["C7"]=f32;








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

//        glm::vec3 pointLightPositions[] = {
//                glm::vec3( 1.f,  0.f,  1.0f),
//                glm::vec3( 19.f,  -20.f, 1.0f),
//                glm::vec3( 19.f,  0.f, 1.0f),
//                glm::vec3( 1.f,  -20.0f, 1.0f),
//                glm::vec3(4.f,-8.f,1.f),
//                glm::vec3(4.f,-10.f,1.f),
//                glm::vec3(16.f,-8.f,1.f),
//                glm::vec3(16.f,-10.f,1.f),
//        };


        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
        //dozvolimo odsecanje stranica
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        // stbi_set_flip_vertically_on_load(true);
        // build and compile our shader zprogram
        //tekstura i svetlo
        Shader skyShader("resources/shaders/skybox.vs","resources/shaders/skybox.fs");
        Shader boardShader("resources/shaders/board.vs", "resources/shaders/board.fs");
        Shader lightShader("resources/shaders/light.vs", "resources/shaders/light.fs");
        Shader modelShader("resources/shaders/model.vs", "resources/shaders/model.fs");
        // ------------------------------------
        Shader ourShader("resources/shaders/field.vs", "resources/shaders/field.fs");
        Model konjA(FileSystem::getPath("resources/objects/WoodenChess/12930_WoodenChessKnightSideA_v1_l3.obj"));
        Model lovacA(FileSystem::getPath("resources/objects/WoodenChessBishopSideA/WoodenChessBishop.obj"));
        Model piunA(FileSystem::getPath("resources/objects/WoodenChessPawnSideA/12931_WoodenChessPawnSideA_v1_l3.obj"));
        Model kraljicaA(FileSystem::getPath("resources/objects/WoodenChessQueenSideA_v1_L3.1/12927_Wooden_Chess_Queen_side_A_v1_l3.obj"));
        Model kraljA(FileSystem::getPath("resources/objects/WoodenChessKingSideA/12926_Wooden_Chess_King_Side_A_v1_l3.obj"));
        Model topB(FileSystem::getPath("resources/objects/topb/12934_Wooden_Chess_Rook_Side_B_V2_L3.obj"));
        Model topA(FileSystem::getPath("resources/objects/WoodenChessRookSideA/Wooden_Chess_Rook_.obj"));
        Model konjB(FileSystem::getPath("resources/objects/konjbb/12936_Wooden_Chess_Knight_Side_B_V2_l3.obj"));
        Model lovacB(FileSystem::getPath("resources/objects/lovacb/12395_Wooden_Chess_Bishop_Side_B_V2_l3.obj"));
        Model kraljicaB(FileSystem::getPath("resources/objects/kraljicab/12933_Wooden_Chess_Queen_side_b_v1_l3.obj"));
        Model kraljB(FileSystem::getPath("resources/objects/kraljb/12932_Wooden_Chess_King_Side_B_V2_l3.obj"));
        Model piunB(FileSystem::getPath("resources/objects/piunb/12937_Wooden_Chess_Pawn_Side_B_V2_L3.obj"));
        Model rock(FileSystem::getPath("resources/objects/rock/rock.obj"));

        rock.SetShaderTextureNamePrefix("material.");

        PointLight pointLight;
        pointLight.ambient = glm::vec3(1.5, 1.5, 1.5);
        pointLight.diffuse = glm::vec3(0.7, 0.7, sin(glfwGetTime())/2.0+0.5);
        pointLight.specular = glm::vec3(1.0, 1.0, 1.0);
        pointLight.constant = 1.0f;
        pointLight.linear = 0.06f;
        pointLight.quadratic = 0.012f;
        pointLight.position = lightPos;
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

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
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 0.0f, 0.0f,


                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, //A
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f,//C
                0.5f, 0.5f, -0.5f, 1.0f, 1.0f,//B
                -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,//F
                0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // D
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

        float skyVertices[] = {
                // positions
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f,  1.0f
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

        unsigned int skyVAO, skyVBO;
        glGenVertexArrays(1, &skyVAO);
        glGenBuffers(1, &skyVBO);
        glBindVertexArray(skyVAO);
        glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyVertices), &skyVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


//        vector<std::string> faces
//                {
//                        FileSystem::getPath("resources/textures/UnionSquare/right.jpg"),
//                        FileSystem::getPath("resources/textures/UnionSquare/left.jpg"),
//                        FileSystem::getPath("resources/textures/UnionSquare/top.jpg"),
//                        FileSystem::getPath("resources/textures/UnionSquare/bottom.jpg"),
//                        FileSystem::getPath("resources/textures/UnionSquare/posz.jpg"),
//                        FileSystem::getPath("resources/textures/UnionSquare/back.jpg")
//                };
        vector<std::string> faces
                {
                        FileSystem::getPath("resources/textures/PiazzaDelPopolo1/posx.jpg"),
                        FileSystem::getPath("resources/textures/PiazzaDelPopolo1/negx.jpg"),
                        FileSystem::getPath("resources/textures/PiazzaDelPopolo1/posy.jpg"),
                        FileSystem::getPath("resources/textures/PiazzaDelPopolo1/negy.jpg"),
                        FileSystem::getPath("resources/textures/PiazzaDelPopolo1/posz.jpg"),
                        FileSystem::getPath("resources/textures/PiazzaDelPopolo1/negz.jpg")
                };

        unsigned int cubemapTexture =  loadCubemap(faces);


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

        skyShader.use();
        skyShader.setInt("skybox", 0);


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


            boardShader.setVec3("light.direction", lightDir);
            boardShader.setVec3("viewPos", camera.Position);

            boardShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
            boardShader.setVec3("light.diffuse", 0.7, 0.7, sin(glfwGetTime())/2.0+0.5);
            boardShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

            boardShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
            boardShader.setFloat("material.shininess", 32.0f);

            // create transformations
            glm::mat4 model = glm::mat4(1.0f);

            glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 projection = glm::mat4(1.0f);


            //ovde se salje globalna promenljiva fov koja se menja na scroll preko callbacka
            projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            view = glm::lookAt(camera.Position, camera.Position+camera.Front, camera.Up);

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
            lightShader.setVec3("color", 0.7, 0.7, sin(glfwGetTime())/2.0+0.5);
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

            string field1 = f->getField();
            string field2 = f2->getField();
            string field3 = f3->getField();
            string field4 = f4->getField();
            string field5 = f5->getField();
            string field6 = f6->getField();
            string field7 = f7->getField();
            string field8 = f8->getField();
            string field9 = f9->getField();
            string field10 = f10->getField();
            string field11 = f11->getField();
            string field12= f12->getField();
            string field13= f13->getField();
            string field14= f14->getField();
            string field15= f15->getField();
            string field16= f16->getField();
            string field17 = f17->getField();
            string field18= f18->getField();
            string field19= f19->getField();
            string field20= f20->getField();
            string field21= f21->getField();
            string field22= f22->getField();
            string field23= f23->getField();
            string field24= f24->getField();
            string field25= f25->getField();
            string field26 = f26->getField();
            string field27 = f27->getField();
            string field28= f28->getField();
            string field29= f29->getField();
            string field30= f30->getField();
            string field31= f31->getField();
            string field32= f32->getField();



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

            // world transformation
            model = glm::mat4(1.0f);
            model = translate(model, glm::vec3(0.0f, -2.0f, -1.0f));
            model = scale(model, glm::vec3(8.0f, 2.0f, 6.0f));

            modelShader.use();
            modelShader.setVec3("pointLight.position",pointLight.position);
            modelShader.setVec3("pointLight.ambient",pointLight.ambient);
            modelShader.setVec3("pointLight.diffuse",pointLight.diffuse);
            modelShader.setVec3("pointLight.specular",pointLight.specular);
            modelShader.setFloat("pointLight.constant",pointLight.constant);
            modelShader.setFloat("pointLight.linear",pointLight.linear);
            modelShader.setFloat("pointLight.quadratic",pointLight.quadratic);

            modelShader.setVec3("viewPosition", camera.Position);
            modelShader.setFloat("material.shininess", 64.0f);
            modelShader.setMat4("projection", projection);
            modelShader.setMat4("view", view);



            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field1][0], mapa[field1][1], mapa[field1][2])); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            konjA.Draw(modelShader);



            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field2][0], mapa[field2][1], mapa[field2][2])); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            konjA.Draw(modelShader);




//
            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field4][0]-0.02f, mapa[field4][1], mapa[field4][2]-0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            lovacA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field8][0]-0.02f, mapa[field8][1], mapa[field8][2]-0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            lovacA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field16][0]-0.9, mapa[field16][1], mapa[field16][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field9][0]-0.9, mapa[field9][1], mapa[field9][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field10][0]-0.9, mapa[field10][1], mapa[field10][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field11][0]-0.9, mapa[field11][1], mapa[field11][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field12][0]-0.9, mapa[field12][1], mapa[field12][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field13][0]-0.9, mapa[field13][1], mapa[field13][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field14][0]-0.9, mapa[field14][1], mapa[field14][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field15][0]-0.9, mapa[field15][1], mapa[field15][2]+0.9f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunA.Draw(modelShader);


            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field6][0], mapa[field6][1], mapa[field6][2]-1.7f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            kraljicaA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field7][0], mapa[field7][1], mapa[field7][2]-2.5f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            kraljA.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field17][0]-5.9f, mapa[field17][1], mapa[field17][2]-2.6f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            kraljB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field18][0]-5.9f, mapa[field18][1], mapa[field18][2]-1.8f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            kraljicaB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field20][0]-5.85f, mapa[field20][1], mapa[field20][2]-4.4f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            konjB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field21][0]-5.85f, mapa[field21][1], mapa[field21][2]-4.4f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            konjB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field22][0]-5.9f, mapa[field22][1], mapa[field22][2]-3.5f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            lovacB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field23][0]-5.9f, mapa[field23][1], mapa[field23][2]-3.5f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            lovacB.Draw(modelShader);


            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field25][0]-5.9f, mapa[field25][1], mapa[field25][2]-5.3f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            topB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field26][0]-5.9f, mapa[field26][1], mapa[field26][2]-5.3f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            topB.Draw(modelShader);



            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field27][0]-4.9f, mapa[field27][1], mapa[field27][2]-5.15f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field28][0]-4.9f, mapa[field28][1], mapa[field28][2]-5.15f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field29][0]-4.9f, mapa[field29][1], mapa[field29][2]-5.15f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field30][0]-4.9f, mapa[field30][1], mapa[field30][2]-5.15f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field31][0]-4.9f, mapa[field31][1], mapa[field31][2]-5.15f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field32][0]-4.9f, mapa[field32][1], mapa[field32][2]-5.2f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field24][0]-4.9f, mapa[field24][1], mapa[field24][2]-5.15f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);

            model = glm::mat4(1.0f);
            model = glm::translate(model,glm::vec3(mapa[field19][0]-4.9f, mapa[field19][1], mapa[field19][2]-5.13f)); // translate it down so it's at the center of the scene
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(-5.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(0.18f));    // it's a bit too big for our scene, so scale it down
            modelShader.setMat4("model", model);
            piunB.Draw(modelShader);



            glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
            skyShader.use();
            view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
            skyShader.setMat4("view", view);
            projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, Z_NEAR, Z_FAR);

            skyShader.setMat4("projection", projection);
            // skybox cube
            glBindVertexArray(skyVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
            glDepthFunc(GL_LESS);



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
        glDeleteVertexArrays(1,&skyVAO);


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
            camera.Position += cameraSpeed * camera.Front;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.Position -= cameraSpeed * camera.Front;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            camera.Position-= glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            camera.Position += glm::normalize(glm::cross(camera.Front, camera.Up)) * cameraSpeed;

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
        camera.Front = glm::normalize(front);


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
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_2 and action == GLFW_PRESS) {
            dest += "2";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_3 and action == GLFW_PRESS) {
            dest += "3";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_4 and action == GLFW_PRESS) {
            dest += "4";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_5 and action == GLFW_PRESS) {
            dest += "5";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_6 and action == GLFW_PRESS) {
            dest += "6";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_7 and action == GLFW_PRESS) {
            dest += "7";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
        if (key == GLFW_KEY_8 and action == GLFW_PRESS) {
            dest += "8";
            std::cout << dest << std::endl;
            if(mapafigurica[src] != nullptr){
                mapafigurica[src]->setField(dest);
                mapafigurica[dest] = mapafigurica[src];
                mapafigurica[src] = nullptr;
            }
            ind = true;
        }
    }
}

unsigned int loadCubemap(vector<string> faces) {

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    return textureID;
}



