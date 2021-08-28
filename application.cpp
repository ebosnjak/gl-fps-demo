#include "application.h"

Application::Application(int w, int h) {
    for (int i = 0; i < 32; i++) {
        keyState[i] = 0;
        lastKeyState[i] = 0;
    }

    mouseState = 0;

    windowWidth = w;
    windowHeight = h;

    dpy = XOpenDisplay(NULL);
    wnd = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 
                                    100, 100,   // (x, y)
                                    windowWidth, windowHeight,  // width, height
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

    if (fbConfigs == nullptr) {
        std::cout << "Error: glXChooseFBConfig failed" << std::endl;
        return;
    }

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 
        (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    if (glXCreateContextAttribsARB == nullptr) {
        std::cout << "Error: glXGetProcAddress failed" << std::endl;
        return;
    }    

    int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        None
    };

    ctx = glXCreateContextAttribsARB(dpy, fbConfigs[0], NULL, true, contextAttribs);
    
    if (ctx == nullptr) {
        std::cout << "Error: glXCreateContextAttribsARB failed" << std::endl;
        return;
    }

    long eventMask = KeyPressMask | KeyReleaseMask | KeymapStateMask | StructureNotifyMask |
                    PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask;
    
    XSelectInput(dpy, wnd, eventMask);

    XkbSetDetectableAutoRepeat(dpy, true, NULL);    

    XStoreName(dpy, wnd, "opengl window");
    XMapWindow(dpy, wnd);
    glXMakeCurrent(dpy, wnd, ctx);

    std::cout << "Success: GL context created and window opened" << std::endl;

    isRunning = false;

    LoadGLProcs();

    std::cout << "Success: Loaded GL functions" << std::endl;

    glViewport(0, 0, windowWidth, windowHeight);
}

Application::~Application() {
    glXDestroyContext(dpy, ctx);
    XDestroyWindow(dpy, wnd);
    XCloseDisplay(dpy);
}

void Application::Run() {
    Atom wmDeleteWindow = XInternAtom(dpy, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(dpy, wnd, &wmDeleteWindow, 1);

    Init();

    auto lastT = clock.now();

    isRunning = true;
    while (isRunning) {
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
                    isRunning = false;
                    break;
                }
            }
            else if (evt.type == ConfigureNotify) {
                if (evt.xconfigure.width != windowWidth || evt.xconfigure.height != windowHeight) {
                    windowWidth = evt.xconfigure.width;
                    windowHeight = evt.xconfigure.height;
                    glViewport(0, 0, windowWidth, windowHeight);
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

        auto currentT = clock.now();
        float delta = std::chrono::duration_cast< std::chrono::duration< float, std::milli > >(currentT - lastT).count() / 1000.0f;
        lastT = currentT;
        Update(delta);

        Draw();
        
        glXSwapBuffers(dpy, wnd);
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
    KeyCode kcode = XKeysymToKeycode(dpy, id);
    return (keyState[kcode / 8] & (1 << (kcode % 8)));
}

bool Application::IsKeyPressed(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    KeyCode kcode = XKeysymToKeycode(dpy, id);
    return (keyState[kcode / 8] & (1 << (kcode % 8))) && !(lastKeyState[kcode / 8] & (1 << (kcode % 8)));
}

bool Application::IsKeyUp(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    KeyCode kcode = XKeysymToKeycode(dpy, id);
    return !(keyState[kcode / 8] & (1 << (kcode % 8)));
}

bool Application::IsKeyReleased(Keys key) {
    unsigned int id = static_cast< unsigned int >(key);
    KeyCode kcode = XKeysymToKeycode(dpy, id);
    return !(keyState[kcode / 8] & (1 << (kcode % 8))) && (lastKeyState[kcode / 8] & (1 << (kcode % 8)));
}