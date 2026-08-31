/*
** ゲームグラフィックス特論用補助プログラム for GLFW
**

Copyright (c) 2011, 2012 Kohe Tokoi. All Rights Reserved.

Permission is hereby granted, free of charge,  to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction,  including without limitation the rights 
to use, copy,  modify, merge,  publish, distribute,  sublicense,  and/or sell 
copies or substantial portions of the Software.

The above  copyright notice  and this permission notice  shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR 
IMPLIED,  INCLUDING  BUT  NOT LIMITED  TO THE WARRANTIES  OF MERCHANTABILITY, 
FITNESS  FOR  A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN  NO EVENT  SHALL 
KOHE TOKOI  BE LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY,  WHETHER IN 
AN ACTION  OF CONTRACT,  TORT  OR  OTHERWISE,  ARISING  FROM,  OUT OF  OR  IN 
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**
*/

#ifndef __GG_H__
#define __GG_H__

#include <cstring>

#define GLFW_NO_GLU
#if defined(WIN32)
#  pragma warning(disable:4996)
#  include <GL/glfw.h>
#  include "glext.h"

extern PFNGLBLENDCOLORPROC glBlendColor;
extern PFNGLBLENDEQUATIONPROC glBlendEquation;
extern PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D;
extern PFNGLCOLORTABLEPROC glColorTable;
extern PFNGLCOLORTABLEPARAMETERFVPROC glColorTableParameterfv;
extern PFNGLCOLORTABLEPARAMETERIVPROC glColorTableParameteriv;
extern PFNGLCOPYCOLORTABLEPROC glCopyColorTable;
extern PFNGLGETCOLORTABLEPROC glGetColorTable;
extern PFNGLGETCOLORTABLEPARAMETERFVPROC glGetColorTableParameterfv;
extern PFNGLGETCOLORTABLEPARAMETERIVPROC glGetColorTableParameteriv;
extern PFNGLCOLORSUBTABLEPROC glColorSubTable;
extern PFNGLCOPYCOLORSUBTABLEPROC glCopyColorSubTable;
extern PFNGLCONVOLUTIONFILTER1DPROC glConvolutionFilter1D;
extern PFNGLCONVOLUTIONFILTER2DPROC glConvolutionFilter2D;
extern PFNGLCONVOLUTIONPARAMETERFPROC glConvolutionParameterf;
extern PFNGLCONVOLUTIONPARAMETERFVPROC glConvolutionParameterfv;
extern PFNGLCONVOLUTIONPARAMETERIPROC glConvolutionParameteri;
extern PFNGLCONVOLUTIONPARAMETERIVPROC glConvolutionParameteriv;
extern PFNGLCOPYCONVOLUTIONFILTER1DPROC glCopyConvolutionFilter1D;
extern PFNGLCOPYCONVOLUTIONFILTER2DPROC glCopyConvolutionFilter2D;
extern PFNGLGETCONVOLUTIONFILTERPROC glGetConvolutionFilter;
extern PFNGLGETCONVOLUTIONPARAMETERFVPROC glGetConvolutionParameterfv;
extern PFNGLGETCONVOLUTIONPARAMETERIVPROC glGetConvolutionParameteriv;
extern PFNGLGETSEPARABLEFILTERPROC glGetSeparableFilter;
extern PFNGLSEPARABLEFILTER2DPROC glSeparableFilter2D;
extern PFNGLGETHISTOGRAMPROC glGetHistogram;
extern PFNGLGETHISTOGRAMPARAMETERFVPROC glGetHistogramParameterfv;
extern PFNGLGETHISTOGRAMPARAMETERIVPROC glGetHistogramParameteriv;
extern PFNGLGETMINMAXPROC glGetMinmax;
extern PFNGLGETMINMAXPARAMETERFVPROC glGetMinmaxParameterfv;
extern PFNGLGETMINMAXPARAMETERIVPROC glGetMinmaxParameteriv;
extern PFNGLHISTOGRAMPROC glHistogram;
extern PFNGLMINMAXPROC glMinmax;
extern PFNGLRESETHISTOGRAMPROC glResetHistogram;
extern PFNGLRESETMINMAXPROC glResetMinmax;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
extern PFNGLSAMPLECOVERAGEPROC glSampleCoverage;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage;
extern PFNGLCLIENTACTIVETEXTUREPROC glClientActiveTexture;
extern PFNGLMULTITEXCOORD1DPROC glMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DVPROC glMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1FPROC glMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FVPROC glMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1IPROC glMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IVPROC glMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1SPROC glMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SVPROC glMultiTexCoord1sv;
extern PFNGLMULTITEXCOORD2DPROC glMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DVPROC glMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2FPROC glMultiTexCoord2f;
extern PFNGLMULTITEXCOORD2FVPROC glMultiTexCoord2fv;
extern PFNGLMULTITEXCOORD2IPROC glMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IVPROC glMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2SPROC glMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SVPROC glMultiTexCoord2sv;
extern PFNGLMULTITEXCOORD3DPROC glMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DVPROC glMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3FPROC glMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FVPROC glMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3IPROC glMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IVPROC glMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3SPROC glMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SVPROC glMultiTexCoord3sv;
extern PFNGLMULTITEXCOORD4DPROC glMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DVPROC glMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4FPROC glMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FVPROC glMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4IPROC glMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IVPROC glMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4SPROC glMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SVPROC glMultiTexCoord4sv;
extern PFNGLLOADTRANSPOSEMATRIXFPROC glLoadTransposeMatrixf;
extern PFNGLLOADTRANSPOSEMATRIXDPROC glLoadTransposeMatrixd;
extern PFNGLMULTTRANSPOSEMATRIXFPROC glMultTransposeMatrixf;
extern PFNGLMULTTRANSPOSEMATRIXDPROC glMultTransposeMatrixd;
extern PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
extern PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays;
extern PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements;
extern PFNGLPOINTPARAMETERFPROC glPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC glPointParameterfv;
extern PFNGLPOINTPARAMETERIPROC glPointParameteri;
extern PFNGLPOINTPARAMETERIVPROC glPointParameteriv;
extern PFNGLFOGCOORDFPROC glFogCoordf;
extern PFNGLFOGCOORDFVPROC glFogCoordfv;
extern PFNGLFOGCOORDDPROC glFogCoordd;
extern PFNGLFOGCOORDDVPROC glFogCoorddv;
extern PFNGLFOGCOORDPOINTERPROC glFogCoordPointer;
extern PFNGLSECONDARYCOLOR3BPROC glSecondaryColor3b;
extern PFNGLSECONDARYCOLOR3BVPROC glSecondaryColor3bv;
extern PFNGLSECONDARYCOLOR3DPROC glSecondaryColor3d;
extern PFNGLSECONDARYCOLOR3DVPROC glSecondaryColor3dv;
extern PFNGLSECONDARYCOLOR3FPROC glSecondaryColor3f;
extern PFNGLSECONDARYCOLOR3FVPROC glSecondaryColor3fv;
extern PFNGLSECONDARYCOLOR3IPROC glSecondaryColor3i;
extern PFNGLSECONDARYCOLOR3IVPROC glSecondaryColor3iv;
extern PFNGLSECONDARYCOLOR3SPROC glSecondaryColor3s;
extern PFNGLSECONDARYCOLOR3SVPROC glSecondaryColor3sv;
extern PFNGLSECONDARYCOLOR3UBPROC glSecondaryColor3ub;
extern PFNGLSECONDARYCOLOR3UBVPROC glSecondaryColor3ubv;
extern PFNGLSECONDARYCOLOR3UIPROC glSecondaryColor3ui;
extern PFNGLSECONDARYCOLOR3UIVPROC glSecondaryColor3uiv;
extern PFNGLSECONDARYCOLOR3USPROC glSecondaryColor3us;
extern PFNGLSECONDARYCOLOR3USVPROC glSecondaryColor3usv;
extern PFNGLSECONDARYCOLORPOINTERPROC glSecondaryColorPointer;
extern PFNGLWINDOWPOS2DPROC glWindowPos2d;
extern PFNGLWINDOWPOS2DVPROC glWindowPos2dv;
extern PFNGLWINDOWPOS2FPROC glWindowPos2f;
extern PFNGLWINDOWPOS2FVPROC glWindowPos2fv;
extern PFNGLWINDOWPOS2IPROC glWindowPos2i;
extern PFNGLWINDOWPOS2IVPROC glWindowPos2iv;
extern PFNGLWINDOWPOS2SPROC glWindowPos2s;
extern PFNGLWINDOWPOS2SVPROC glWindowPos2sv;
extern PFNGLWINDOWPOS3DPROC glWindowPos3d;
extern PFNGLWINDOWPOS3DVPROC glWindowPos3dv;
extern PFNGLWINDOWPOS3FPROC glWindowPos3f;
extern PFNGLWINDOWPOS3FVPROC glWindowPos3fv;
extern PFNGLWINDOWPOS3IPROC glWindowPos3i;
extern PFNGLWINDOWPOS3IVPROC glWindowPos3iv;
extern PFNGLWINDOWPOS3SPROC glWindowPos3s;
extern PFNGLWINDOWPOS3SVPROC glWindowPos3sv;
extern PFNGLGENQUERIESPROC glGenQueries;
extern PFNGLDELETEQUERIESPROC glDeleteQueries;
extern PFNGLISQUERYPROC glIsQuery;
extern PFNGLBEGINQUERYPROC glBeginQuery;
extern PFNGLENDQUERYPROC glEndQuery;
extern PFNGLGETQUERYIVPROC glGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLISBUFFERPROC glIsBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLBUFFERSUBDATAPROC glBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData;
extern PFNGLMAPBUFFERPROC glMapBuffer;
extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv;
extern PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
extern PFNGLDRAWBUFFERSPROC glDrawBuffers;
extern PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC glGetShaderSource;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC glGetUniformiv;
extern PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
extern PFNGLISPROGRAMPROC glIsProgram;
extern PFNGLISSHADERPROC glIsShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM2FPROC glUniform2f;
extern PFNGLUNIFORM3FPROC glUniform3f;
extern PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM2IPROC glUniform2i;
extern PFNGLUNIFORM3IPROC glUniform3i;
extern PFNGLUNIFORM4IPROC glUniform4i;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC glValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv;
extern PFNGLCOLORMASKIPROC glColorMaski;
extern PFNGLGETBOOLEANI_VPROC glGetBooleani_v;
extern PFNGLGETINTEGERI_VPROC glGetIntegeri_v;
extern PFNGLENABLEIPROC glEnablei;
extern PFNGLDISABLEIPROC glDisablei;
extern PFNGLISENABLEDIPROC glIsEnabledi;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC glBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying;
extern PFNGLCLAMPCOLORPROC glClampColor;
extern PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender;
extern PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender;
extern PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i;
extern PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i;
extern PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i;
extern PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv;
extern PFNGLGETUNIFORMUIVPROC glGetUniformuiv;
extern PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation;
extern PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC glUniform1ui;
extern PFNGLUNIFORM2UIPROC glUniform2ui;
extern PFNGLUNIFORM3UIPROC glUniform3ui;
extern PFNGLUNIFORM4UIPROC glUniform4ui;
extern PFNGLUNIFORM1UIVPROC glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC glUniform4uiv;
extern PFNGLTEXPARAMETERIIVPROC glTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv;
extern PFNGLCLEARBUFFERIVPROC glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC glClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC glClearBufferfi;
extern PFNGLGETSTRINGIPROC glGetStringi;
extern PFNGLDRAWARRAYSINSTANCEDPROC glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC glDrawElementsInstanced;
extern PFNGLTEXBUFFERPROC glTexBuffer;
extern PFNGLPRIMITIVERESTARTINDEXPROC glPrimitiveRestartIndex;
extern PFNGLGETINTEGER64I_VPROC glGetInteger64i_v;
extern PFNGLGETBUFFERPARAMETERI64VPROC glGetBufferParameteri64v;
extern PFNGLFRAMEBUFFERTEXTUREPROC glFramebufferTexture;
extern PFNGLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;
extern PFNGLMINSAMPLESHADINGPROC glMinSampleShading;
extern PFNGLBLENDEQUATIONIPROC glBlendEquationi;
extern PFNGLBLENDEQUATIONSEPARATEIPROC glBlendEquationSeparatei;
extern PFNGLBLENDFUNCIPROC glBlendFunci;
extern PFNGLBLENDFUNCSEPARATEIPROC glBlendFuncSeparatei;
extern PFNGLISRENDERBUFFERPROC glIsRenderbuffer;
extern PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
extern PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers;
extern PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv;
extern PFNGLISFRAMEBUFFERPROC glIsFramebuffer;
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv;
extern PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
extern PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer;
extern PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC glIsVertexArray;
extern PFNGLGETUNIFORMINDICESPROC glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC glGetActiveUniformsiv;
extern PFNGLGETACTIVEUNIFORMNAMEPROC glGetActiveUniformName;
extern PFNGLGETUNIFORMBLOCKINDEXPROC glGetUniformBlockIndex;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC glGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC glGetActiveUniformBlockName;
extern PFNGLUNIFORMBLOCKBINDINGPROC glUniformBlockBinding;
extern PFNGLCOPYBUFFERSUBDATAPROC glCopyBufferSubData;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC glDrawRangeElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC glDrawElementsInstancedBaseVertex;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC glMultiDrawElementsBaseVertex;
extern PFNGLPROVOKINGVERTEXPROC glProvokingVertex;
extern PFNGLFENCESYNCPROC glFenceSync;
extern PFNGLISSYNCPROC glIsSync;
extern PFNGLDELETESYNCPROC glDeleteSync;
extern PFNGLCLIENTWAITSYNCPROC glClientWaitSync;
extern PFNGLWAITSYNCPROC glWaitSync;
extern PFNGLGETINTEGER64VPROC glGetInteger64v;
extern PFNGLGETSYNCIVPROC glGetSynciv;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC glTexImage3DMultisample;
extern PFNGLGETMULTISAMPLEFVPROC glGetMultisamplefv;
extern PFNGLSAMPLEMASKIPROC glSampleMaski;
extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC glBindFragDataLocationIndexed;
extern PFNGLGETFRAGDATAINDEXPROC glGetFragDataIndex;
extern PFNGLGENSAMPLERSPROC glGenSamplers;
extern PFNGLDELETESAMPLERSPROC glDeleteSamplers;
extern PFNGLISSAMPLERPROC glIsSampler;
extern PFNGLBINDSAMPLERPROC glBindSampler;
extern PFNGLSAMPLERPARAMETERIPROC glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFPROC glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC glSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIIVPROC glSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC glSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERIVPROC glGetSamplerParameteriv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC glGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERFVPROC glGetSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC glGetSamplerParameterIuiv;
extern PFNGLQUERYCOUNTERPROC glQueryCounter;
extern PFNGLGETQUERYOBJECTI64VPROC glGetQueryObjecti64v;
extern PFNGLGETQUERYOBJECTUI64VPROC glGetQueryObjectui64v;
extern PFNGLVERTEXP2UIPROC glVertexP2ui;
extern PFNGLVERTEXP2UIVPROC glVertexP2uiv;
extern PFNGLVERTEXP3UIPROC glVertexP3ui;
extern PFNGLVERTEXP3UIVPROC glVertexP3uiv;
extern PFNGLVERTEXP4UIPROC glVertexP4ui;
extern PFNGLVERTEXP4UIVPROC glVertexP4uiv;
extern PFNGLTEXCOORDP1UIPROC glTexCoordP1ui;
extern PFNGLTEXCOORDP1UIVPROC glTexCoordP1uiv;
extern PFNGLTEXCOORDP2UIPROC glTexCoordP2ui;
extern PFNGLTEXCOORDP2UIVPROC glTexCoordP2uiv;
extern PFNGLTEXCOORDP3UIPROC glTexCoordP3ui;
extern PFNGLTEXCOORDP3UIVPROC glTexCoordP3uiv;
extern PFNGLTEXCOORDP4UIPROC glTexCoordP4ui;
extern PFNGLTEXCOORDP4UIVPROC glTexCoordP4uiv;
extern PFNGLMULTITEXCOORDP1UIPROC glMultiTexCoordP1ui;
extern PFNGLMULTITEXCOORDP1UIVPROC glMultiTexCoordP1uiv;
extern PFNGLMULTITEXCOORDP2UIPROC glMultiTexCoordP2ui;
extern PFNGLMULTITEXCOORDP2UIVPROC glMultiTexCoordP2uiv;
extern PFNGLMULTITEXCOORDP3UIPROC glMultiTexCoordP3ui;
extern PFNGLMULTITEXCOORDP3UIVPROC glMultiTexCoordP3uiv;
extern PFNGLMULTITEXCOORDP4UIPROC glMultiTexCoordP4ui;
extern PFNGLMULTITEXCOORDP4UIVPROC glMultiTexCoordP4uiv;
extern PFNGLNORMALP3UIPROC glNormalP3ui;
extern PFNGLNORMALP3UIVPROC glNormalP3uiv;
extern PFNGLCOLORP3UIPROC glColorP3ui;
extern PFNGLCOLORP3UIVPROC glColorP3uiv;
extern PFNGLCOLORP4UIPROC glColorP4ui;
extern PFNGLCOLORP4UIVPROC glColorP4uiv;
extern PFNGLSECONDARYCOLORP3UIPROC glSecondaryColorP3ui;
extern PFNGLSECONDARYCOLORP3UIVPROC glSecondaryColorP3uiv;
extern PFNGLVERTEXATTRIBP1UIPROC glVertexAttribP1ui;
extern PFNGLVERTEXATTRIBP1UIVPROC glVertexAttribP1uiv;
extern PFNGLVERTEXATTRIBP2UIPROC glVertexAttribP2ui;
extern PFNGLVERTEXATTRIBP2UIVPROC glVertexAttribP2uiv;
extern PFNGLVERTEXATTRIBP3UIPROC glVertexAttribP3ui;
extern PFNGLVERTEXATTRIBP3UIVPROC glVertexAttribP3uiv;
extern PFNGLVERTEXATTRIBP4UIPROC glVertexAttribP4ui;
extern PFNGLVERTEXATTRIBP4UIVPROC glVertexAttribP4uiv;
extern PFNGLDRAWARRAYSINDIRECTPROC glDrawArraysIndirect;
extern PFNGLDRAWELEMENTSINDIRECTPROC glDrawElementsIndirect;
extern PFNGLUNIFORM1DPROC glUniform1d;
extern PFNGLUNIFORM2DPROC glUniform2d;
extern PFNGLUNIFORM3DPROC glUniform3d;
extern PFNGLUNIFORM4DPROC glUniform4d;
extern PFNGLUNIFORM1DVPROC glUniform1dv;
extern PFNGLUNIFORM2DVPROC glUniform2dv;
extern PFNGLUNIFORM3DVPROC glUniform3dv;
extern PFNGLUNIFORM4DVPROC glUniform4dv;
extern PFNGLUNIFORMMATRIX2DVPROC glUniformMatrix2dv;
extern PFNGLUNIFORMMATRIX3DVPROC glUniformMatrix3dv;
extern PFNGLUNIFORMMATRIX4DVPROC glUniformMatrix4dv;
extern PFNGLUNIFORMMATRIX2X3DVPROC glUniformMatrix2x3dv;
extern PFNGLUNIFORMMATRIX2X4DVPROC glUniformMatrix2x4dv;
extern PFNGLUNIFORMMATRIX3X2DVPROC glUniformMatrix3x2dv;
extern PFNGLUNIFORMMATRIX3X4DVPROC glUniformMatrix3x4dv;
extern PFNGLUNIFORMMATRIX4X2DVPROC glUniformMatrix4x2dv;
extern PFNGLUNIFORMMATRIX4X3DVPROC glUniformMatrix4x3dv;
extern PFNGLGETUNIFORMDVPROC glGetUniformdv;
extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC glGetSubroutineUniformLocation;
extern PFNGLGETSUBROUTINEINDEXPROC glGetSubroutineIndex;
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC glGetActiveSubroutineUniformiv;
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC glGetActiveSubroutineUniformName;
extern PFNGLGETACTIVESUBROUTINENAMEPROC glGetActiveSubroutineName;
extern PFNGLUNIFORMSUBROUTINESUIVPROC glUniformSubroutinesuiv;
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC glGetUniformSubroutineuiv;
extern PFNGLGETPROGRAMSTAGEIVPROC glGetProgramStageiv;
extern PFNGLPATCHPARAMETERIPROC glPatchParameteri;
extern PFNGLPATCHPARAMETERFVPROC glPatchParameterfv;
extern PFNGLBINDTRANSFORMFEEDBACKPROC glBindTransformFeedback;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC glDeleteTransformFeedbacks;
extern PFNGLGENTRANSFORMFEEDBACKSPROC glGenTransformFeedbacks;
extern PFNGLISTRANSFORMFEEDBACKPROC glIsTransformFeedback;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC glPauseTransformFeedback;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC glResumeTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKPROC glDrawTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC glDrawTransformFeedbackStream;
extern PFNGLBEGINQUERYINDEXEDPROC glBeginQueryIndexed;
extern PFNGLENDQUERYINDEXEDPROC glEndQueryIndexed;
extern PFNGLGETQUERYINDEXEDIVPROC glGetQueryIndexediv;
extern PFNGLRELEASESHADERCOMPILERPROC glReleaseShaderCompiler;
extern PFNGLSHADERBINARYPROC glShaderBinary;
extern PFNGLGETSHADERPRECISIONFORMATPROC glGetShaderPrecisionFormat;
extern PFNGLDEPTHRANGEFPROC glDepthRangef;
extern PFNGLCLEARDEPTHFPROC glClearDepthf;
extern PFNGLGETPROGRAMBINARYPROC glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC glProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC glProgramParameteri;
extern PFNGLUSEPROGRAMSTAGESPROC glUseProgramStages;
extern PFNGLACTIVESHADERPROGRAMPROC glActiveShaderProgram;
extern PFNGLCREATESHADERPROGRAMVPROC glCreateShaderProgramv;
extern PFNGLBINDPROGRAMPIPELINEPROC glBindProgramPipeline;
extern PFNGLDELETEPROGRAMPIPELINESPROC glDeleteProgramPipelines;
extern PFNGLGENPROGRAMPIPELINESPROC glGenProgramPipelines;
extern PFNGLISPROGRAMPIPELINEPROC glIsProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEIVPROC glGetProgramPipelineiv;
extern PFNGLPROGRAMUNIFORM1IPROC glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1IVPROC glProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM1FPROC glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1FVPROC glProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM1DPROC glProgramUniform1d;
extern PFNGLPROGRAMUNIFORM1DVPROC glProgramUniform1dv;
extern PFNGLPROGRAMUNIFORM1UIPROC glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM1UIVPROC glProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2IPROC glProgramUniform2i;
extern PFNGLPROGRAMUNIFORM2IVPROC glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM2FPROC glProgramUniform2f;
extern PFNGLPROGRAMUNIFORM2FVPROC glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM2DPROC glProgramUniform2d;
extern PFNGLPROGRAMUNIFORM2DVPROC glProgramUniform2dv;
extern PFNGLPROGRAMUNIFORM2UIPROC glProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM2UIVPROC glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3IPROC glProgramUniform3i;
extern PFNGLPROGRAMUNIFORM3IVPROC glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM3FPROC glProgramUniform3f;
extern PFNGLPROGRAMUNIFORM3FVPROC glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM3DPROC glProgramUniform3d;
extern PFNGLPROGRAMUNIFORM3DVPROC glProgramUniform3dv;
extern PFNGLPROGRAMUNIFORM3UIPROC glProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM3UIVPROC glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4IPROC glProgramUniform4i;
extern PFNGLPROGRAMUNIFORM4IVPROC glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM4FPROC glProgramUniform4f;
extern PFNGLPROGRAMUNIFORM4FVPROC glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM4DPROC glProgramUniform4d;
extern PFNGLPROGRAMUNIFORM4DVPROC glProgramUniform4dv;
extern PFNGLPROGRAMUNIFORM4UIPROC glProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM4UIVPROC glProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC glProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC glProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC glProgramUniformMatrix2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC glProgramUniformMatrix3dv;
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC glProgramUniformMatrix4dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC glProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC glProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC glProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC glProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC glProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC glProgramUniformMatrix4x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC glProgramUniformMatrix2x3dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC glProgramUniformMatrix3x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC glProgramUniformMatrix2x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC glProgramUniformMatrix4x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC glProgramUniformMatrix3x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC glProgramUniformMatrix4x3dv;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC glValidateProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC glGetProgramPipelineInfoLog;
extern PFNGLVERTEXATTRIBL1DPROC glVertexAttribL1d;
extern PFNGLVERTEXATTRIBL2DPROC glVertexAttribL2d;
extern PFNGLVERTEXATTRIBL3DPROC glVertexAttribL3d;
extern PFNGLVERTEXATTRIBL4DPROC glVertexAttribL4d;
extern PFNGLVERTEXATTRIBL1DVPROC glVertexAttribL1dv;
extern PFNGLVERTEXATTRIBL2DVPROC glVertexAttribL2dv;
extern PFNGLVERTEXATTRIBL3DVPROC glVertexAttribL3dv;
extern PFNGLVERTEXATTRIBL4DVPROC glVertexAttribL4dv;
extern PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttribLPointer;
extern PFNGLGETVERTEXATTRIBLDVPROC glGetVertexAttribLdv;
extern PFNGLVIEWPORTARRAYVPROC glViewportArrayv;
extern PFNGLVIEWPORTINDEXEDFPROC glViewportIndexedf;
extern PFNGLVIEWPORTINDEXEDFVPROC glViewportIndexedfv;
extern PFNGLSCISSORARRAYVPROC glScissorArrayv;
extern PFNGLSCISSORINDEXEDPROC glScissorIndexed;
extern PFNGLSCISSORINDEXEDVPROC glScissorIndexedv;
extern PFNGLDEPTHRANGEARRAYVPROC glDepthRangeArrayv;
extern PFNGLDEPTHRANGEINDEXEDPROC glDepthRangeIndexed;
extern PFNGLGETFLOATI_VPROC glGetFloati_v;
extern PFNGLGETDOUBLEI_VPROC glGetDoublei_v;
extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC glDrawArraysInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC glDrawElementsInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC glDrawElementsInstancedBaseVertexBaseInstance;
extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC glDrawTransformFeedbackInstanced;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC glDrawTransformFeedbackStreamInstanced;
extern PFNGLGETINTERNALFORMATIVPROC glGetInternalformativ;
extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC glGetActiveAtomicCounterBufferiv;
extern PFNGLBINDIMAGETEXTUREPROC glBindImageTexture;
extern PFNGLMEMORYBARRIERPROC glMemoryBarrier;
extern PFNGLTEXSTORAGE1DPROC glTexStorage1D;
extern PFNGLTEXSTORAGE2DPROC glTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC glTexStorage3D;
extern PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC glGetDebugMessageLog;
extern PFNGLPUSHDEBUGGROUPPROC glPushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC glPopDebugGroup;
extern PFNGLOBJECTLABELPROC glObjectLabel;
extern PFNGLGETOBJECTLABELPROC glGetObjectLabel;
extern PFNGLOBJECTPTRLABELPROC glObjectPtrLabel;
extern PFNGLGETOBJECTPTRLABELPROC glGetObjectPtrLabel;
extern PFNGLCLEARBUFFERDATAPROC glClearBufferData;
extern PFNGLCLEARBUFFERSUBDATAPROC glClearBufferSubData;
extern PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC glDispatchComputeIndirect;
extern PFNGLCOPYIMAGESUBDATAPROC glCopyImageSubData;
extern PFNGLTEXTUREVIEWPROC glTextureView;
extern PFNGLBINDVERTEXBUFFERPROC glBindVertexBuffer;
extern PFNGLVERTEXATTRIBFORMATPROC glVertexAttribFormat;
extern PFNGLVERTEXATTRIBIFORMATPROC glVertexAttribIFormat;
extern PFNGLVERTEXATTRIBLFORMATPROC glVertexAttribLFormat;
extern PFNGLVERTEXATTRIBBINDINGPROC glVertexAttribBinding;
extern PFNGLVERTEXBINDINGDIVISORPROC glVertexBindingDivisor;
extern PFNGLFRAMEBUFFERPARAMETERIPROC glFramebufferParameteri;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC glGetFramebufferParameteriv;
extern PFNGLGETINTERNALFORMATI64VPROC glGetInternalformati64v;
extern PFNGLINVALIDATETEXSUBIMAGEPROC glInvalidateTexSubImage;
extern PFNGLINVALIDATETEXIMAGEPROC glInvalidateTexImage;
extern PFNGLINVALIDATEBUFFERSUBDATAPROC glInvalidateBufferSubData;
extern PFNGLINVALIDATEBUFFERDATAPROC glInvalidateBufferData;
extern PFNGLINVALIDATEFRAMEBUFFERPROC glInvalidateFramebuffer;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC glInvalidateSubFramebuffer;
extern PFNGLMULTIDRAWARRAYSINDIRECTPROC glMultiDrawArraysIndirect;
extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC glMultiDrawElementsIndirect;
extern PFNGLGETPROGRAMINTERFACEIVPROC glGetProgramInterfaceiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC glGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC glGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEIVPROC glGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC glGetProgramResourceLocation;
extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC glGetProgramResourceLocationIndex;
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC glShaderStorageBlockBinding;
extern PFNGLTEXBUFFERRANGEPROC glTexBufferRange;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC glTexStorage2DMultisample;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC glTexStorage3DMultisample;

