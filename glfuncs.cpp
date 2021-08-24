#include "glfuncs.h"

PFNGLGENBUFFERSPROC					glGenBuffers;
PFNGLDELETEBUFFERSPROC				glDeleteBuffers;
PFNGLBINDBUFFERPROC					glBindBuffer;
PFNGLBUFFERDATAPROC					glBufferData;
PFNGLGENVERTEXARRAYSPROC			glGenVertexArrays;
PFNGLDELETEVERTEXARRAYSPROC			glDeleteVertexArrays;
PFNGLBINDVERTEXARRAYPROC			glBindVertexArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC	glEnableVertexAttribArray;
PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC		glVertexAttribPointer;
PFNGLCREATESHADERPROC				glCreateShader;
PFNGLSHADERSOURCEPROC				glShaderSource;
PFNGLCOMPILESHADERPROC				glCompileShader;
PFNGLGETSHADERIVPROC				glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
PFNGLDELETESHADERPROC				glDeleteShader;
PFNGLCREATEPROGRAMPROC				glCreateProgram;
PFNGLATTACHSHADERPROC				glAttachShader;
PFNGLLINKPROGRAMPROC				glLinkProgram;
PFNGLGETPROGRAMIVPROC				glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
PFNGLDELETEPROGRAMPROC				glDeleteProgram;
PFNGLUSEPROGRAMPROC					glUseProgram;
PFNGLUNIFORM1DPROC					glUniform1d;
PFNGLUNIFORM1DVPROC					glUniform1dv;
PFNGLUNIFORM1FPROC					glUniform1f;
PFNGLUNIFORM1FVPROC					glUniform1fv;
PFNGLUNIFORM1IPROC					glUniform1i;
PFNGLUNIFORM1IVPROC					glUniform1iv;
PFNGLUNIFORM2DPROC					glUniform2d;
PFNGLUNIFORM2DVPROC					glUniform2dv;
PFNGLUNIFORM2FPROC					glUniform2f;
PFNGLUNIFORM2FVPROC					glUniform2fv;
PFNGLUNIFORM2IPROC					glUniform2i;
PFNGLUNIFORM2IVPROC					glUniform2iv;
PFNGLUNIFORM3DPROC 					glUniform3d;
PFNGLUNIFORM3DVPROC					glUniform3dv;
PFNGLUNIFORM3FPROC					glUniform3f;
PFNGLUNIFORM3FVPROC					glUniform3fv;
PFNGLUNIFORM3IPROC					glUniform3i;
PFNGLUNIFORM3IVPROC					glUniform3iv;
PFNGLUNIFORM4DPROC					glUniform4d;
PFNGLUNIFORM4DVPROC					glUniform4dv;
PFNGLUNIFORM4FPROC					glUniform4f;
PFNGLUNIFORM4FVPROC					glUniform4fv;
PFNGLUNIFORM4IPROC					glUniform4i;
PFNGLUNIFORM4IVPROC					glUniform4iv;
PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv;
PFNGLGENERATEMIPMAPPROC				glGenerateMipmap;
PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation;
PFNGLVERTEXATTRIBDIVISORPROC		glVertexAttribDivisor;
PFNGLDRAWARRAYSINSTANCEDPROC		glDrawArraysInstanced;

GLenum CheckGLError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

