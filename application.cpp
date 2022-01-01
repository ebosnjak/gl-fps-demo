#include "application.h"

bool Application::firstMouse = true;
uint8_t Application::mouseState;     // bits represent: scrollDown|scrollUp|lastRMB|lastMMB|lastLMB|RMB|MMB|LMB
double Application::mouseX, Application::mouseY, Application::lastMouseX, Application::lastMouseY;
uint16_t Application::keyState[32], Application::lastKeyState[32];
bool Application::isFocused;
bool Application::isCursorLocked;

Application::Application(int w, int h) {
    for (int i = 0; i < 32; i++) {
        keyState[i] = 0;
        lastKeyState[i] = 0;
    }

    mouseState = 0;

    isCursorLocked = false;
    isFocused = true;

    windowWidth = w;
    windowHeight = h;

    isRunning = false;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    window = glfwCreateWindow(windowWidth, windowHeight, "opengl window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Error: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowPos(window, 200, 200);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetWindowFocusCallback(window, WindowFocusCallback);

    LoadGLProcs();
    std::cout << "Success: Loaded GL functions" << std::endl;

    glViewport(0, 0, windowWidth, windowHeight);
}

Application::~Application() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::Run() {
    Init();

    auto lastT = clock.now();

    isRunning = true;
    while (isRunning) {
        if (glfwWindowShouldClose(window)) {
            isRunning = false;
            break;
        }

        auto currentT = clock.now();
        float delta = std::chrono::duration_cast< std::chrono::duration< float, std::milli > >(currentT - lastT).count() / 1000.0f;
        lastT = currentT;
        Update(delta);
        Draw();

        for (int i = 0; i < 32; i++) {
            lastKeyState[i] = keyState[i];
        }

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        mouseState &= ~(3 << 6);                // clear scroll up/down flags (not used for now)
        mouseState &= ~(7 << 3);                // clear last mouse state;
        mouseState |= ((mouseState & 7) << 3);  // set last mouse state to current mouse state

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Cleanup();
}

bool Application::IsButtonDown(Mouse button) {
    uint8_t id = static_cast< uint8_t >(button);
    return mouseState & (1 << id);
}

bool Application::IsButtonPressed(Mouse button) {
    uint8_t id = static_cast< uint8_t >(button);
    return (mouseState & (1 << id)) && !(mouseState & (1 << (id + 3)));
}

bool Application::IsButtonUp(Mouse button) {
    uint8_t id = static_cast< uint8_t >(button);
    return !(mouseState & (1 << id));
}

bool Application::IsButtonReleased(Mouse button) {
    uint8_t id = static_cast< uint8_t >(button);
    return !(mouseState & (1 << id)) && (mouseState & (1 << (id + 3)));
}
bool Application::IsKeyDown(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    return keyState[id / 16] & (1 << (id % 16));
}

bool Application::IsKeyPressed(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    return (keyState[id / 16] & (1 << (id % 16))) && !(lastKeyState[id / 16] & (1 << (id % 16)));
}

bool Application::IsKeyUp(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    return !(keyState[id / 16] & (1 << (id % 16)));
}

bool Application::IsKeyReleased(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    return !(keyState[id / 16] & (1 << (id % 16))) && (lastKeyState[id / 16] & (1 << (id % 16)));
}

glm::vec2 Application::GetMousePos() {
    return glm::vec2(mouseX, mouseY);
}

glm::vec2 Application::GetMouseDelta() {
    return glm::vec2(mouseX - lastMouseX, mouseY - lastMouseY);
}

void Application::FramebufferSizeCallback(GLFWwindow* wnd, int w, int h) {
    glViewport(0, 0, w, h);
}

void Application::KeyCallback(GLFWwindow* wnd, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UNKNOWN) 
        return;

    if (action == GLFW_PRESS) {
        keyState[key / 16] |= (1 << (key % 16));
    }
    else if (action == GLFW_RELEASE) {  
        keyState[key / 16] &= ~(1 << (key % 16));
    }
}

void Application::MouseButtonCallback(GLFWwindow* wnd, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            mouseState |= 1;
        }
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            mouseState |= (1 << 2);
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            mouseState |= (1 << 1);
        }
    }
    else if (action == GLFW_RELEASE) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            mouseState &= ~1;
        }
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            mouseState &= ~(1 << 2);
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            mouseState &= ~(1 << 1);
        }
    }
}

void Application::CursorPosCallback(GLFWwindow* wnd, double x, double y) {
    if (firstMouse) {
        firstMouse = false;
        lastMouseX = x;
        lastMouseY = y;
    }
    else {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    mouseX = x;
    mouseY = y;
}

void Application::WindowFocusCallback(GLFWwindow* wnd, int focused) {
    isFocused = focused;
    if (!isFocused) {
        glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Application::SetCursorLocked(bool locked) {
    if (isCursorLocked == locked) return;
    
    isCursorLocked = locked;
    if (isCursorLocked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

bool Application::IsWindowFocused() {
    return isFocused;
}