#elif defined(__APPLE__)
#  define GLFW_INCLUDE_GL3
#  include <GL/glfw.h>
#  include <OpenGL/glext.h>
#  include <OpenGL/gl3ext.h>
#else
#  define GL_GLEXT_PROTOTYPES
#  include <GL/glfw.h>
#  include <GL/glext.h>
#endif

namespace gg
{
  /*
  ** ゲームグラフィックス特論の都合にもとづく初期化
  **
  **     OpenGL のレンダリングコンテキスト作成後に実行する
  */
  extern void ggInit(void);

  /*
  ** OpenGL のエラーチェック
  **
  **     OpenGL の API を呼び出し直後に実行すればエラーのあるときにメッセージを表示する
  **     msg はメッセージの頭に追加する文字列
  */
  extern void ggError(const char *msg = 0);

  /*
  ** FBO のエラーチェック
  **
  **     FBO の API を呼び出し直後に実行すればエラーのあるときにメッセージを表示する
  **     msg はメッセージに乗じる文字列
  */
  extern void ggFBOError(const char *msg = 0);

  /*
  ** シェーダーソースファイルの読み込み
  */
  extern GLuint loadShader(
    const char *vert,                   // バーテックスシェーダのソースファイル名
    const char *frag = 0,               // フラグメントシェーダのソースファイル名（0 なら不使用）
    const char *geom = 0,               // ジオメトリシェーダのソースファイル名（0 なら不使用）
    int nvarying = 0,                   // フィードバックする varying 変数の数（0 なら不使用）
    const char **varyings = 0           // フィードバックする varying 変数のリスト
    );

