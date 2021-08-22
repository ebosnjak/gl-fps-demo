#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

typedef GLXContext (*glXCreateContextAttribsARBProc) 
    (Display*, GLXFBConfig, GLXContext, bool, const int*);

enum {
    Mouse_Left = 0,
    Mouse_Mid = 1,
    Mouse_Right = 2,
    Scroll_Up = 1,
    Scroll_Down = -1,
    Scroll_None = 0
};

typedef enum {
    Key_LShift     = XK_Shift_L,
    Key_RShift     = XK_Shift_R,      
    Key_LControl   = XK_Control_L,    
    Key_RControl   = XK_Control_R,    
    Key_LAlt       = XK_Alt_L,        
    Key_RAlt       = XK_Alt_R,        
    Key_LSystem    = XK_Super_L,      
    Key_RSystem    = XK_Super_R,      
    Key_Menu       = XK_Menu,         
    Key_Escape     = XK_Escape,       
    Key_Semicolon  = XK_semicolon,    
    Key_Slash      = XK_slash,        
    Key_Equal      = XK_equal,        
    Key_Hyphen     = XK_minus,        
    Key_LBracket   = XK_bracketleft,  
    Key_RBracket   = XK_bracketright, 
    Key_Comma      = XK_comma,        
    Key_Period     = XK_period,       
    Key_Quote      = XK_apostrophe,   
    Key_Backslash  = XK_backslash,    
    Key_Tilde      = XK_grave,        
    Key_Space      = XK_space,        
    Key_Enter      = XK_Return,       
    Key_Backspace  = XK_BackSpace,    
    Key_Tab        = XK_Tab,          
    Key_PageUp     = XK_Prior,        
    Key_PageDown   = XK_Next,         
    Key_End        = XK_End,          
    Key_Home       = XK_Home,         
    Key_Insert     = XK_Insert,       
    Key_Delete     = XK_Delete,       
    Key_Add        = XK_KP_Add,       
    Key_Subtract   = XK_KP_Subtract,  
    Key_Multiply   = XK_KP_Multiply,  
    Key_Divide     = XK_KP_Divide,    
    Key_Pause      = XK_Pause,        
    Key_F1         = XK_F1,           
    Key_F2         = XK_F2,           
    Key_F3         = XK_F3,           
    Key_F4         = XK_F4,           
    Key_F5         = XK_F5,           
    Key_F6         = XK_F6,           
    Key_F7         = XK_F7,           
    Key_F8         = XK_F8,           
    Key_F9         = XK_F9,           
    Key_F10        = XK_F10,          
    Key_F11        = XK_F11,          
    Key_F12        = XK_F12,          
    Key_F13        = XK_F13,          
    Key_F14        = XK_F14,          
    Key_F15        = XK_F15,          
    Key_Left       = XK_Left,         
    Key_Right      = XK_Right,        
    Key_Up         = XK_Up,           
    Key_Down       = XK_Down,         
    Key_Numpad0    = XK_KP_Insert,    
    Key_Numpad1    = XK_KP_End,       
    Key_Numpad2    = XK_KP_Down,      
    Key_Numpad3    = XK_KP_Page_Down, 
    Key_Numpad4    = XK_KP_Left,      
    Key_Numpad5    = XK_KP_Begin,     
    Key_Numpad6    = XK_KP_Right,     
    Key_Numpad7    = XK_KP_Home,      
    Key_Numpad8    = XK_KP_Up,        
    Key_Numpad9    = XK_KP_Page_Up,   
    Key_A          = XK_a,            
    Key_B          = XK_b,            
    Key_C          = XK_c,            
    Key_D          = XK_d,            
    Key_E          = XK_e,            
    Key_F          = XK_f,            
    Key_G          = XK_g,            
    Key_H          = XK_h,            
    Key_I          = XK_i,            
    Key_J          = XK_j,            
    Key_K          = XK_k,            
    Key_L          = XK_l,            
    Key_M          = XK_m,            
    Key_N          = XK_n,            
    Key_O          = XK_o,            
    Key_P          = XK_p,            
    Key_Q          = XK_q,            
    Key_R          = XK_r,            
    Key_S          = XK_s,            
    Key_T          = XK_t,            
    Key_U          = XK_u,            
    Key_V          = XK_v,            
    Key_W          = XK_w,            
    Key_X          = XK_x,            
    Key_Y          = XK_y,            
    Key_Z          = XK_z,            
    Key_Num0       = XK_0,            
    Key_Num1       = XK_1,            
    Key_Num2       = XK_2,            
    Key_Num3       = XK_3,            
    Key_Num4       = XK_4,            
    Key_Num5       = XK_5,            
    Key_Num6       = XK_6,            
    Key_Num7       = XK_7,            
    Key_Num8       = XK_8,            
    Key_Num9       = XK_9,                         
} Keys;

Display *dpy;

uint8_t mouseState;     // bits represent: scrollDown|scrollUp|lastRMB|lastMMB|lastLMB|RMB|MMB|LMB
int mouseX, mouseY, mouseGlobalX, mouseGlobalY;

uint8_t keyState[32], lastKeyState[32];

bool IsButtonDown(uint8_t button) {
    if (button < 0 || button > 2) 
        return false; 

    return mouseState & (1 << button);
}

bool IsButtonPressed(uint8_t button) {
    if (button < 0 || button > 2) 
        return false; 

    return (mouseState & (1 << button)) && !(mouseState & (1 << (button + 3)));
}

bool IsButtonUp(uint8_t button) {
    if (button < 0 || button > 2)
        return false;
    
    return !(mouseState & (1 << button));
}

