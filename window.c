#include "window.h"

GameWindow* GameWindow_Create(int w, int h) {
    GameWindow* ret = (GameWindow *) malloc(sizeof(GameWindow));

    ret->dpy = XOpenDisplay(NULL);
    ret->wnd = XCreateSimpleWindow(ret->dpy, DefaultRootWindow(ret->dpy), 
                                    100, 100,   // (x, y)
                                    w, h,  // width, height
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
    GLXFBConfig *fbConfigs = glXChooseFBConfig(ret->dpy, DefaultScreen(ret->dpy), attribs, &nFbConfigs);

    if (fbConfigs == NULL) {
        printf("Error: glXChooseFBConfig failed\n");
        return NULL;
    }

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 
        (glXCreateContextAttribsARBProc) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");

    if (glXCreateContextAttribsARB == NULL) {
        printf("Error: glXGetProcAddress failed\n");
        return NULL;
    }    

    int contextAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        None
    };

    ret->ctx = glXCreateContextAttribsARB(ret->dpy, fbConfigs[0], NULL, true, contextAttribs);
    
    if (ret->ctx == NULL) {
        printf("Error: glXCreateContextAttribsARB failed\n");
        return NULL;
    }

    long eventMask = KeyPressMask | KeyReleaseMask | KeymapStateMask | 
                    PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask;
    
    XSelectInput(ret->dpy, ret->wnd, eventMask);

    XkbSetDetectableAutoRepeat(ret->dpy, true, NULL);    

    XStoreName(ret->dpy, ret->wnd, "opengl window");
    XMapWindow(ret->dpy, ret->wnd);
    glXMakeCurrent(ret->dpy, ret->wnd, ret->ctx);

    printf("Success: GL context created and window opened\n");

    ret->isRunning = false;

    LoadGLFuncs();

    printf("Success: Loaded GL functions\n");

    return ret;
}

void GameWindow_Run(GameWindow *g, void (*initFunc)(), void (*updateFunc)(float), void (*drawFunc)()) {
    Atom wmDeleteWindow = XInternAtom(g->dpy, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(g->dpy, g->wnd, &wmDeleteWindow, 1);

    initFunc();

    g->isRunning = true;
    while (g->isRunning) {
        for (int i = 0; i < 32; i++) {
            g->lastKeyState[i] = g->keyState[i];
        }

        g->mouseState &= ~(3 << 6);                // clear scroll up/down flags (not used for now)
        g->mouseState &= ~(7 << 3);                // clear last mouse state;
        g->mouseState |= ((g->mouseState & 7) << 3);  // set last mouse state to current mouse state

        XEvent evt;
        while (XPending(g->dpy)) {
            XNextEvent(g->dpy, &evt);

            KeySym ksym = 0;
            int len = 0;
            char str[25] = {0};
            if (evt.type == ClientMessage) {
                if (evt.xclient.data.l[0] == wmDeleteWindow) {
                    g->isRunning = false;
                    break;
                }
            }
            else if (evt.type == KeymapNotify) {
                XRefreshKeyboardMapping(&evt.xmapping);
            }
            else if (evt.type == KeyPress) {
                KeyCode kcode = evt.xkey.keycode;
                g->keyState[kcode / 8] |= (1 << (kcode % 8));
            }
            else if (evt.type == KeyRelease) {
                KeyCode kcode = evt.xkey.keycode;
                g->keyState[kcode / 8] &= ~(1 << (kcode % 8));
            }
            else if (evt.type == MotionNotify) {
                g->mouseX = evt.xmotion.x;
                g->mouseY = evt.xmotion.y;
            }
            else if (evt.type == ButtonPress) {
                if (evt.xbutton.button == 1) {
                    g->mouseState |= 1;
                }
                else if (evt.xbutton.button == 2) {
                    g->mouseState |= (1 << 1);
                }
                else if (evt.xbutton.button == 3) {
                    g->mouseState |= (1 << 2);
                }
                else if (evt.xbutton.button == 4) {
                    g->mouseState |= (1 << 6);
                }
                else if (evt.xbutton.button == 5) {
                    g->mouseState |= (1 << 7);
                }
            }
            else if (evt.type == ButtonRelease) {
                if (evt.xbutton.button == 1) {
                    g->mouseState &= ~1;
                }
                else if (evt.xbutton.button == 2) {
                    g->mouseState &= ~(1 << 1);
                }
                else if (evt.xbutton.button == 3) {
                    g->mouseState &= ~(1 << 2);
                }
            }
        }

        updateFunc(0.0f);

        drawFunc();
        
        glXSwapBuffers(g->dpy, g->wnd);
    }
}

void GameWindow_Destroy(GameWindow* g) {
    glXDestroyContext(g->dpy, g->ctx);
    XDestroyWindow(g->dpy, g->wnd);
    XCloseDisplay(g->dpy);
}