  /*
  ** テクスチャマッピング用の RAW 画像ファイルの読み込み
  */
  extern bool loadImage(const char *name, int width, int height, GLenum internal);

  /*
  ** 高さマップ用の RAW 画像ファイルの読み込んで法線マップを作成する
  */
  extern bool loadHeight(const char *name, int width, int height, float nz);

  /*
  ** 三角形分割された OBJ ファイルを読み込む
  */
  extern bool loadObj(const char *name, GLuint &nv, GLfloat (*&vert)[3], GLfloat (*&norm)[3], GLuint &nf, GLuint (*&face)[3], bool normalize);

  /*
  ** 基底クラス
  */
  class Gg
  {
  protected:

    // デストラクタ
    ~Gg(void) {}

  public:

    // コンストラクタ
    Gg(void) {}
  };

  /*
  ** 変換行列
  */
  class GgMatrix
    : public Gg
  {
    // 変換行列の要素
    GLfloat array[16];

    // 行列 a とベクトル b の積をベクトル c に代入する
    void projection(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

    // 行列 a と行列 b の積を行列 c に代入する
    void multiply(GLfloat *c, const GLfloat *a, const GLfloat *b) const;

  public:

    // デストラクタ
    virtual ~GgMatrix(void) {}

    // コンストラクタ
    GgMatrix(void) {}
    GgMatrix(const GLfloat *a)
    {
      load(a);
    }
    GgMatrix(const GgMatrix &m)
    {
      load(m);
    }

    // 演算子
    GgMatrix &multiply(const GgMatrix &m, const GgMatrix &n)
    {
      multiply(array, m.array, n.array);
      return *this;
    }
    GgMatrix &multiply(const GgMatrix &m, const GLfloat *a)
    {
      multiply(array, m.array, a);
      return *this;
    }
    GgMatrix &multiply(const GLfloat *a)
    {
      GLfloat t[16];
      multiply(t, array, a);
      memcpy(array, t, sizeof array);
      return *this;
    }
    GgMatrix &multiply(const GgMatrix &m)
    {
      return multiply(m.array);
    }
    GgMatrix &operator=(const GLfloat *a)
    {
      return load(a);
    }
    GgMatrix &operator=(const GgMatrix &m)
    {
      return load(m);
    }
    GgMatrix operator*(const GLfloat *a) const
    {
      GgMatrix t;
      t.multiply(t.array, this->array, a);
      return t;
    }
    GgMatrix operator*(const GgMatrix &m) const
    {
      GgMatrix t;
      t.multiply(t.array, this->array, m.array);
      return t;
    }
    GgMatrix &operator*=(const GLfloat *a)
    {
      return multiply(a);
    }
    GgMatrix &operator*=(const GgMatrix &m)
    {
      return multiply(m);
    }

    // 変換行列の読み込み
    GgMatrix &load(const GLfloat *a)
    {
      memcpy(array, a, sizeof array);
      return *this;
    }
    GgMatrix &load(const GgMatrix &m)
    {
      return load(m.array);
    }

    // 単位行列を設定する
    GgMatrix &loadIdentity(void);

    // 平行移動の変換行列を設定する
    GgMatrix &loadTranslate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadTranslate(const GLfloat *t)
    {
      return loadTranslate(t[0], t[1], t[2], t[3]);
    }

    // 拡大縮小の変換行列を設定する
    GgMatrix &loadScale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f);
    GgMatrix &loadScale(const GLfloat *s)
    {
      return loadScale(s[0], s[1], s[2], s[3]);
    }

    // 回転の変換行列を設定する
    GgMatrix &loadRotateX(GLfloat a);
    GgMatrix &loadRotateY(GLfloat a);
    GgMatrix &loadRotateZ(GLfloat a);
    GgMatrix &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgMatrix &loadRotate(const GLfloat *r)
    {
      return loadRotate(r[0], r[1], r[2], r[3]);
    }

    // 視野変換行列を設定する
    GgMatrix &loadLookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &loadLookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return loadLookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // 直交投影変換行列を設定する
    GgMatrix &loadOrthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 透視透視投影変換行列を設定する
    GgMatrix &loadFrustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 画角を指定して透視投影変換行列を設定する
    GgMatrix &loadPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // 転置行列を設定する
    GgMatrix &loadTranspose(const GgMatrix &m);

    // 逆行列を設定する
    GgMatrix &loadInvert(const GgMatrix &m);

    // 法線変換行列を設定する
    GgMatrix &loadNormal(const GgMatrix &m);

    // 平行移動変換を乗じる
    GgMatrix &translate(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      GgMatrix m;
      m.loadTranslate(x, y, z, w);
      multiply(m);
      return *this;
    }
    GgMatrix &translate(const GLfloat *t)
    {
      return translate(t[0], t[1], t[2], t[3]);
    }

    // 拡大縮小変換を乗じる
    GgMatrix &scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1.0f)
    {
      GgMatrix m;
      m.loadScale(x, y, z, w);
      multiply(m);
      return *this;
    }
    GgMatrix &scale(const GLfloat *s)
    {
      return scale(s[0], s[1], s[2], s[3]);
    }