void LoadGLProcs() {
    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(glXGetProcAddress((const GLubyte*)"glGenBuffers"));
	glDeleteBuffers = reinterpret_cast<PFNGLDELETEBUFFERSPROC>(glXGetProcAddress((const GLubyte*)"glDeleteBuffers"));
	glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(glXGetProcAddress((const GLubyte*)"glBindBuffer"));
	glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(glXGetProcAddress((const GLubyte*)"glBufferData"));
	glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(glXGetProcAddress((const GLubyte*)"glGenVertexArrays"));
	glDeleteVertexArrays = reinterpret_cast<PFNGLDELETEVERTEXARRAYSPROC>(glXGetProcAddress((const GLubyte*)"glDeleteVertexArrays"));
	glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(glXGetProcAddress((const GLubyte*)"glBindVertexArray"));
	glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(glXGetProcAddress((const GLubyte*)"glEnableVertexAttribArray"));
	glDisableVertexAttribArray = reinterpret_cast<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(glXGetProcAddress((const GLubyte*)"glDisableVertexAttribArray"));
	glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(glXGetProcAddress((const GLubyte*)"glVertexAttribPointer"));
	glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(glXGetProcAddress((const GLubyte*)"glCreateShader"));
	glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(glXGetProcAddress((const GLubyte*)"glShaderSource"));
	glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(glXGetProcAddress((const GLubyte*)"glCompileShader"));
	glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(glXGetProcAddress((const GLubyte*)"glGetShaderiv"));
	glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(glXGetProcAddress((const GLubyte*)"glGetShaderInfoLog"));
	glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>(glXGetProcAddress((const GLubyte*)"glDeleteShader"));
	glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(glXGetProcAddress((const GLubyte*)"glCreateProgram"));
	glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(glXGetProcAddress((const GLubyte*)"glAttachShader"));
	glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(glXGetProcAddress((const GLubyte*)"glLinkProgram"));
	glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(glXGetProcAddress((const GLubyte*)"glGetProgramiv"));
	glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(glXGetProcAddress((const GLubyte*)"glGetProgramInfoLog"));
	glDeleteProgram = reinterpret_cast<PFNGLDELETEPROGRAMPROC>(glXGetProcAddress((const GLubyte*)"glDeleteProgram"));
	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(glXGetProcAddress((const GLubyte*)"glUseProgram"));
	glUniform1d = reinterpret_cast<PFNGLUNIFORM1DPROC>(glXGetProcAddress((const GLubyte*)"glUniform1d"));
	glUniform1dv = reinterpret_cast<PFNGLUNIFORM1DVPROC>(glXGetProcAddress((const GLubyte*)"glUniform1dv"));
	glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>(glXGetProcAddress((const GLubyte*)"glUniform1f"));
	glUniform1fv = reinterpret_cast<PFNGLUNIFORM1FVPROC>(glXGetProcAddress((const GLubyte*)"glUniform1fv"));
	glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>(glXGetProcAddress((const GLubyte*)"glUniform1i"));
	glUniform1iv = reinterpret_cast<PFNGLUNIFORM1IVPROC>(glXGetProcAddress((const GLubyte*)"glUniform1iv"));
	glUniform2d = reinterpret_cast<PFNGLUNIFORM2DPROC>(glXGetProcAddress((const GLubyte*)"glUniform2d"));
	glUniform2dv = reinterpret_cast<PFNGLUNIFORM2DVPROC>(glXGetProcAddress((const GLubyte*)"glUniform2dv"));
	glUniform2f = reinterpret_cast<PFNGLUNIFORM2FPROC>(glXGetProcAddress((const GLubyte*)"glUniform2f"));
	glUniform2fv = reinterpret_cast<PFNGLUNIFORM2FVPROC>(glXGetProcAddress((const GLubyte*)"glUniform2fv"));
	glUniform2i = reinterpret_cast<PFNGLUNIFORM2IPROC>(glXGetProcAddress((const GLubyte*)"glUniform2i"));
	glUniform2iv = reinterpret_cast<PFNGLUNIFORM2IVPROC>(glXGetProcAddress((const GLubyte*)"glUniform2iv"));
	glUniform3d = reinterpret_cast<PFNGLUNIFORM3DPROC>(glXGetProcAddress((const GLubyte*)"glUniform3d"));
	glUniform3dv = reinterpret_cast<PFNGLUNIFORM3DVPROC>(glXGetProcAddress((const GLubyte*)"glUniform3dv"));
	glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>(glXGetProcAddress((const GLubyte*)"glUniform3f"));
	glUniform3fv = reinterpret_cast<PFNGLUNIFORM3FVPROC>(glXGetProcAddress((const GLubyte*)"glUniform3fv"));
	glUniform3i = reinterpret_cast<PFNGLUNIFORM3IPROC>(glXGetProcAddress((const GLubyte*)"glUniform3i"));
	glUniform3iv = reinterpret_cast<PFNGLUNIFORM3IVPROC>(glXGetProcAddress((const GLubyte*)"glUniform3iv"));
	glUniform4d = reinterpret_cast<PFNGLUNIFORM4DPROC>(glXGetProcAddress((const GLubyte*)"glUniform4d"));
	glUniform4dv = reinterpret_cast<PFNGLUNIFORM4DVPROC>(glXGetProcAddress((const GLubyte*)"glUniform4dv"));
	glUniform4f = reinterpret_cast<PFNGLUNIFORM4FPROC>(glXGetProcAddress((const GLubyte*)"glUniform4f"));
	glUniform4fv = reinterpret_cast<PFNGLUNIFORM4FVPROC>(glXGetProcAddress((const GLubyte*)"glUniform4fv"));
	glUniform4i = reinterpret_cast<PFNGLUNIFORM4IPROC>(glXGetProcAddress((const GLubyte*)"glUniform4i"));
	glUniform4iv = reinterpret_cast<PFNGLUNIFORM4IVPROC>(glXGetProcAddress((const GLubyte*)"glUniform4iv"));
	glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(glXGetProcAddress((const GLubyte*)"glUniformMatrix4fv"));
	glGenerateMipmap = reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(glXGetProcAddress((const GLubyte*)"glGenerateMipmap"));
	glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(glXGetProcAddress((const GLubyte*)"glGetUniformLocation"));
	glVertexAttribDivisor = reinterpret_cast<PFNGLVERTEXATTRIBDIVISORPROC>(glXGetProcAddress((const GLubyte*)"glVertexAttribDivisor"));
	glDrawArraysInstanced = reinterpret_cast<PFNGLDRAWARRAYSINSTANCEDPROC>(glXGetProcAddress((const GLubyte*)"glDrawArraysInstanced"));
}