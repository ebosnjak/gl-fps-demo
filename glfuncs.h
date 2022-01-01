#ifndef GLFUNCS_H
#define GLFUNCS_H

#define CheckGLError() CheckGLError_(__FILE__, __LINE__);

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>

#include <iostream>

extern PFNGLGENBUFFERSPROC					glGenBuffers;
extern PFNGLDELETEBUFFERSPROC				glDeleteBuffers;
extern PFNGLBINDBUFFERPROC					glBindBuffer;
extern PFNGLBUFFERDATAPROC					glBufferData;
extern PFNGLGENVERTEXARRAYSPROC				glGenVertexArrays;
extern PFNGLDELETEVERTEXARRAYSPROC			glDeleteVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC				glBindVertexArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC		glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC	glDisableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC			glVertexAttribPointer;
extern PFNGLCREATESHADERPROC				glCreateShader;
extern PFNGLSHADERSOURCEPROC				glShaderSource;
extern PFNGLCOMPILESHADERPROC				glCompileShader;
extern PFNGLGETSHADERIVPROC					glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC				glDeleteShader;
extern PFNGLCREATEPROGRAMPROC				glCreateProgram;
extern PFNGLATTACHSHADERPROC				glAttachShader;
extern PFNGLLINKPROGRAMPROC					glLinkProgram;
extern PFNGLGETPROGRAMIVPROC				glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
extern PFNGLDELETEPROGRAMPROC				glDeleteProgram;
extern PFNGLUSEPROGRAMPROC					glUseProgram;
extern PFNGLUNIFORM1DPROC					glUniform1d;
extern PFNGLUNIFORM1DVPROC					glUniform1dv;
extern PFNGLUNIFORM1FPROC					glUniform1f;
extern PFNGLUNIFORM1FVPROC					glUniform1fv;
extern PFNGLUNIFORM1IPROC					glUniform1i;
extern PFNGLUNIFORM1IVPROC					glUniform1iv;
extern PFNGLUNIFORM2DPROC					glUniform2d;
extern PFNGLUNIFORM2DVPROC					glUniform2dv;
extern PFNGLUNIFORM2FPROC					glUniform2f;
extern PFNGLUNIFORM2FVPROC					glUniform2fv;
extern PFNGLUNIFORM2IPROC					glUniform2i;
extern PFNGLUNIFORM2IVPROC					glUniform2iv;
extern PFNGLUNIFORM3DPROC 					glUniform3d;
extern PFNGLUNIFORM3DVPROC					glUniform3dv;
extern PFNGLUNIFORM3FPROC					glUniform3f;
extern PFNGLUNIFORM3FVPROC					glUniform3fv;
extern PFNGLUNIFORM3IPROC					glUniform3i;
extern PFNGLUNIFORM3IVPROC					glUniform3iv;
extern PFNGLUNIFORM4DPROC					glUniform4d;
extern PFNGLUNIFORM4DVPROC					glUniform4dv;
extern PFNGLUNIFORM4FPROC					glUniform4f;
extern PFNGLUNIFORM4FVPROC					glUniform4fv;
extern PFNGLUNIFORM4IPROC					glUniform4i;
extern PFNGLUNIFORM4IVPROC					glUniform4iv;
extern PFNGLUNIFORMMATRIX4FVPROC			glUniformMatrix4fv;
extern PFNGLGENERATEMIPMAPPROC				glGenerateMipmap;
extern PFNGLGETUNIFORMLOCATIONPROC			glGetUniformLocation;
extern PFNGLVERTEXATTRIBDIVISORPROC			glVertexAttribDivisor;
extern PFNGLDRAWARRAYSINSTANCEDPROC			glDrawArraysInstanced;

void LoadGLProcs();
GLenum CheckGLError_(const char* file, int line);

#endif