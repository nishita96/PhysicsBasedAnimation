////
////  proj8.cpp
////  ProjectICG
////
////  Created by Nishita Kharche on 3/15/22.
////
////
////
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
//Vec3f camera(0.0,0.0,-12.0);
//Vec3f trans(0.0,0.0,0.0);
//Vec3f up(0.0,1.0,0.0);
//
//Vec3f boundMin(0.0,0.0,0.0);
//Vec3f boundMax(1.0,1.0,1.0);
//Vec3f centre(0.0,0.0,0.0);
//
//Vec4f lightDirection(10.0, 50.0, -20.0, 0.0); //CHECK IF NO VALUE COMES
//
//bool ctrlPressed = false;
//bool altPressed = false;
//bool spacePressed = false;
//
//string path = "";
//
//GLuint frameBuffer = 0;
//GLuint renderedTexture;
//GLuint depthBuffer;
//
//GLuint planevertexbuffer;
//GLuint planevertexnormalbuffer;
//
//GLuint planetxc;
//GLuint txc_t;
//
//int width = 1280;
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
//
//Vec4f cameraRot(0.0, 0.0, 0.0, 0.0);
//
//string argsNorm, argsDisp;
//
//unsigned int widthImg;
//unsigned int heightImg;
//
//vector<unsigned char> png;
//vector<unsigned char> texImage;
//
//
////proj7
//GLuint depthMap;
//double shadWidth = 5000;
//double shadHeight = 4000;
//
//Vec3f transBias(0.5,0.5,0.5 - 0.0000066);
//
////proj8
//int tesLevel = 1;
//
//bool noTes = false;
//
//static void createVertexArray(){
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//}
//
//
//static void createVertexBufferPlane(){
//
//    //didnt work with 6
//    float sizePlane = 30.0f ;
//    static const GLfloat vertex_buffer[] = {
//        -sizePlane, sizePlane, 0.0f,
//        sizePlane, sizePlane, 0.0f,
//        sizePlane, -sizePlane, 0.0f,
//        -sizePlane, -sizePlane, 0.0f,
//    };
//
//    static const GLfloat plane_normal[] = { //x up
//        0.0f, 0.0f, 1.0f,
//        0.0f, 0.0f, 1.0f,
//        0.0f, 0.0f, 1.0f,
//        0.0f, 0.0f, 1.0f,
//
//    };
//    static const GLfloat txc_vertex_buffer[] = {
//        0.0f, 0.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        1.0f, 1.0f,0.0f,
//        1.0f, 0.0f,0.0f,
//    };
//
//    glGenBuffers(1, &planevertexbuffer); //vbo0,
//    glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &planevertexnormalbuffer); //vbo1
//    glBindBuffer(GL_ARRAY_BUFFER, planevertexnormalbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_normal), plane_normal, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &txc);
//    glBindBuffer(GL_ARRAY_BUFFER, txc);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(txc_vertex_buffer), txc_vertex_buffer, GL_STATIC_DRAW);
//}
//
//static void buildProgram( GLSLProgram prog){
//    prog.BuildFiles("shader.vert", "shader.frag"); //
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
//    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
//        spacePressed = true;
//    }
//    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE){
//        spacePressed = false;
//    }
//    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS && !noTes){
//        if(tesLevel > 0)
//        tesLevel--;
//    }
//    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS && !noTes){
//        tesLevel++;
//    }
//}
//
//static void createNormTextureUnit(){
//
//    string pathNorm = argsNorm;//args[1];
//    //the raw pixels in texImage
//
//    unsigned error = lodepng::load_file(png, pathNorm.c_str()); //load the image file with given filename
//    if(!error) error = lodepng::decode(texImage, widthImg, heightImg, png);
//    //if there's an error, display it
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
////    glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
//    glGenBuffers(1, &texID0);
//    glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
//    glBindTexture(GL_TEXTURE_2D, texID0);
//    glTexImage2D(GL_TEXTURE_2D,
//                 0,
//                 GL_RGBA,
//                 widthImg,
//                 heightImg,
//                 0,
//                 GL_RGBA,
//                 GL_UNSIGNED_BYTE,
//                 texImage.data()); //pixel data
//    glGenerateMipmap(GL_TEXTURE_2D);
//    glTexParameteri(
//                    GL_TEXTURE_2D,
//                    GL_TEXTURE_MIN_FILTER,
//                    GL_LINEAR_MIPMAP_LINEAR
//        );
//    glTexParameteri(
//                   GL_TEXTURE_2D,
//                   GL_TEXTURE_MAG_FILTER,
//                   GL_LINEAR
//       );
//    glTexParameteri(
//                    GL_TEXTURE_2D,
//                    GL_TEXTURE_WRAP_S,
//                    GL_REPEAT
//        );
//
//    glTexParameteri(
//                    GL_TEXTURE_2D,
//                    GL_TEXTURE_WRAP_T,
//                    GL_REPEAT //changed here, wrap doesnt work right
//        );
//}
//
//static void createDispTextureUnit(){
//
//    string pathDisp = argsDisp;//args[2];
//    vector<unsigned char> png;
//    vector<unsigned char> texImage; //the raw pixels
//
//    unsigned error = lodepng::load_file(png, pathDisp.c_str()); //load the image file with given filename
//    if(!error) error = lodepng::decode(texImage, widthImg, heightImg, png);
//    //if there's an error, display it
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
////    glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
//    glGenBuffers(1, &texID1);
//    glActiveTexture(GL_TEXTURE1); //specifying texture unit number, here is the default
//    glBindTexture(GL_TEXTURE_2D, texID1);
//    glTexImage2D(GL_TEXTURE_2D,
//                 0,
//                 GL_RGBA,
//                 widthImg,
//                 heightImg,
//                 0,
//                 GL_RGBA,
//                 GL_UNSIGNED_BYTE,
//                 texImage.data()); //pixel data
//    glGenerateMipmap(GL_TEXTURE_2D);
//    glTexParameteri(
//                    GL_TEXTURE_2D,
//                    GL_TEXTURE_MIN_FILTER,
//                    GL_LINEAR_MIPMAP_LINEAR
//        );
//    glTexParameteri(
//                   GL_TEXTURE_2D,
//                   GL_TEXTURE_MAG_FILTER,
//                   GL_LINEAR
//       );
//    glTexParameteri(
//                    GL_TEXTURE_2D,
//                    GL_TEXTURE_WRAP_S,
//                    GL_REPEAT
//        );
//
//    glTexParameteri(
//                    GL_TEXTURE_2D,
//                    GL_TEXTURE_WRAP_T,
//                    GL_REPEAT //changed here, wrap doesnt work right
//        );
//}
//
//static void getMouseCoordinates(GLFWwindow* window){
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        if (ctrlPressed){
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            rotLightX = rotLightX + newRotLightX - prevRotPlaneX;
//            prevRotPlaneX = newRotLightX;
//            rotLightY = rotLightY + newRotLightY - prevRotPlaneY;
//            prevRotPlaneY = newRotLightY;
//        }
//        else{
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            rotObjX = rotObjX + newRotObjX - prevRotObjX;
//            prevRotObjX = newRotObjX;
//            rotObjY = rotObjY + newRotObjY - prevRotObjY;
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
//            glfwGetCursorPos(window, &newZoomXObj, &newZoomYObj);
//            camera.z += 0.02 * (prevZoomXObj - newZoomXObj);
//            prevZoomXObj = newZoomXObj;
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
//        glfwGetCursorPos(window, &newZoomXPlane, &newZoomYPlane);
//        prevZoomXPlane = newZoomXPlane;
//        glfwGetCursorPos(window, &newZoomXObj, &newZoomYObj);
//        prevZoomXObj = newZoomXObj;
//    }
//}
//
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
//
//    argsNorm = args[1];
//    fprintf(stdout, "\n argument 1: %s\n", argsNorm.c_str());
//    if(argc > 1){
////    Put a check for this second file
//        argsDisp = args[2];
//        fprintf(stdout, "argument 2: %s\n", argsDisp.c_str());
//    }else{
//        noTes = true;
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
//    
//    GLSLProgram prog; //use for plane
//    prog.CreateProgram();
//    if(prog.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    prog.BuildFiles("shader.vert", "shader.frag", NULL, "tcsShader.gs", "tesShader.gs");
//    
//     GLSLProgram progLines; //
//    progLines.CreateProgram();
//     if(progLines.IsNull()){
//         fprintf(stderr, "Error creating shader program. \n");
//         return 1;
//     }
//    progLines.BuildFiles("shader1.vert", "shader1.frag", "shader.gs", "tcsShader1.gs", "tesShader1.gs");
//    
//    GLSLProgram shadowProgram;
//        shadowProgram.CreateProgram();
//        shadowProgram.BuildFiles("shaderShadow.vert", "shaderShadow.frag", NULL, "tcsShader1.gs", "tesShader1.gs"); //shader1
//        if(shadowProgram.IsNull()){
//            fprintf(stderr, "Error creating shader program. \n");
//            return 1;
//        }
//
//    createVertexArray();
////    createVertexBuffer(&mesh);//teapot
//    createVertexBufferPlane();
//    createNormTextureUnit();
//    createDispTextureUnit();
//
//
//    //calculate bounding box and centre obj, this works irrespective of the object size changes
////    boundMin = mesh.GetBoundMin();
////    boundMax = mesh.GetBoundMax();
////    centre.x =  (boundMin.x + boundMax.x) / 2.0;
////    centre.y =  (boundMin.y + boundMax.y) / 2.0;
////    centre.z =  (boundMin.z + boundMax.z) / 2.0;
//
////    CHECK IF WORKS HERE
//    GLRenderDepth2D shadowMap;
//    shadowMap.Initialize(
//           true,   // depth comparison texture
//           shadWidth,  // width
//           shadHeight  // height
//           );
//    shadowMap.SetTextureFilteringMode( GL_LINEAR, GL_LINEAR );
//    shadowMap.SetTextureWrappingMode( GL_CLAMP, GL_CLAMP );
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        glClearColor(0,0,0, 1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LEQUAL);
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
//        //rotate light
//        Matrix4f rotLightMatrix;
//        Matrix4f rotLightMatX;
//        Matrix4f rotLightMatY;
//        rotLightMatX = Matrix4f::RotationX(-rotLightY * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
//        rotLightMatY = Matrix4f::RotationZ(rotLightX * (M_PI/180.0));
//        rotLightMatrix = rotLightMatX * rotLightMatY;
//
////        //shifting based on bounding box
////        Matrix4f translationMatrix = Matrix4f::Translation(-centre.XYZ());
////
//        Matrix4f scaleMatrix = Matrix4f::Scale(0.08);
//        Matrix4f modelMatrix = scaleMatrix ; //* translationMatrix; //
////
//        cameraRot = rotMatrix * Vec4f(camera,1);//rotating the camera
//        //for env
//        Matrix4f viewMatrix = Matrix4f::View(cameraRot.XYZ(), trans.XYZ(), up.XYZ());//camera, movees the angle with the obj also
//
//        Matrix4f projMatrix = Matrix4f::Perspective(40.0 * (M_PI/180.0), width/height, 0.1f, 1000.0f);
//        Matrix4f transMatrix = projMatrix * viewMatrix * modelMatrix;
//
//        //for lighting take from view only
//        Matrix4f mvMatrix = viewMatrix * modelMatrix;
//        Matrix3f normalMatrix = mvMatrix.GetSubMatrix3().GetInverse().GetTranspose();
//
//        //direction of light
//        Vec4f rotLightDirection = viewMatrix * rotLightMatrix * lightDirection;//used for light Light Direction
//
//        Vec4f rotLightDirectionL =  rotLightMatrix * lightDirection;
//        Matrix4f lightMatrix = Matrix4f::View(rotLightDirectionL.XYZ() , trans.XYZ(), up.XYZ());
//
//        Matrix4f matrixMLP = projMatrix * lightMatrix ;
//        Matrix4f matrixShadow = Matrix4f::Translation(transBias) * Matrix4f::Scale(0.5) * matrixMLP;
//
//        float matrixMlp[16];
//
//        //SHADOW everything
//        shadowMap.Bind();
//
//        glClear( GL_DEPTH_BUFFER_BIT );
//        glUseProgram( shadowProgram.GetID());
//
//        matrixMLP.Get(matrixMlp);
//        GLint samplerMLP = glGetUniformLocation(shadowProgram.GetID(), "mvp");//can directly use in next line
//        glUniformMatrix4fv( samplerMLP, 1, GL_FALSE, matrixMlp );//can do outside loop
//
//        GLint tes_level = glGetUniformLocation(shadowProgram.GetID(), "tesLevel");
//        glUniform1i(tes_level, tesLevel);
//        
//        //
//        glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
//        GLuint pos_location4 = glGetAttribLocation(shadowProgram.GetID(), "pos");
//        glEnableVertexAttribArray(pos_location4);
//        glVertexAttribPointer(pos_location4, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//        
//        GLint sampler_disp = glGetUniformLocation(shadowProgram.GetID(), "tex1");
//        glActiveTexture(GL_TEXTURE1); //disp texture unit
//        glBindTexture(GL_TEXTURE_2D, texID1);
//        glUniform1i(sampler_disp, 1);
//        glPatchParameteri( GL_PATCH_VERTICES, 4 );
//        glDrawArrays(GL_PATCHES, 0, 4);
//        shadowMap.Unbind();
//
////        glViewport( 0, 0, width, height );
////        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//        glUseProgram(prog.GetID());
////
////
//        //rendering everything
//        float matrixMvp[16];
//        float matrixMv[16];
//        float matrixNorm[9];
//        float matrixShad[16];
//
//        matrixShadow.Get(matrixShad);
//        GLint shadow_pos = glGetUniformLocation( prog.GetID(), "matrixShadow" );
//        glUniformMatrix4fv(shadow_pos, 1, GL_FALSE, matrixShad );
//
//        transMatrix.Get(matrixMvp);
//        GLint mvp_pos = glGetUniformLocation(prog.GetID(), "mvp");
//        glUseProgram(prog.GetID());
//        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
//
//        mvMatrix.Get(matrixMv);
//        GLint mv_pos = glGetUniformLocation(prog.GetID(), "mv");
//        glUseProgram(prog.GetID());
//        glUniformMatrix4fv(mv_pos, 1, GL_FALSE, matrixMv);
//
//        normalMatrix.Get(matrixNorm);
//        GLint normal_pos = glGetUniformLocation(prog.GetID(), "normalMatrix");
//        glUseProgram(prog.GetID());
//        glUniformMatrix3fv(normal_pos, 1, GL_FALSE, matrixNorm);
//
//        GLint lightDirection = glGetUniformLocation(prog.GetID(), "lightDirection");
//        glUseProgram(prog.GetID());
////        glUniform3f(lightDirection, 25.0,25.0,25.0);
//        glUniform3f(lightDirection, rotLightDirection.x, rotLightDirection.y, rotLightDirection.z);
////        fprintf(stdout, " Light position: %.2f, %.2f, %.2f\n", rotLightDirection.x, rotLightDirection.y, rotLightDirection.z);
//
//        GLint shine = glGetUniformLocation(prog.GetID(), "shine");
//        glUseProgram(prog.GetID());
//        glUniform1f(shine, 80.0);
//        
//        GLint camera = glGetUniformLocation(prog.GetID(), "camera");
//        glUseProgram(prog.GetID());
//        glUniform3f(camera, cameraRot.x,cameraRot.y,cameraRot.z);
//        
//        GLint tes_levelP = glGetUniformLocation(prog.GetID(), "tesLevel");
//        glUniform1i(tes_levelP, tesLevel);
//        
////        glEnable(GL_DEPTH_TEST);
//
//        GLuint pos_loc_plane = glGetAttribLocation(prog.GetID(), "pos");
//        glUseProgram(prog.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
//        glEnableVertexAttribArray(pos_loc_plane);
//        glVertexAttribPointer(pos_loc_plane, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        GLuint normal_loc_plane = glGetAttribLocation(prog.GetID(), "normal");
//        glUseProgram(prog.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, planevertexnormalbuffer);
//        glEnableVertexAttribArray(normal_loc_plane);
//        glVertexAttribPointer(normal_loc_plane, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//
//        GLuint txc_loc_plane = glGetAttribLocation(prog.GetID(), "txc");
//        glUseProgram(prog.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, txc);
//        glEnableVertexAttribArray(txc_loc_plane);
//        glVertexAttribPointer(txc_loc_plane, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//        
//        glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
//        glBindTexture(GL_TEXTURE_2D, texID0);
//        GLint sampler = glGetUniformLocation(prog.GetID(), "tex0"); //texNorm, using as normals
//        glUseProgram(prog.GetID());
//        glUniform1i(sampler, 0);//0 coz texture unit 0, texID0
//
//
//        glActiveTexture(GL_TEXTURE1); //specifying texture unit number, here is the default
//        glBindTexture(GL_TEXTURE_2D, texID1);
//        GLint sampler1 = glGetUniformLocation(prog.GetID(), "tex1"); //texDisp, in tes, to the positions
//        glUseProgram(prog.GetID());
//        glUniform1i(sampler1, 1);//1 coz texture unit 1, texID1
//        
//        //CHECK, rendering it
//        glActiveTexture(GL_TEXTURE2);
//        GLint samplerS = glGetUniformLocation(prog.GetID(), "shadow");
//        glUniform1i(samplerS, 2);
//        shadowMap.BindTexture(2);
//        
//        glPatchParameteri( GL_PATCH_VERTICES, 4 );
//        glDrawArrays(GL_PATCHES, 0, 4);
//        
//       
//        //for lines of tesselation
//        glUseProgram(progLines.GetID());
//        GLint mvp_pos1 = glGetUniformLocation( progLines.GetID(), "mvp" );
//        transMatrix.Get(matrixMvp);
//        glUniformMatrix4fv(mvp_pos1, 1, GL_FALSE, matrixMvp);
//
//        glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
//        GLuint pos_loc1 = glGetAttribLocation(progLines.GetID(), "pos");
//        glEnableVertexAttribArray(pos_loc1);
//        glVertexAttribPointer(pos_loc1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        glBindBuffer(GL_ARRAY_BUFFER, txc);
//        GLuint txc_loc1 = glGetAttribLocation(progLines.GetID(), "txc");
//        glEnableVertexAttribArray(txc_loc1);
//        glVertexAttribPointer(txc_loc1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        GLint tes_level1 = glGetUniformLocation(progLines.GetID(), "tesLevel");
//        glUniform1i(tes_level1, tesLevel);
//        
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texID1);
//        GLint sampler_disp1 = glGetUniformLocation(progLines.GetID(), "tex1");
//        glUniform1i(sampler_disp1, 1);
//
//        if(spacePressed){
//            glDepthFunc(GL_ALWAYS);//for line dash
//            glPatchParameteri( GL_PATCH_VERTICES, 4 );
//            glDrawArrays(GL_PATCHES, 0, 4);
//            glDepthFunc(GL_LEQUAL);
//        }
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
////-----------------------------------------------------------------------------------------------------------------