bool IsButtonReleased(uint8_t button) {
    if (button < 0 || button > 2) 
        return false; 

    return !(mouseState & (1 << button)) && (mouseState & (1 << (button + 3)));
}

bool IsKeyDown(Keys key) {
    KeyCode kcode = XKeysymToKeycode(dpy, key);
    return keyState[kcode / 8] & (1 << (kcode % 8));
}

bool IsKeyPressed(Keys key) {
    KeyCode kcode = XKeysymToKeycode(dpy, key);
    return (keyState[kcode / 8] & (1 << (kcode % 8))) && !(lastKeyState[kcode / 8] & (1 << (kcode % 8)));
}

bool IsKeyUp(Keys key) {
    KeyCode kcode = XKeysymToKeycode(dpy, key);
    return !(keyState[kcode / 8] & (1 << (kcode % 8)));
}

bool IsKeyReleased(Keys key) {
    KeyCode kcode = XKeysymToKeycode(dpy, key);
    return !(keyState[kcode / 8] & (1 << (kcode % 8))) && (lastKeyState[kcode / 8] & (1 << (kcode % 8)));
}

int main() {
    dpy = XOpenDisplay(NULL);
    Window wnd = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 
                                    100, 100,   // (x, y)
                                    1280, 720,  // width, height
                                    0, 0,       // border width and height
                                    0);         // background
    
    int attribs[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER, true,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        None
    };

    int nFbConfigs = 0;
    GLXFBConfig *fbConfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy), attribs, &nFbConfigs);

    if (fbConfigs == NULL) {
        printf("Error: glXChooseFBConfig failed\n");
        return 1;
    }

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 
        (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    if (glXCreateContextAttribsARB == NULL) {
        printf("Error: glXGetProcAddress failed\n");
        return 1;
    }    

    int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        None
    };

    GLXContext ctx = glXCreateContextAttribsARB(dpy, fbConfigs[0], NULL, true, contextAttribs);
    
    if (ctx == NULL) {
        printf("Error: glXCreateContextAttribsARB failed\n");
        return 1;
    }

    long eventMask = KeyPressMask | KeyReleaseMask | KeymapStateMask | 
                    PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask;
    
    XSelectInput(dpy, wnd, eventMask);

    XkbSetDetectableAutoRepeat(dpy, true, NULL);    

    XStoreName(dpy, wnd, "opengl window");
    XMapWindow(dpy, wnd);
    glXMakeCurrent(dpy, wnd, ctx);

    printf("Success: GL context created and window opened\n");

    Atom wmDeleteWindow = XInternAtom(dpy, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(dpy, wnd, &wmDeleteWindow, 1);

    bool running = true;
    while (running) {
        // Input

        for (int i = 0; i < 32; i++) {
            lastKeyState[i] = keyState[i];
        }

        mouseState &= ~(3 << 6);                // clear scroll up/down flags (not used for now)
        mouseState &= ~(7 << 3);                // clear last mouse state;
        mouseState |= ((mouseState & 7) << 3);  // set last mouse state to current mouse state

        XEvent evt;
        while (XPending(dpy)) {
            XNextEvent(dpy, &evt);

            KeySym ksym = 0;
            int len = 0;
            char str[25] = {0};
            if (evt.type == ClientMessage) {
                if (evt.xclient.data.l[0] == wmDeleteWindow) {
                    running = false;
                    break;
                }
            }
            else if (evt.type == KeymapNotify) {
                XRefreshKeyboardMapping(&evt.xmapping);
            }
            else if (evt.type == KeyPress) {
                KeyCode kcode = evt.xkey.keycode;
                keyState[kcode / 8] |= (1 << (kcode % 8));
            }
            else if (evt.type == KeyRelease) {
                KeyCode kcode = evt.xkey.keycode;
                keyState[kcode / 8] &= ~(1 << (kcode % 8));
            }
            else if (evt.type == MotionNotify) {
                mouseX = evt.xmotion.x;
                mouseY = evt.xmotion.y;
            }
            else if (evt.type == ButtonPress) {
                if (evt.xbutton.button == 1) {
                    mouseState |= 1;
                }
                else if (evt.xbutton.button == 2) {
                    mouseState |= (1 << 1);
                }
                else if (evt.xbutton.button == 3) {
                    mouseState |= (1 << 2);
                }
                else if (evt.xbutton.button == 4) {
                    mouseState |= (1 << 6);
                }
                else if (evt.xbutton.button == 5) {
                    mouseState |= (1 << 7);
                }
            }
            else if (evt.type == ButtonRelease) {
                if (evt.xbutton.button == 1) {
                    mouseState &= ~1;
                }
                else if (evt.xbutton.button == 2) {
                    mouseState &= ~(1 << 1);
                }
                else if (evt.xbutton.button == 3) {
                    mouseState &= ~(1 << 2);
                }
            }
        }

        if (IsKeyDown(Key_Escape)) {
            running = false;
            break;
        }

        // -----
        // Update 

        if (IsKeyPressed(Key_A)) {
            printf("A pressed\n");
        }
        if (IsKeyReleased(Key_A)) {
            printf("A released\n");
        }
        if (IsButtonPressed(Mouse_Left)) {
            printf("lmb pressed\n");
        }
        if (IsButtonReleased(Mouse_Left)) {
            printf("lmb released\n");
        }

        // -----
        // Draw

        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // -----
        
        glXSwapBuffers(dpy, wnd);
    }

    glXDestroyContext(dpy, ctx);
    XDestroyWindow(dpy, wnd);
    XCloseDisplay(dpy);

    return 0;
}