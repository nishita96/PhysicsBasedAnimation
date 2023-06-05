////
////  proj6.cpp
////  ProjectICG
////
////  Created by Nishita Kharche on 3/1/22.
////
//
//
//#define GL_SILENCE_DEPRECATION
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <GLUT/glut.h>
//#include "cyTriMesh.h"
//#include "cyCore.h"
//#include "cyVector.h"
//#include "cyGL.h"
//#include "cyMatrix.h"
//#include "lodepng.h"
//#include <cstring>
//using namespace std;
//using namespace cy;
//
//GLuint vao;
//GLuint vbo0;
//GLuint vbo1;
//GLuint ebuffer;
//GLuint texID0;
//GLuint texID1;
//GLuint txc;
//
//double rotObjX = 0.0f;
//double rotObjY = 0.0f;
//double newRotObjX = 0.0f;
//double newRotObjY = 0.0f;
//double prevRotObjX = 0.0f;
//double prevRotObjY = 0.0f;
//
//double rotLightX = 0.0f;
//double rotLightY = 0.0f;
//double newRotLightX = 0.0f;
//double newRotLightY = 0.0f;
//double prevRotLightX = 0.0f;
//double prevRotLightY = 0.0f;
//
//double prevZoomXObj = 0.0f;
//double prevZoomYObj = 0.0f;
//double newZoomXObj = 0.0f;
//double newZoomYObj = 0.0f;
//
//Vec3f camera(0.0,0.0,-20.0); //-20 showed the plane reflections
//Vec3f cameraPlane(0.0,0.0,-15.0);
//Vec3f trans(0.0,0.0,0.0);
//Vec3f up(0.0,1.0,0.0);
//
//Vec3f boundMin(0.0,0.0,0.0);
//Vec3f boundMax(1.0,1.0,1.0);
//Vec3f centre(0.0,0.0,0.0);
//
//Vec4f lightDirection(2.0, 2.0, 2.0, 0.0);
//
//bool ctrlPressed = false;
//bool altPressed = false;
//
//unsigned int widthImg = 1920;
//unsigned int heightImg = 1020;
//
//string path = "";
//
//GLuint frameBuffer = 0;
//GLuint renderedTexture;
//GLuint depthBuffer;
//unsigned int textureWidth = 640;
//unsigned int textureHeight = 480;
//
//GLuint quad_vertexbuffer;
//GLuint quad_VertexArrayID;
//GLuint quad_vertexnormalbuffer;
//
//GLuint planetxc;
//GLuint txc_t;
//int width = 1280; //window size
//int height = 1020;
//
//double rotPlaneX = 0.0f;
//double rotPlaneY = 0.0f;
//double prevRotPlaneX = 0.0f;
//double prevRotPlaneY = 0.0f;
//double newRotPlaneX = 0.0f;
//double newRotPlaneY = 0.0f;
//
//double prevZoomXPlane = 0.0f;
//double prevZoomYPlane = 0.0f;
//double newZoomXPlane = 0.0f;
//double newZoomYPlane = 0.0f;
//
//GLuint triangle_envbuffer; //
//GLuint texId; //change
//GLuint texID;
//
//Vec4f cameraRot(0.0, 0.0, 0.0, 0.0);
//
//
//static void createVertexArray(){
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//}
//
//static void createVertexBuffer(TriMesh *mesh){
//
//    glGenBuffers(1, &vbo0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NV(), &mesh->V(0), GL_STATIC_DRAW);
//
//    glGenBuffers(1, &vbo1);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NVN(), &mesh->VN(0), GL_STATIC_DRAW);
//
//    glGenBuffers(1, &ebuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NF(), &mesh->F(0), GL_STATIC_DRAW);
//}
//
//
//static void createVertexBufferPlane(){
//
//    float sizePlane = 20.0f ;
//    static const GLfloat quad_vertex_buffer[] = {
//        -sizePlane, 0.0f, -sizePlane,
//        sizePlane, 0.0f, -sizePlane,
//        -sizePlane,  0.0f, sizePlane,
//        -sizePlane,  0.0f, sizePlane,
//        sizePlane, 0.0f, -sizePlane,
//        sizePlane,  0.0f, sizePlane
//    };
//
//    static const GLfloat plane_vertex_normal[] = { //y up
//        0.0f, 1.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        0.0f, 1.0f,0.0f
//
//    };
//
//    glGenBuffers(1, &quad_vertexbuffer); //vbo0
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_buffer), quad_vertex_buffer, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &quad_vertexnormalbuffer); //vbo1
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexnormalbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_normal), plane_vertex_normal, GL_STATIC_DRAW);
//}
//
//static void createVertexBufferEnvTriangle(){
//
//    static const GLfloat traingle_env_vertex[] = {
//        -1.0f, -1.0f, 0.99999f,
//        3.0f, -1.0f, 0.99999f,
//        -1.0f,  3.0f, 0.99999f
//    };
//
//    glGenBuffers(1, &triangle_envbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, triangle_envbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(traingle_env_vertex), traingle_env_vertex, GL_STATIC_DRAW);
//}
//
//static void buildProgram( cy::GLSLProgram prog){
//    prog.BuildFiles("shader.vert", "shader.frag"); //1
//    prog.Bind();
//}
//
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) //close window
//        glfwSetWindowShouldClose(window, GLFW_TRUE);
//
//    if (key == GLFW_KEY_F6 && action == GLFW_PRESS){ //redo shaders
//        GLSLProgram prog;
//        prog.CreateProgram();
//        if(prog.IsNull()){
//            cout << "Error creating shader program. \n";
//        }
//        buildProgram(prog);
//    }
//    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS){ //cant keep code here coz only called when key change detected, wont refresh all the time
//        ctrlPressed = true;
//    }
//    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE){
//        ctrlPressed = false;
//    }
//    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS){
//        altPressed = true;
//    }
//    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE){
//        altPressed = false;
//    }
//
//}
//
//static void getMouseCoordinates(GLFWwindow* window){
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        if (ctrlPressed){
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            rotLightX = rotLightX + newRotLightX - prevRotPlaneX;
//            rotLightY = rotLightY + newRotLightY - prevRotPlaneY;
//            prevRotPlaneX = newRotLightX;
//            prevRotPlaneY = newRotLightY;
//        }
//        else{
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            rotObjX = rotObjX + newRotObjX - prevRotObjX;
//            rotObjY = rotObjY + newRotObjY - prevRotObjY;
//            prevRotObjX = newRotObjX;
//            prevRotObjY = newRotObjY;
//        }
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
//
//        glfwGetCursorPos(window, &newRotPlaneX, &newRotPlaneY);
//        prevRotPlaneX = newRotPlaneX;
//        prevRotPlaneY = newRotPlaneY;
//        prevRotObjX = newRotPlaneX;
//        prevRotObjY = newRotPlaneY;
//
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
//        if (altPressed){
//            glfwGetCursorPos(window, &newZoomXPlane, &newZoomYPlane);
//            cameraPlane.z += 0.02 * (prevZoomXPlane - newZoomXPlane);
//            prevZoomXPlane = newZoomXPlane;
//        }
//        else{
//            glfwGetCursorPos(window, &newZoomXObj, &newZoomYObj);
//            camera.z += 0.02 * (prevZoomXObj - newZoomXObj);
//            prevZoomXObj = newZoomXObj;
//        }
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
//        glfwGetCursorPos(window, &newZoomXPlane, &newZoomYPlane);
//        prevZoomXPlane = newZoomXPlane;
//        glfwGetCursorPos(window, &newZoomXObj, &newZoomYObj);
//        prevZoomXObj = newZoomXObj;
//    }
//}
//
//static void  createEnvTextureCube(){
//    unsigned int imgWidth, imgHeight;
//
//    string file1 = "";
//    vector<unsigned char> png1;
//    vector<unsigned char> texImage1;
//    vector<unsigned char> texImage2;
//    vector<unsigned char> texImage3;
//    vector<unsigned char> texImage4;
//    vector<unsigned char> texImage5;
//    vector<unsigned char> texImage6;
//
//    file1 = path + "cubemap_posx.png";
//    unsigned error = lodepng::load_file(png1, file1.c_str()); //load the image file with given filename
//    if(!error) error = lodepng::decode(texImage1, imgWidth, imgHeight, png1);
//    //if there's an error, display it
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
//    file1 = path + "cubemap_posy.png";
//    error = lodepng::load_file(png1, file1.c_str());
//    if(!error) error = lodepng::decode(texImage2, imgWidth, imgHeight, png1);
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
//    file1 = path + "cubemap_posz.png";
//    error = lodepng::load_file(png1, file1.c_str());
//    if(!error) error = lodepng::decode(texImage3, imgWidth, imgHeight, png1);
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
//    file1 = path + "cubemap_negx.png";
//    error = lodepng::load_file(png1, file1.c_str());
//    if(!error) error = lodepng::decode(texImage4, imgWidth, imgHeight, png1);
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
//    file1 = path + "cubemap_negy.png";
//    error = lodepng::load_file(png1, file1.c_str());
//    if(!error) error = lodepng::decode(texImage5, imgWidth, imgHeight, png1);
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
//    file1 = path + "cubemap_negz.png";
//    error = lodepng::load_file(png1, file1.c_str());
//    if(!error) error = lodepng::decode(texImage6, imgWidth, imgHeight, png1);
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
//    glGenTextures( 1, &texID );
//    glBindTexture( GL_TEXTURE_CUBE_MAP, texID );
//    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X,
//                 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//                 texImage1.data());
//    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
//                 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//                 texImage2.data());
//    glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
//                 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//                 texImage3.data());
//    glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
//                 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//                 texImage4.data());
//    glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
//                 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//                 texImage5.data());
//    glTexImage2D( GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
//                 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
//                 texImage6.data());
//    glGenerateMipmap( GL_TEXTURE_CUBE_MAP );
//    glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );
//    glTexParameteri(
//        GL_TEXTURE_CUBE_MAP,
//        GL_TEXTURE_MIN_FILTER,
//        GL_LINEAR_MIPMAP_LINEAR
//        );
//    glTexParameteri(
//        GL_TEXTURE_CUBE_MAP,
//        GL_TEXTURE_MAG_FILTER,
//        GL_LINEAR
//    );
//
//}
//
////static void createTextureUnit(TriMesh *mesh){
//////    unsigned int imgWidth, imgHeight;
//////
//////    file0 = path + string(mesh->M(0).map_Kd);
//////    unsigned error = lodepng::load_file(png0, file0.c_str()); //load the image file with given filename
//////    if(!error) error = lodepng::decode(texImage, imgWidth, imgHeight, png0);
//////    //if there's an error, display it
//////    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//////
//////    glGenTextures(1, &texID0);
//////    glBindTexture(GL_TEXTURE_2D, texID0);
//////    glTexImage2D(GL_TEXTURE_2D,
//////                 0,
//////                 GL_RGBA,
//////                 imgWidth,
//////                 imgHeight,
//////                 0,
//////                 GL_RGBA,
//////                 GL_UNSIGNED_BYTE,
//////                 texImage.data()); //pixel data, texImage1
//////    glGenerateMipmap(GL_TEXTURE_2D);
//////    glTexParameteri(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_MIN_FILTER,
//////                    GL_LINEAR_MIPMAP_LINEAR
//////        );
//////    glTexParameteri(
//////                   GL_TEXTURE_2D,
//////                   GL_TEXTURE_MAG_FILTER,
//////                   GL_LINEAR
//////       );
//////    glTexParameterf(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_MAX_ANISOTROPY_EXT,
//////                    GL_MAX_TEXTURE_MAX_ANISOTROPY );
//////    glTexParameteri(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_WRAP_S,
//////                    GL_REPEAT
//////        );
//////    glTexParameteri(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_WRAP_T,
//////                    GL_REPEAT //changed here, wrap doesnt work right
//////        );
//////
//////    file1 = path + string(mesh->M(0).map_Ks);
//////    unsigned error1 = lodepng::load_file(png1, file1.c_str()); //load the image file with given filename
//////    if(!error1) error1 = lodepng::decode(texImage1, imgWidth, imgHeight, png0);
//////    //if there's an error, display it
//////    if(error1) std::cout << "decoder error " << error1 << ": " << lodepng_error_text(error1) << std::endl;
//////
//////    glGenTextures(1, &texID1);
//////    glBindTexture(GL_TEXTURE_2D, texID1);
//////    glTexImage2D(GL_TEXTURE_2D,
//////                 0,
//////                 GL_RGBA,
//////                 imgWidth,
//////                 imgHeight,
//////                 0,
//////                 GL_RGBA,
//////                 GL_UNSIGNED_BYTE,
//////                 texImage1.data()); //pixel data, texImage1
//////    glGenerateMipmap(GL_TEXTURE_2D);
//////    glTexParameteri(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_MIN_FILTER,
//////                    GL_LINEAR_MIPMAP_LINEAR
//////        );
//////    glTexParameteri(
//////                   GL_TEXTURE_2D,
//////                   GL_TEXTURE_MAG_FILTER,
//////                   GL_LINEAR
//////       );
//////    glTexParameterf(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_MAX_ANISOTROPY_EXT,
//////                    GL_MAX_TEXTURE_MAX_ANISOTROPY );
//////    glTexParameteri(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_WRAP_S,
//////                    GL_REPEAT
//////        );
//////    glTexParameteri(
//////                    GL_TEXTURE_2D,
//////                    GL_TEXTURE_WRAP_T,
//////                    GL_REPEAT //changed here, wrap doesnt work right
//////        );
//////
////}
////
////static bool createFrameBuffer(){
////
////    glGenFramebuffers( 1, &frameBuffer );
////
////    glGenTextures( 1, &renderedTexture );
////    glBindTexture( GL_TEXTURE_2D, renderedTexture );
////    glTexImage2D( GL_TEXTURE_2D,
////                 0, GL_RGB, textureWidth, textureHeight, 0,
////                 GL_RGB, GL_UNSIGNED_BYTE, 0 );//the plane texture size (ratio of obj to plane changes)
////
////    glTexParameteri( GL_TEXTURE_2D,
////                    GL_TEXTURE_MAG_FILTER, GL_LINEAR );
////    glTexParameteri( GL_TEXTURE_2D,
////                    GL_TEXTURE_MIN_FILTER, GL_LINEAR );
////    glGenerateMipmap( renderedTexture );
////
////    glGenRenderbuffers( 1, &depthBuffer );
////    glBindRenderbuffer( GL_RENDERBUFFER, depthBuffer );
////    glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT, textureWidth, textureHeight );
////
////    glBindFramebuffer( GL_FRAMEBUFFER, frameBuffer );
////    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer );
////    glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0 );
////
////    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
////    glDrawBuffers( 1, drawBuffers );
////    if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE ) return false;
////    return true;
////}
//
//int main( int argc, char* args[] )
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        exit(EXIT_FAILURE);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(width, height, "ICG Projects", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//
//    //create mesh
//    TriMesh mesh;
//    mesh.LoadFromFileObj(args[1]); //loading teapot
//    mesh.ComputeBoundingBox();
//    mesh.ComputeNormals();
//
//    if(argc > 1){
//        std::string arg1(args[1]);
//        fprintf(stdout, "argument: %s\n", arg1.c_str());
//        std::string arg2(args[2]);
//        fprintf(stdout, "argument 2: %s\n", arg2.c_str());
//        path = arg2;
//    }
//
//    glfwSetKeyCallback(window, key_callback);
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    //adding glew
//    glewExperimental = GL_TRUE;
//    GLenum err = glewInit();
//    if (GLEW_OK != err)
//    {
//      /* Problem: glewInit failed, something is seriously wrong. */
//      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//
//    createVertexArray();
//    createVertexBuffer(&mesh);
//    createEnvTextureCube();
//    createVertexBufferEnvTriangle();
//    createVertexBufferPlane();
//    
//    GLSLProgram progTeapot;
//    progTeapot.CreateProgram();
//    if(progTeapot.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    progTeapot.BuildFiles("shader.vert", "shader.frag");
//    
//    GLSLProgram progEnv;
//    progEnv.CreateProgram();
//    if(progEnv.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    progEnv.BuildFiles("shader1.vert", "shader1.frag"); //CHANGE THIS
//
//    GLSLProgram progPlane;
//    progPlane.CreateProgram();
//    if(progPlane.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    progPlane.BuildFiles("shader2.vert", "shader2.frag");
//
//
//    //calculate bounding box and centre obj, this works irrespective of the object size changes
//    boundMin = mesh.GetBoundMin();
//    boundMax = mesh.GetBoundMax();
//    centre.x =  (boundMin.x + boundMax.x) / 2.0;
//    centre.y =  (boundMin.y + boundMax.y) / 2.0;
//    centre.z =  (boundMin.z + boundMax.z) / 2.0;
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        glClearColor(0, 0, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//
//        getMouseCoordinates(window);
//
//        //rotate object
//        Matrix4f rotMatrix;
//        Matrix4f rotMatX;
//        Matrix4f rotMatY;
//        rotMatX = Matrix4f::RotationX(-rotObjY * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
//        rotMatY = Matrix4f::RotationY(-rotObjX * (M_PI/180.0));
//        rotMatrix = rotMatX * rotMatY;
//
//        //shifting based on bounding box
//        Matrix4f translationMatrix = Matrix4f::Translation(-centre.XYZ());
//
//        Matrix4f scaleMatrix = Matrix4f::Scale(0.08);
//        Matrix4f modelMatrix = scaleMatrix * translationMatrix;
//
//        cameraRot = rotMatrix * Vec4f(camera,1);//rotating the camera
//        //for env
//        Matrix4f viewMatrix = Matrix4f::View(cameraRot.XYZ(), trans.XYZ(), up.XYZ());//camera, movees the angle with the obj also
//        Matrix4f projMatrix = Matrix4f::Perspective(10.0 * (M_PI/180.0), 1020.0/680.0, 0.1f, 1000.0f);
//        Matrix4f transMatrix = projMatrix * viewMatrix * modelMatrix;
//
//        //for lighting take from view only
//        Matrix4f mvMatrix = viewMatrix * modelMatrix;
//        Matrix3f normalMatrix = mvMatrix.GetSubMatrix3().GetInverse().GetTranspose();
//
//        //for env
//        Matrix4f viewMatrixInv = Matrix4f::View(cameraRot.XYZ(), trans.XYZ(), up.XYZ());
//        Matrix4f invMatrix = projMatrix * viewMatrixInv;
//        invMatrix = invMatrix.GetInverse();
//
//        Matrix3f cameraNormalMatrix =  modelMatrix.GetSubMatrix3().GetInverse().GetTranspose();//changed
//
//        //ENVIRONMENT everything
//        float matrixInv[16];
//        invMatrix.Get(matrixInv);
//
//        GLint inverse_pos = glGetUniformLocation(progEnv.GetID(), "inverse");
//        glUseProgram(progEnv.GetID());
//        glUniformMatrix4fv(inverse_pos, 1, GL_FALSE, matrixInv);
//
//        GLint center = glGetUniformLocation(progEnv.GetID(), "center");
//        glUseProgram(progEnv.GetID());
//        glUniform3f(center, camera.x,camera.y,camera.z);
//
////        glEnable( GL_TEXTURE_CUBE_MAP_SEAMLESS );
//        glActiveTexture( GL_TEXTURE0 );
//        glBindTexture( GL_TEXTURE_CUBE_MAP, texID);
//        GLint samplerEnv = glGetUniformLocation(progEnv.GetID(), "env"); //in frag
//        glUseProgram(progEnv.GetID());
//        glUniform1i(samplerEnv, 0);
//
//        //location = 0
//        GLuint pos_location = glGetAttribLocation(progEnv.GetID(), "pos"); //in view space , canonical
//        glUseProgram(progEnv.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, triangle_envbuffer);
//        glEnableVertexAttribArray(pos_location);
//        glVertexAttribPointer(pos_location, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        glClearColor(0,0,0,1);//(1,1,1,1)
//        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//
//        glUseProgram(progEnv.GetID());
//
//        glDepthMask( GL_FALSE );//
//        glDrawArrays(GL_TRIANGLES, 0, 3); //draw env
//        glDepthMask( GL_TRUE );//
//
//
//        //TEAPOT rendering everything
//        float matrixMvp[16];
//        float matrixMv[16];
//        float matrixNorm[9];
//        float cameraNormMatrix[9];
//        float matrixMod[9];
//        transMatrix.Get(matrixMvp); //gives single colour shading
//        mvMatrix.Get(matrixMv);
//        normalMatrix.Get(matrixNorm);
//        glUseProgram(progTeapot.GetID());
//
////        transMatrix.Get(matrixMvp);
//        GLint mvp_pos = glGetUniformLocation(progTeapot.GetID(), "mvp");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
//
////        mvMatrix.Get(matrixMv);
//        GLint mv_pos = glGetUniformLocation(progTeapot.GetID(), "mv");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mv_pos, 1, GL_FALSE, matrixMv);
//
////        normalMatrix.Get(matrixNorm);
//        GLint normal_pos = glGetUniformLocation(progTeapot.GetID(), "normalMatrix");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix3fv(normal_pos, 1, GL_FALSE, matrixNorm);
//
//        GLint lightDirection = glGetUniformLocation(progTeapot.GetID(), "lightDirection");
//        glUseProgram(progTeapot.GetID());
//        glUniform3f(lightDirection, 5.0,5.0,5.0);
//
//        GLint shine = glGetUniformLocation(progTeapot.GetID(), "shine");
//        glUseProgram(progTeapot.GetID());
//        glUniform1f(shine, 80.0);
//
//        GLint camera = glGetUniformLocation(progTeapot.GetID(), "camera");
//        glUseProgram(progTeapot.GetID());
//        glUniform3f(camera, cameraRot.x,cameraRot.y,cameraRot.z);
//
//        modelMatrix.Get(matrixMod);
//        GLint model_pos = glGetUniformLocation(progTeapot.GetID(), "modelPosition");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix3fv(model_pos, 1, GL_FALSE, matrixMod);
//
//        cameraNormalMatrix.Get(cameraNormMatrix);
//        GLint cameranormal_pos = glGetUniformLocation(progTeapot.GetID(), "cameraNormalMatrix");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix3fv(cameranormal_pos, 1, GL_FALSE, cameraNormMatrix);
//
//        //location = 0
//        GLuint pos_loc = glGetAttribLocation(progTeapot.GetID(), "pos");
//        glUseProgram(progTeapot.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//        glEnableVertexAttribArray(pos_loc);
//        glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE,
//                              0, (void*) 0);
//
//        //location = 1
//        GLuint normal_loc = glGetAttribLocation(progTeapot.GetID(), "normal");
//        glUseProgram(progTeapot.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//        glEnableVertexAttribArray(normal_loc);
//        glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//
//        glActiveTexture( GL_TEXTURE0 );
//        glBindTexture( GL_TEXTURE_CUBE_MAP, texID );
//        GLint samplerT = glGetUniformLocation(progTeapot.GetID(), "env");
//        glUseProgram(progTeapot.GetID());
//        glUniform1i(samplerT, 0);
//
//        glEnable(GL_DEPTH_TEST);
//        glUseProgram(progTeapot.GetID());
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//        glDrawElements(GL_TRIANGLES, sizeof(cy::Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0);
//        
//        
//        //------------------------
//        //making texture for the reflection of teapot on the plane
//        //rotate
//        //take texture here
//        
//        
//        //PLANE everything
//        glUseProgram(progPlane.GetID());
//        
//        transMatrix.Get(matrixMvp);
//        GLint mvp_pos_plane = glGetUniformLocation(progPlane.GetID(), "mvp");
//        glUseProgram(progPlane.GetID());
//        glUniformMatrix4fv(mvp_pos_plane, 1, GL_FALSE, matrixMvp);
//
//        mvMatrix.Get(matrixMv);
//        GLint mv_pos_plane = glGetUniformLocation(progPlane.GetID(), "mv");
//        glUseProgram(progPlane.GetID());
//        glUniformMatrix4fv(mv_pos_plane, 1, GL_FALSE, matrixMv);
//
//        normalMatrix.Get(matrixNorm);
//        GLint normal_pos_plane = glGetUniformLocation(progPlane.GetID(), "normalMatrix");
//        glUseProgram(progPlane.GetID());
//        glUniformMatrix3fv(normal_pos_plane, 1, GL_FALSE, matrixNorm);
//
//        GLint lightDirectionPlane = glGetUniformLocation(progPlane.GetID(), "lightDirection");
//        glUseProgram(progPlane.GetID());
//        glUniform3f(lightDirectionPlane, 5.0,5.0,5.0);
//        
//        GLint shinePlane = glGetUniformLocation(progPlane.GetID(), "shine");
//        glUseProgram(progPlane.GetID());
//        glUniform1f(shinePlane, 80.0);
//        
//        GLint cameraPos1 = glGetUniformLocation(progPlane.GetID(), "camera");
//        glUseProgram(progPlane.GetID());
//        glUniform3f(cameraPos1, cameraRot.x,cameraRot.y,cameraRot.z);
//
//        modelMatrix.Get(matrixMod);
//        GLint model_pos_plane = glGetUniformLocation(progPlane.GetID(), "modelPosition");
//        glUseProgram(progPlane.GetID());
//        glUniformMatrix3fv(model_pos_plane, 1, GL_FALSE, matrixMod);
//
//        cameraNormalMatrix.Get(cameraNormMatrix);
//        GLint normalMatrix1_pos1 = glGetUniformLocation(progPlane.GetID(), "cameraNormalMatrix");
//        glUseProgram(progPlane.GetID());
//        glUniformMatrix3fv(normalMatrix1_pos1, 1, GL_FALSE, cameraNormMatrix);
//
//        glActiveTexture( GL_TEXTURE0 );
//        glBindTexture( GL_TEXTURE_CUBE_MAP, texID);
//        GLint samplerPlane = glGetUniformLocation(progPlane.GetID(), "env");
//        glUseProgram(progPlane.GetID());
//        glUniform1i(samplerPlane, 0);
//
//        GLuint pos_loc_plane = glGetAttribLocation(progPlane.GetID(), "pos");
//        glUseProgram(progPlane.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//        glEnableVertexAttribArray(pos_loc_plane);
//        glVertexAttribPointer(pos_loc_plane, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        GLuint normal_loc_plane = glGetAttribLocation(progPlane.GetID(), "normal");
//        glUseProgram(progPlane.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexnormalbuffer);
//        glEnableVertexAttribArray(normal_loc_plane);
//        glVertexAttribPointer(normal_loc_plane, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//        
//        //use the texture here
//
//        glUseProgram(progPlane.GetID());
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    glfwTerminate();
//    return 0;
//}
//
//
////------------------------------------------------------------------------------------------------------------
//
//
//
//
//
