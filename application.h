#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <cstddef>
#include <chrono>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/extensions/Xfixes.h>

#include "glfuncs.h"
#include "mathhelper.h"

typedef GLXContext (*glXCreateContextAttribsARBProc) 
    (Display*, GLXFBConfig, GLXContext, bool, const int*);

enum class Mouse {
    Left = 0,
    Mid = 1,
    Right = 2,
};

enum class Keys {
    LShift     = XK_Shift_L,
    RShift     = XK_Shift_R,      
    LControl   = XK_Control_L,    
    RControl   = XK_Control_R,    
    LAlt       = XK_Alt_L,        
    RAlt       = XK_Alt_R,        
    LSystem    = XK_Super_L,      
    RSystem    = XK_Super_R,      
    Menu       = XK_Menu,         
    Escape     = XK_Escape,       
    Semicolon  = XK_semicolon,    
    Slash      = XK_slash,        
    Equal      = XK_equal,        
    Hyphen     = XK_minus,        
    LBracket   = XK_bracketleft,  
    RBracket   = XK_bracketright, 
    Comma      = XK_comma,        
    Period     = XK_period,       
    Quote      = XK_apostrophe,   
    Backslash  = XK_backslash,    
    Tilde      = XK_grave,        
    Space      = XK_space,        
    Enter      = XK_Return,       
    Backspace  = XK_BackSpace,    
    Tab        = XK_Tab,          
    PageUp     = XK_Prior,        
    PageDown   = XK_Next,         
    End        = XK_End,          
    Home       = XK_Home,         
    Insert     = XK_Insert,       
    Delete     = XK_Delete,       
    Add        = XK_KP_Add,       
    Subtract   = XK_KP_Subtract,  
    Multiply   = XK_KP_Multiply,  
    Divide     = XK_KP_Divide,    
    Pause      = XK_Pause,        
    F1         = XK_F1,           
    F2         = XK_F2,           
    F3         = XK_F3,           
    F4         = XK_F4,           
    F5         = XK_F5,           
    F6         = XK_F6,           
    F7         = XK_F7,           
    F8         = XK_F8,           
    F9         = XK_F9,           
    F10        = XK_F10,          
    F11        = XK_F11,          
    F12        = XK_F12,          
    F13        = XK_F13,          
    F14        = XK_F14,          
    F15        = XK_F15,          
    Left       = XK_Left,         
    Right      = XK_Right,        
    Up         = XK_Up,           
    Down       = XK_Down,         
    Numpad0    = XK_KP_Insert,    
    Numpad1    = XK_KP_End,       
    Numpad2    = XK_KP_Down,      
    Numpad3    = XK_KP_Page_Down, 
    Numpad4    = XK_KP_Left,      
    Numpad5    = XK_KP_Begin,     
    Numpad6    = XK_KP_Right,     
    Numpad7    = XK_KP_Home,      
    Numpad8    = XK_KP_Up,        
    Numpad9    = XK_KP_Page_Up,   
    A          = XK_a,            
    B          = XK_b,            
    C          = XK_c,            
    D          = XK_d,            
    E          = XK_e,            
    F          = XK_f,            
    G          = XK_g,            
    H          = XK_h,            
    I          = XK_i,            
    J          = XK_j,            
    K          = XK_k,            
    L          = XK_l,            
    M          = XK_m,            
    N          = XK_n,            
    O          = XK_o,            
    P          = XK_p,            
    Q          = XK_q,            
    R          = XK_r,            
    S          = XK_s,            
    T          = XK_t,            
    U          = XK_u,            
    V          = XK_v,            
    W          = XK_w,            
    X          = XK_x,            
    Y          = XK_y,            
    Z          = XK_z,            
    Num0       = XK_0,            
    Num1       = XK_1,            
    Num2       = XK_2,            
    Num3       = XK_3,            
    Num4       = XK_4,            
    Num5       = XK_5,            
    Num6       = XK_6,            
    Num7       = XK_7,            
    Num8       = XK_8,            
    Num9       = XK_9,                         
};

class Application {
private:
    bool isCursorLocked;

public:
    std::chrono::high_resolution_clock clock;    

    Display* dpy;
    Window wnd;
    GLXContext ctx;

    bool isRunning;

    int windowWidth, windowHeight;

    uint8_t mouseState;     // bits represent: scrollDown|scrollUp|lastRMB|lastMMB|lastLMB|RMB|MMB|LMB
    int mouseX, mouseY, lastMouseX, lastMouseY;
    uint8_t keyState[32], lastKeyState[32];

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
};

#endif