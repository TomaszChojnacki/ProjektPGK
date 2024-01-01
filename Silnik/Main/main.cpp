#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <../Opengl/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"

#include <iostream>

/// Deklaracja funkcji 
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

/// Ustawienie wielkosci okna  
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

/// Ustawienie kamery
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	/// Yaw jest inicjalizowany na -90.0 stopni poniewaz yaw o wartosci 0.0 
                    /// skutkuje wektorem kierunkowym wskazuj¹cym na prawo wiec poczatkowo obracamy sie nieco w lewo
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;

/// Czas 
float deltaTime = 0.0f;	/// Ustawienie czasu miedzy obecna a ostania klatka
float lastFrame = 0.0f;

int main(void)
{
    /// Inicjalizacja i konfiguracja GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /// Tworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    /// Informujemy GLFW aby przechwytywal polozenie myszki
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /// Ladowanie wskaznikow funkcji OpenG glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /// Konfiguracja globalnego stanu OpenGL
    glEnable(GL_DEPTH_TEST);

    /// Kompilowanie naszego programu shaderowego i przkierowanie do tych plikow 
    Shader ourShader("Silnik/Assets/Shaders/shader.vs", "Silnik/Assets/Shaders/shader.fs");
    
    /// Ustawienie danych wierzcholkow i buforow oraz konfiguracja atrybutow wierzcholkow
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    /// Pozycje szescianow w przestrzeni swiata
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /// Atrybut pozycji
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /// Atrybut koordynatow tekstury
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /// Ladowanie i tworzenie tekstur
    unsigned int texture1, texture2;
    /// Tekstura 1 
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    /// Ustawianie parametrow zawijania tekstur
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /// ustawianie parametrow filtrowania tekstur w celu zeby nie bylo rozpikselowane
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /// zaladuj obraz utworz teksture i wygeneruj mipmapy
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); /// przeslij stb_image.h aby odwrocil zaladowane tekstury na osi Y "zeby nie byly do gory nogami"
    unsigned char* data = stbi_load("Silnik/resources/textures/sciana.png", &width, &height, &nrChannels, 0); /// ladowanie grafiki sciany szescianu
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

    /// takstura 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    /// ustaw parametry zawijania tekstur
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /// ustawianie parametrow filtrowania tekstur w celu zeby nie bylo rozpikselowane
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /// zaladuj obraz naszego zepolu czyli tworzenie tekstury na sciane kwadratu i wygeneracja mipmapy
     data = stbi_load("Silnik/resources/textures/zespol.png", &width, &height, &nrChannels, 0);
     if (data)
     {
         /// dodanie takstury 2D na kanal alfa i wyslanie informacji do bibliteki ze tekstura jest przezroczysta czyli typ danych to GL_RGBA
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
         glGenerateMipmap(GL_TEXTURE_2D);
     }
     else
     {
         std::cout << "Failed to load texture" << std::endl;
     }
     stbi_image_free(data);

     /// informacja do ktorej jednostki tekstury nalezy sie odwolac i uruchomienie shaderow
     ourShader.use();
     ourShader.setInt("texture1", 0);
     ourShader.setInt("texture2", 1);


     /// glowna petla programu do renderowania 
     while (!glfwWindowShouldClose(window))
     {
         /// ustawienie logiki czasu na klatke 
         float currentFrame = static_cast<float>(glfwGetTime());
         deltaTime = currentFrame - lastFrame;
         lastFrame = currentFrame;

         // Obsluga wejscia danych do okna
         processInput(window);

         /// Renderowanie
         glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         /// Wiazanie tekstur z odpowiadajacymi im jednostkami tekstur
         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, texture1);
         glActiveTexture(GL_TEXTURE1);
         glBindTexture(GL_TEXTURE_2D, texture2);

         /// Aktywacja shadera
         ourShader.use();

         /// Przekazywanie macierzy projekcji do shadera
         glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
         ourShader.setMat4("projection", projection);

         /// Transformacja kamery
         glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
         ourShader.setMat4("view", view);

         /// Renderowanie szescianow
         glBindVertexArray(VAO);
         for (unsigned int i = 0; i < 10; i++)
         {
             /// Obliczanie macierzy modelu dla kazdego obiektu i przekazywanie go do shadera przed wyrenderowaniem
             glm::mat4 model = glm::mat4(1.0f); // inicjowanie macierzy do macierzy glownej 
             model = glm::translate(model, cubePositions[i]);
             float angle = 20.0f * i;
             model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
             ourShader.setMat4("model", model);

             glDrawArrays(GL_TRIANGLES, 0, 36);
         }

         /// zniamna bufora i zapisanie kazdego zdarzenia czyli wcisniecia lub zwolnienia klawisza i poruszania myszka
         glfwSwapBuffers(window);
         glfwPollEvents();
     }

     /// zwolnienie zasobow z pamieci jesli wykonaja swoje zadanie 
     glDeleteVertexArrays(1, &VAO);
     glDeleteBuffers(1, &VBO);

     /// Zakonczenie i zwolnienie wszystkich zasobow przydzielonych przez GLFW.
     glfwTerminate();
     return 0;
}

/// Obsluga wejscia sprawdzanie czy w danej klatce zostaly nacisniete/puszczone klawisze
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}


/// glfw ta funkcja wykonuje sie za kazdym razem kiedy zmienia sie rozmiar okna czy to systemowo czy przez uzytkownika
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/// glfw: za kazdym razem gdy poruszymy mysz¹ wywolywana jest ta funkcja ktora zwraca pozycje
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; /// odwrocenie poniewaz wspolrzedne y biegna od dolu do gory
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; /// czulosc myszy usawiona na 0.1
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    /// sprawdzanie czy obszar nie jest poza zakresem zeby ekran nie zostal odwrocony
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

/// za kazdym razem kiedy przsuniemy scrolem zmienia sie widok kamery 
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}