    // 回転変換を乗じる
    GgMatrix &rotateX(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateX(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotateY(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateY(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotateZ(GLfloat a)
    {
      GgMatrix m;
      m.loadRotateZ(a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a)
    {
      GgMatrix m;
      m.loadRotate(x, y, z, a);
      multiply(m);
      return *this;
    }
    GgMatrix &rotate(const GLfloat *r)
    {
      return rotate(r[0], r[1], r[2], r[3]);
    }

    // 視野変換を乗じる
    GgMatrix &lookat(GLfloat ex, GLfloat ey, GLfloat ez, GLfloat tx, GLfloat ty, GLfloat tz, GLfloat ux, GLfloat uy, GLfloat uz);
    GgMatrix &lookat(const GLfloat *e, const GLfloat *t, const GLfloat *u)
    {
      return lookat(e[0], e[1], e[2], t[0], t[1], t[2], u[0], u[1], u[2]);
    }

    // 直交投影変換を乗じる
    GgMatrix &orthogonal(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 透視投影変換を乗じる
    GgMatrix &frustum(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);

    // 画角を指定して透視投影変換を乗じる
    GgMatrix &perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);

    // 転置行列を得る
    GgMatrix transpose(void) const
    {
      GgMatrix t;
      return t.loadTranspose(*this);
    }

    // 逆行列を得る
    GgMatrix invert(void) const
    {
      GgMatrix t;
      return t.loadInvert(*this);
    }

    // 法線変換行列を得る
    GgMatrix normal(void) const
    {
      GgMatrix t;
      return t.loadNormal(*this);
    }

    // ベクトルに対して投影変換を行う
    void projection(GLfloat *c, const GLfloat *v) const
    {
      projection(c, array, v);
    }

    // 変換行列を取り出す
    const GLfloat *get(void) const
    {
      return array;
    }
  };

  /*
  ** 四元数
  */
  class GgQuaternion
    : public Gg
  {
    // 四元数の要素
    GLfloat array[4];

    // 四元数 p と四元数 q の和を四元数 r に求める
    void add(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // 四元数 p と四元数 q の差を四元数 r に求める
    void subtract(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // 四元数 p と四元数 q の積を四元数 r に求める
    void multiply(GLfloat *r, const GLfloat *p, const GLfloat *q) const;

    // 四元数 q が表す回転の変換行列を m に求める
    void toMatrix(GLfloat *m, const GLfloat *q) const;

    // 回転の変換行列 m が表す四元数を q に求める
    void toQuaternion(GLfloat *q, const GLfloat *m) const;

    // 球面線形補間 q と r を t で補間した四元数を p に求める
    void slerp(GLfloat *p, const GLfloat *q, const GLfloat *r, GLfloat t) const;

  public:

    // デストラクタ
    virtual ~GgQuaternion(void) {}

    // コンストラクタ
    GgQuaternion(void) {}
    GgQuaternion(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
      load(x, y, z, w);
    }
    GgQuaternion(const GLfloat *a)
    {
      load(a);
    }
    GgQuaternion(const GgQuaternion &q)
    {
      load(q);
    }

    // 演算子
    GgQuaternion &operator=(const GLfloat *a)
    {
      return load(a);
    }
    GgQuaternion &operator=(const GgQuaternion &q)
    {
      return load(q);
    }
    GgQuaternion operator+(const GLfloat *a) const
    {
      GgQuaternion t;
      t.add(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator+(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.add(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator+=(const GLfloat *a)
    {
      return add(a);
    }
    GgQuaternion &operator+=(const GgQuaternion &q)
    {
      return add(q);
    }
    GgQuaternion operator-(const GLfloat *a) const
    {
      GgQuaternion t;
      t.subtract(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator-(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.subtract(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator-=(const GLfloat *a)
    {
      return subtract(a);
    }
    GgQuaternion &operator-=(const GgQuaternion &q)
    {
      return subtract(q);
    }
    GgQuaternion operator*(const GLfloat *a) const
    {
      GgQuaternion t;
      t.multiply(t.array, this->array, a);
      return t;
    }
    GgQuaternion operator*(const GgQuaternion &q) const
    {
      GgQuaternion t;
      t.multiply(t.array, this->array, q.array);
      return t;
    }
    GgQuaternion &operator*=(const GLfloat *a)
    {
      return multiply(a);
    }
    GgQuaternion &operator*=(const GgQuaternion &q)
    {
      return multiply(q);
    }

    // 四元数を設定する
    GgQuaternion &load(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
      array[0] = x;
      array[1] = y;
      array[2] = z;
      array[3] = w;
      return *this;
    }
    GgQuaternion &load(const GLfloat *a)
    {
      return load(a[0], a[1], a[2], a[3]);
    }
    GgQuaternion &load(const GgQuaternion &q)
    {
      return load(q.array);
    }

    // 回転の変換行列 m を表す四元数を設定する
    GgQuaternion &loadMatrix(const GLfloat *m)
    {
      toQuaternion(array, m);
      return *this;
    }

    // 単位元を設定する
    GgQuaternion &loadIdentity(void)
    {
      return load(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // (x, y, z) を軸として角度 a 回転する資源数を設定する
    GgQuaternion &loadRotate(GLfloat x, GLfloat y, GLfloat z, GLfloat a);
    GgQuaternion &loadRotate(const GLfloat *v, GLfloat a)
    {
      return loadRotate(v[0], v[1], v[2], a);
    }

    // オイラー角 (h, p, r) で与えられた回転を表す四元数を設定する
    GgQuaternion &loadEuler(GLfloat h, GLfloat p, GLfloat r);
    GgQuaternion &loadEuler(const GLfloat *e)
    {
      return loadEuler(e[0], e[1], e[2]);
    }

    // 四元数の和を求める
    GgQuaternion &add(const GgQuaternion &p, const GgQuaternion &q)
    {
      add(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &add(const GgQuaternion &q, const GLfloat *a)
    {
      add(array, q.array, a);
      return *this;
    }
    GgQuaternion &add(const GLfloat *a)
    {
      GLfloat t[4];
      add(t, array, a);
      return load(t);
    }
    GgQuaternion &add(const GgQuaternion &q)
    {
      return add(q.array);
    }

    // 四元数の差を求める
    GgQuaternion &subtract(const GgQuaternion &p, const GgQuaternion &q)
    {
      subtract(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &subtract(const GgQuaternion &q, const GLfloat *a)
    {
      subtract(array, q.array, a);
      return *this;
    }
    GgQuaternion &subtract(const GLfloat *a)
    {
      GLfloat t[4];
      subtract(t, array, a);
      return load(t);
    }
    GgQuaternion &subtract(const GgQuaternion &q)
    {
      return subtract(q.array);
    }

    // 四元数の積を求める
    GgQuaternion &multiply(const GgQuaternion &p, const GgQuaternion &q)
    {
      multiply(array, p.array, q.array);
      return *this;
    }
    GgQuaternion &multiply(const GgQuaternion &q, const GLfloat *a)
    {
      multiply(array, q.array, a);
      return *this;
    }
    GgQuaternion &multiply(const GLfloat *a)
    {
      GLfloat t[4];
      multiply(t, array, a);
      return load(t);
    }
    GgQuaternion &multiply(const GgQuaternion &q)
    {
      return multiply(q.array);
    }

    // 球面線形補間
    GgQuaternion &slerp(const GgQuaternion &q, const GgQuaternion &r, GLfloat t)
    {
      slerp(array, q.array, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(const GgQuaternion &q, const GLfloat *b, GLfloat t)
    {
      slerp(array, q.array, b, t);
      return *this;
    }
    GgQuaternion &slerp(const GLfloat *a, const GgQuaternion &r, GLfloat t)
    {
      slerp(array, a, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(const GLfloat *a, const GLfloat *b, GLfloat t)
    {
      slerp(array, a, b, t);
      return *this;
    }
    GgQuaternion &slerp(const GgQuaternion &r, GLfloat t)
    {
      slerp(array, array, r.array, t);
      return *this;
    }
    GgQuaternion &slerp(GLfloat *b, GLfloat t)
    {
      slerp(array, array, b, t);
      return *this;
    }

    // 四元数のノルムを求める
    GLfloat norm(void) const;

    // 共役四元数を求める
    GgQuaternion conjugate(void) const;

    // 四元数の逆を求める
    GgQuaternion invert(void) const;

    // 四元数を正規化する
    GgQuaternion normalize(void) const;

    // 四元数を取り出す
    const GLfloat *get(void) const
    {
      return array;
    }
    void get(GLfloat *a) const
    {
      a[0] = array[0];
      a[1] = array[1];
      a[2] = array[2];
      a[3] = array[3];
    }

    // 四元数が表す回転の行列を m に求める
    void getMatrix(GLfloat *m) const
    {
      toMatrix(m, array);
    }
  };

  /*
  ** 簡易トラックボール処理
  */
  class GgTrackball
    : public Gg
  {
    int cx, cy;       // ドラッグ開始位置
    bool drag;        // ドラッグ中か否か
    float sx, sy;     // マウスの絶対位置→ウィンドウ内での相対位置の換算係数
    GgQuaternion cq;  // 回転の初期値 (四元数)
    GgQuaternion tq;  // ドラッグ中の回転 (四元数)
    GLfloat rt[16];   // 回転の変換行列

  public:

    // デストラクタ
    virtual ~GgTrackball(void) {}

    // コンストラクタ
    GgTrackball(void);

    // トラックボール処理の範囲指定
    //    ウィンドウのリサイズ時に呼び出す
    void region(int w, int h);

    // トラックボール処理の開始
    //    マウスのドラッグ開始時（マウスボタンを押したとき）に呼び出す
    void start(int x, int y);

    // 回転の変換行列の計算
    //    マウスのドラッグ中に呼び出す
    void motion(int x, int y);

    // トラックボール処理の停止
    //    マウスのドラッグ終了時（マウスボタンを離したとき）に呼び出す
    void stop(int x, int y);

    // 現在の回転の変換行列を取り出す
    const GLfloat *get(void) const
    {
      return rt;
    }
  };

  /*
  ** 参照カウンタ
  **
  **     複数の属性データ間で共有されるリソースの確保と解放を管理する
  */
  class GgCounter
    : public Gg
  {
    friend class GgAttribute;
    
    // 参照カウント
    unsigned int count;

    // デストラクタ
    ~GgCounter(void) {}

    // コンストラクタ
    GgCounter(void)
      : count(0) {}
  };

  /*
  ** 属性データ
  **
  **     テクスチャとシェーダの基底クラス
  **     インスタンスは複数のオブジェクトから参照されることを想定する
  **     そのためこのクラスでは参照カウントを管理する
  */
  class GgAttribute
    : public Gg
  {
    // 参照カウンタ
    GgCounter *ref;

    // 参照カウントの増加
    void inc(void)
    {
      ++ref->count;
    }

  protected:

    // 参照カウントの減少
    unsigned int dec(void)
    {
      return --ref->count;
    }

  public:

    // デストラクタ
    virtual ~GgAttribute(void)
    {
      if (ref->count == 0) delete ref;
    }

    // コンストラクタ
    GgAttribute(void)
      : ref(new GgCounter)
    {
      inc();
    }
    GgAttribute(const GgAttribute &o)
      : ref(o.ref)
    {
      inc();
    }
    
    // 代入
    GgAttribute &operator=(const GgAttribute &o)
    {
      if (&o != this)
      {
        ref = o.ref;
        inc();
      }
      return *this;
    }
  };

  /*
  ** テクスチャ
  **
  **     カラー画像を読み込んでテクスチャマップを作成する
  */
  class GgTexture
    : public GgAttribute
  {
    // テクスチャ名
    GLuint texture;

  public:

    // デストラクタ
    virtual ~GgTexture(void)
    {
      if (dec() == 0) glDeleteTextures(1, &texture);
    }

    // コンストラクタ
    GgTexture(void)
    {
      glGenTextures(1, &texture);
    }
    GgTexture(const char *name, int width, int height, GLenum internal = GL_RGB)
    {
      glGenTextures(1, &texture);
      load(name, width, height, internal);
    }
    GgTexture(const GgTexture &o)
      : GgAttribute(o), texture(o.texture) {}

    // 代入
    GgTexture &operator=(const GgTexture &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        texture = o.texture;
      }
      return *this;
    }

    // 拡散反射色テクスチャを読み込む
    //     name: ファイル名, width, height: 幅と高さ (2^n), internal: GL_RGB か GL_RGBA
    void load(const char *name, int width, int height, GLenum internal = GL_RGB) const
    {
      glBindTexture(GL_TEXTURE_2D, texture);
      loadImage(name, width, height, internal);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    // テクスチャオブジェクトを結合する
    //     このテクスチャを使用する際に呼び出す
    //     unit: 使用するテクスチャユニット番号（0～）
    void use(GLuint unit = 0) const
    {
      glActiveTexture(GL_TEXTURE0 + unit);
      glBindTexture(GL_TEXTURE_2D, texture);
    }

    // テクスチャオブジェクトを解放する
    //    このテクスチャを使用しなくなったら呼び出す
    void unuse(void) const
    {
      glBindTexture(GL_TEXTURE_2D, 0);
      glActiveTexture(GL_TEXTURE0);
    }

    // テクスチャオブジェクトを取り出す
    GLuint get(void) const
    {
      return texture;
    }
  };
  
  /*
  ** 法線マップ
  **
  **     高さマップ（グレイスケール画像）を読み込んで法線マップを作成する
  */
  class GgNormalTexture
    : public GgTexture
  {
  public:

    // デストラクタ
    virtual ~GgNormalTexture(void) {}

    // コンストラクタ
    GgNormalTexture(void) {}
    GgNormalTexture(
      const char *name,                   // 画像ファイル名（1 チャネルの RAW 画像）
      int width, int height,              // 画像の幅と高さ（2^n 画素）
      float nz = 1.0f                     // 法線マップの z 成分の値
      )
      : GgTexture()
    {
      load(name, width, height, nz);
    }
    GgNormalTexture(const GgNormalTexture &o)
      : GgTexture(o) {}

    // 代入
    GgNormalTexture &operator=(const GgNormalTexture &o)
    {
      GgTexture::operator=(o);
      return *this;
    }

    // 高さマップを読み込んで法線マップを作成する
    //    name: ファイル名, width, height: 幅と高さ (2^n), nz: 法線マップの z 成分の値
    void load(const char *name, int width, int height, float nz = 1.0f) const
    {
      loadHeight(name, width, height, nz);
    }
  };

  /*
  ** シェーダ
  **
  **     シェーダの基底クラス
  */
  class GgShader
    : public GgAttribute
  {
    // プログラム名
    GLuint program;

  public:

    // デストラクタ
    virtual ~GgShader(void)
    {
      if (dec() == 0 && program != 0) glDeleteProgram(program);
    }

    // コンストラクタ
    GgShader(void)
      : program(0) {}
    GgShader(
      const char *vert,                   // バーテックスシェーダのソースファイル名
      const char *frag = 0,               // フラグメントシェーダのソースファイル名（0 なら不使用）
      const char *geom = 0,               // ジオメトリシェーダのソースファイル名（0 なら不使用）
      int nvarying = 0,                   // フィードバックする varying 変数の数（0 なら不使用）
      const char **varyings = 0           // フィードバックする varying 変数のリスト
      )
      : program(loadShader(vert, frag, geom, nvarying, varyings)) {}
    GgShader(const GgShader &o)
      : GgAttribute(o), program(o.program) {}
    
    // 代入
    GgShader &operator=(const GgShader &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        program = o.program;
      }
      return *this;
    }

    // シェーダのソースプログラムの読み込みとコンパイル・リンク
    void load(
      const char *vert,                   // バーテックスシェーダのソースファイル名
      const char *frag = 0,               // フラグメントシェーダのソースファイル名（0 なら不使用）
      const char *geom = 0,               // ジオメトリシェーダのソースファイル名（0 なら不使用）
      GLint nvarying = 0,                 // フィードバックする varying 変数の数（0 なら不使用）
      const char **varyings = 0           // フィードバックする varying 変数のリスト
      )
    {
      if (program != 0) glDeleteProgram(program);
      program = loadShader(vert, frag, geom, nvarying, varyings);
    }

    // シェーダプログラムの使用を開始する
    virtual void use(GLuint vert, ...) const
    {
      glUseProgram(program);
    }

    // シェーダプログラムの使用を終了する
    virtual void unuse(void) const
    {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glUseProgram(0);
    }

    // 変換行列を設定する
    virtual void loadMatrix(const GgMatrix &mp, const GgMatrix &mw) = 0;
    virtual void loadMatrix(const GLfloat *mp, const GLfloat *mw) = 0;

    // シェーダプログラム名を取り出す
    GLuint get(void) const
    {
      return program;
    }
  };

  /*
  ** バッファオブジェクト
  **
  **    頂点／インデックスバッファオブジェクトの基底クラス
  */
  template <typename T>
  class GgBuffer
    : public GgAttribute
  {
    // バッファオブジェクト
    GLuint buffer;

    // データ数
    GLuint number;

  public:

    // デストラクタ
    virtual ~GgBuffer<T>(void)
    {
      if (dec() == 0) glDeleteBuffers(1, &buffer);
    }

    // コンストラクタ
    GgBuffer<T>(void)
      : number(0)
    {
      glGenBuffers(1, &buffer);
    }
    GgBuffer<T>(GLenum target, GLuint n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      glGenBuffers(1, &buffer);
      load(target, n, data, usage);
    }
    GgBuffer<T>(const GgBuffer<T> &o)
      : GgAttribute(o), buffer(o.buffer), number(o.number) {}

    // 代入
    GgBuffer<T> &operator=(const GgBuffer<T> &o)
    {
      if (&o != this)
      {
        GgAttribute::operator=(o);
        buffer = o.buffer;
        number = o.number;
      }
      return *this;
    }

    // バッファオブジェクトにデータを格納する
    void load(GLenum target, GLuint n, const T *data, GLenum usage = GL_STATIC_DRAW)
    {
      number = n;
      glBindBuffer(target, buffer);
      glBufferData(target, sizeof (T) * n, data, usage);
    }

    // バッファオブジェクトのデータを複写する
    void copy(GLuint buf)
    {
      const size_t size = sizeof (T) * number;
#ifdef __APPLE__
      T *temp = new T[number];
      glBindBuffer(GL_ARRAY_BUFFER, buf);
      glGetBufferSubData(GL_ARRAY_BUFFER, 0, size, temp);
      glBindBuffer(GL_ARRAY_BUFFER, buffer);
      glBufferSubData(GL_ARRAY_BUFFER, 0, size, temp);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      delete[] temp;
#else
      glBindBuffer(GL_COPY_READ_BUFFER, buf);
      glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
      glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size);
      glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
      glBindBuffer(GL_COPY_READ_BUFFER, 0);
#endif
    }
    
    // バッファオブジェクト名を取り出す
    GLuint buf(void) const
    {
      return buffer;
    }

    // データの数を取り出す
    GLuint num(void) const
    {
      return number;
    }
  };

  /*
  ** 形状データ
  **
  **    形状データの基底クラス
  **    このクラスから使用するシェーダを参照する
  **    シェーダのインスタンスを結合したら参照カウントをインクリメントする
  **    シェーダのインスタンスの結合を解除したら参照カウントをデクリメントし，0 になったらシェーダを削除する
  */
  class GgShape
    : public Gg
  {
    // シェーダー
    GgShader *shader;

  protected:

    // 描画図形
    GLenum mode;

  public:

    // デストラクタ
    virtual ~GgShape(void) {}

    // コンストラクタ
    GgShape(void)
      : shader(0), mode(GL_POINTS) {}
    GgShape(const GgShape &o)
      : shader(o.shader), mode(o.mode) {}

    // 代入演算子
    GgShape &operator=(const GgShape &o)
    {
      if (this != &o)
      {
        attachShader(o.shader);
        mode = o.mode;
      }
      return *this;
    }

    // 形状データにシェーダのインスタンス s を結合する
    //    それまで結合されていたシェーダの参照カウントをデクリメントして 0 になったらそのシェーダを破棄する
    //    新しいシェーダ s を結合して s の参照カウントをインクリメントする
    void attachShader(GgShader *s)
    {
      shader = s;
    }
    void attachShader(GgShader &s)
    {
      shader = &s;
    }

    // この形状データで使用しているシェーダを取り出す
    GgShader *getShader(void) const
    {
      return shader;
    }

    // 描画に使う基本図形を設定する
    void setMode(GLenum m)
    {
      mode = m;
    }

    // この形状を描画する手続きをオーバーライドする
    virtual void draw(void) const = 0;
  };

  /*
  ** ポイント
  */
  class GgPoints
    : public GgShape
  {
    // 頂点バッファオブジェクト
    GgBuffer<GLfloat[3]> position;

  public:

    // デストラクタ
    virtual ~GgPoints(void) {}

    // コンストラクタ
    GgPoints(void) {}
    GgPoints(GLuint n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      load(n, pos, usage);
      mode = GL_POINTS;
    }
    GgPoints(const GgPoints &o)
      : GgShape(o), position(o.position) {}

    // 代入
    GgPoints &operator=(const GgPoints &o)
    {
      if (&o != this)
      {
        GgShape::operator=(o);
        position = o.position;
      }
      return *this;
    }

    // バッファオブジェクトを確保して頂点を格納する
    //    n: 頂点数, pos: 頂点の位置
    void load(GLuint n, const GLfloat (*pos)[3], GLenum usage = GL_STATIC_DRAW)
    {
      position.load(GL_ARRAY_BUFFER, n, pos, usage);
    }

    // バッファオブジェクト名を取り出す
    GLuint pbuf(void) const
    {
      return position.buf();
    }
    
    // データの数を取り出す
    GLuint pnum(void) const
    {
      return position.num();
    }
    
    // ポイントの描画
    virtual void draw(void) const;
  };

  /*
  ** ポリゴン
  */
  class GgTriangles
    : public GgPoints
  {
    // 頂点の法線ベクトル
    GgBuffer<GLfloat[3]> normal;

  public:

    // デストラクタ
    virtual ~GgTriangles(void) {}

    // コンストラクタ
    GgTriangles(void) {}
    GgTriangles(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
      : GgPoints(n, pos, usage)
    {
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
      mode = GL_TRIANGLES;
    }
    GgTriangles(const GgTriangles &o)
      : GgPoints(o), normal(o.normal) {}

    // 代入
    GgTriangles &operator=(const GgTriangles &o)
    {
      if (&o != this)
      {
        GgPoints::operator=(o);
        normal = o.normal;
      }
      return *this;
    }

    // バッファオブジェクトを確保して位置と法線を格納する
    //    n: 頂点数, pos: 頂点の位置, norm: 頂点の法線
    void load(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgPoints::load(n, pos, usage);
      normal.load(GL_ARRAY_BUFFER, n, norm, usage);
    }

    // バッファオブジェクト名を取り出す
    GLuint nbuf(void) const
    {
      return normal.buf();
    }
    
    // データの数を取り出す
    GLuint nnum(void) const
    {
      return normal.num();
    }
    
    // 三角形群を描画する手続き
    virtual void draw(void) const;
  };

  /*
  ** 三角形の形状データ
  */
  class GgObject
    : public GgTriangles
  {
    // インデックスバッファオブジェクト
    GgBuffer<GLuint[3]> index;

  public:

    // デストラクタ
    virtual ~GgObject(void) {}

    // コンストラクタ
    GgObject(void) {}
    GgObject(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      GLuint f, const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
      : GgTriangles(n, pos, norm, usage)
    {
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }
    GgObject(const GgObject &o)
      : GgTriangles(o), index(o.index) {}
    
    // 代入
    GgObject &operator=(const GgObject &o)
    {
      if (&o != this)
      {
        GgTriangles::operator=(o);
        index = o.index;
      }
      return *this;
    }

    // バッファオブジェクトを確保して位置と法線とインデックスを格納する
    //    n: 頂点数, pos: 頂点の位置, norm:頂点の法線
    //    f: 面数, face: 頂点のインデックスデータ
    void load(GLuint n, const GLfloat (*pos)[3], const GLfloat (*norm)[3],
      GLuint f, const GLuint (*face)[3], GLenum usage = GL_STATIC_DRAW)
    {
      GgTriangles::load(n, pos, norm, usage);
      index.load(GL_ELEMENT_ARRAY_BUFFER, f, face);
    }

    // バッファオブジェクト名を取り出す
    GLuint fbuf(void) const
    {
      return index.buf();
    }
    
    // データの数を取り出す
    GLuint fnum(void) const
    {
      return index.num();
    }
    
    // 三角形ポリゴンを描画する手続き
    virtual void draw(void) const;
  };

  /*
  ** 球状のポイント
  */
  extern GgPoints *ggPointSphere(GLuint nv, GLfloat cx = 0.0f, GLfloat cy = 0.0f, GLfloat cz = 0.0f, GLfloat radius = 0.5f);

  /*
  ** 矩形
  */
  extern GgTriangles *ggRectangle(GLfloat width = 1.0f, GLfloat height = 1.0f);

  /*
  ** 楕円
  */
  extern GgTriangles *ggEllipse(GLfloat width = 1.0f, GLfloat height = 1.0f, GLuint slices = 16);

  /*
  ** 三角形分割された Alias OBJ ファイル (Arrays 形式)
  */
  extern GgTriangles *ggObjArray(const char *name, bool normalize = false);

  /*
  ** 三角形分割された Alias OBJ ファイル (Elements 形式)
  */
  extern GgObject *ggObj(const char *name, bool normalize = false);
}

#endif
