#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <chrono>

#include <GLFW/glfw3.h>

#include "glfuncs.h"
#include "mathhelper.h"

enum class Mouse {
    Left = GLFW_MOUSE_BUTTON_LEFT,
    Mid = GLFW_MOUSE_BUTTON_MIDDLE,
    Right = GLFW_MOUSE_BUTTON_RIGHT,
};

enum class Keys {
    LShift     = GLFW_KEY_LEFT_SHIFT,
    RShift     = GLFW_KEY_RIGHT_SHIFT,      
    LControl   = GLFW_KEY_LEFT_CONTROL,    
    RControl   = GLFW_KEY_RIGHT_CONTROL,    
    LAlt       = GLFW_KEY_LEFT_ALT,        
    RAlt       = GLFW_KEY_RIGHT_ALT,        
    LSystem    = GLFW_KEY_LEFT_SUPER,      
    RSystem    = GLFW_KEY_RIGHT_SUPER,      
    Menu       = GLFW_KEY_MENU,         
    Escape     = GLFW_KEY_ESCAPE,       
    Semicolon  = GLFW_KEY_SEMICOLON,    
    Slash      = GLFW_KEY_SLASH,        
    Equal      = GLFW_KEY_EQUAL,        
    Hyphen     = GLFW_KEY_MINUS,        
    LBracket   = GLFW_KEY_LEFT_BRACKET,  
    RBracket   = GLFW_KEY_RIGHT_BRACKET, 
    Comma      = GLFW_KEY_COMMA,        
    Period     = GLFW_KEY_PERIOD,       
    Quote      = GLFW_KEY_APOSTROPHE,   
    Backslash  = GLFW_KEY_BACKSLASH,        
    Space      = GLFW_KEY_SPACE,        
    Enter      = GLFW_KEY_ENTER,       
    Backspace  = GLFW_KEY_BACKSPACE,    
    Tab        = GLFW_KEY_TAB,          
    PageUp     = GLFW_KEY_PAGE_UP,        
    PageDown   = GLFW_KEY_PAGE_DOWN,         
    End        = GLFW_KEY_END,          
    Home       = GLFW_KEY_HOME,         
    Insert     = GLFW_KEY_INSERT,       
    Delete     = GLFW_KEY_DELETE,       
    Add        = GLFW_KEY_KP_ADD,       
    Subtract   = GLFW_KEY_KP_SUBTRACT,  
    Multiply   = GLFW_KEY_KP_MULTIPLY,  
    Divide     = GLFW_KEY_KP_DIVIDE,    
    Pause      = GLFW_KEY_PAUSE,        
    F1         = GLFW_KEY_F1,           
    F2         = GLFW_KEY_F2,           
    F3         = GLFW_KEY_F3,           
    F4         = GLFW_KEY_F4,           
    F5         = GLFW_KEY_F5,           
    F6         = GLFW_KEY_F6,           
    F7         = GLFW_KEY_F7,           
    F8         = GLFW_KEY_F8,           
    F9         = GLFW_KEY_F9,           
    F10        = GLFW_KEY_F10,          
    F11        = GLFW_KEY_F11,          
    F12        = GLFW_KEY_F12,          
    F13        = GLFW_KEY_F13,          
    F14        = GLFW_KEY_F14,          
    F15        = GLFW_KEY_F15,          
    Left       = GLFW_KEY_LEFT,         
    Right      = GLFW_KEY_RIGHT,        
    Up         = GLFW_KEY_UP,           
    Down       = GLFW_KEY_DOWN,           
    A          = GLFW_KEY_A,            
    B          = GLFW_KEY_B,            
    C          = GLFW_KEY_C,            
    D          = GLFW_KEY_D,            
    E          = GLFW_KEY_E,            
    F          = GLFW_KEY_F,            
    G          = GLFW_KEY_G,            
    H          = GLFW_KEY_H,            
    I          = GLFW_KEY_I,            
    J          = GLFW_KEY_J,            
    K          = GLFW_KEY_K,            
    L          = GLFW_KEY_L,            
    M          = GLFW_KEY_M,            
    N          = GLFW_KEY_N,            
    O          = GLFW_KEY_O,            
    P          = GLFW_KEY_P,            
    Q          = GLFW_KEY_Q,            
    R          = GLFW_KEY_R,            
    S          = GLFW_KEY_S,            
    T          = GLFW_KEY_T,            
    U          = GLFW_KEY_U,            
    V          = GLFW_KEY_V,            
    W          = GLFW_KEY_W,            
    X          = GLFW_KEY_X,            
    Y          = GLFW_KEY_Y,            
    Z          = GLFW_KEY_Z,            
    Num0       = GLFW_KEY_0,            
    Num1       = GLFW_KEY_1,            
    Num2       = GLFW_KEY_2,            
    Num3       = GLFW_KEY_3,            
    Num4       = GLFW_KEY_4,            
    Num5       = GLFW_KEY_5,            
    Num6       = GLFW_KEY_6,            
    Num7       = GLFW_KEY_7,            
    Num8       = GLFW_KEY_8,            
    Num9       = GLFW_KEY_9,                         
};

class Application {
private:
    static bool firstMouse;
    static uint8_t mouseState;     // bits represent: scrollDown|scrollUp|lastMMB|lastRMB|lastLMB|MMB|RMB|LMB
    static double mouseX, mouseY, lastMouseX, lastMouseY;
    static uint16_t keyState[32], lastKeyState[32];

    static bool isFocused;
    static bool isCursorLocked;

    static void FramebufferSizeCallback(GLFWwindow* wnd, int w, int h);
    static void KeyCallback(GLFWwindow* wnd, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* wnd, int button, int action, int mods);
    static void CursorPosCallback(GLFWwindow* wnd, double x, double y);
    static void WindowFocusCallback(GLFWwindow* wnd, int focused);

public:
    std::chrono::high_resolution_clock clock;    

    GLFWwindow* window;
    int windowWidth, windowHeight;
    bool isRunning;

    Application(int w, int h);

    ~Application();
    
    void Run();

    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void Cleanup() = 0;

    bool IsKeyDown(Keys key);
    bool IsKeyUp(Keys key);
    bool IsKeyPressed(Keys key);
    bool IsKeyReleased(Keys key);

    bool IsButtonDown(Mouse button);
    bool IsButtonUp(Mouse button);
    bool IsButtonPressed(Mouse button);
    bool IsButtonReleased(Mouse button);

    glm::vec2 GetMousePos();
    glm::vec2 GetMouseDelta();

    void SetCursorLocked(bool locked);

    bool IsWindowFocused();
};

#endif