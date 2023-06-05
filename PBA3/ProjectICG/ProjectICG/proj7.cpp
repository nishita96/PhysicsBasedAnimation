////
////  proj7.cpp
////  ProjectICG
////
////  Created by Nishita Kharche on 3/9/22.
////
////
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
//// camera viewing changes based on this
//Vec3f camera(0.0,25.0,-1.0); //-20 showed the plane reflections
////Vec3f cameraPlane(0.0,0.0,-15.0);
//Vec3f trans(0.0,0.0,0.0);
//Vec3f up(0.0,1.0,0.0);
//
//Vec3f boundMin(0.0,0.0,0.0);
//Vec3f boundMax(1.0,1.0,1.0);
//Vec3f centre(0.0,0.0,0.0);
//
//Vec3f planeShift(0.0,12.0,0.0);
//
//Vec4f lightDirection(10.0, 50.0, -20.0, 0.0);
//
//bool ctrlPressed = false;
//bool altPressed = false;
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
//// used in viewport
//int width = 2280;
//int height = 2020;
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
////proj7
//GLuint depthMap;
////double shadWidth = 5000;
////double shadHeight = 4000;
//double shadWidth = 2280;
//double shadHeight = 2020;
//
//float sizePlane = 60.0f ;
//float limitPlane = sizePlane + 23.0;
//Vec3f spherePosition(0.0, 0.0, 0.0);
//Vec3f sphereVelocity(1.0, 0.0, 1.0);
//Vec3f spherePositionInitial(0.0, 0.0, 0.0);
//Vec3f spherePositionFinal(0.0, 0.0, 0.0);
//bool clickFlag = false;
//bool startFlag = false;
//
//Vec3f transBias(0.5,0.5,0.5 - 0.0000066);
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
//static void createVertexBufferPlane(){
//
//    static const GLfloat vertex_buffer[] = {
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
//    };
//
//    glGenBuffers(1, &planevertexbuffer); //vbo0,
//    glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &planevertexnormalbuffer); //vbo1
//    glBindBuffer(GL_ARRAY_BUFFER, planevertexnormalbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_normal), plane_vertex_normal, GL_STATIC_DRAW);
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
////        glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
////        fprintf(stdout, " Mouse Click position: %.2f, %.2f\n", newRotLightX, newRotLightY);
//        if (ctrlPressed){
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            rotLightX = rotLightX + newRotLightX - prevRotPlaneX;
//            rotLightY = rotLightY + newRotLightY - prevRotPlaneY;
//            prevRotPlaneX = newRotLightX;
//            prevRotPlaneY = newRotLightY;
//        }
//        else{
//            if(!clickFlag){// if false
//                //it is first click
//                sphereVelocity = Vec3f(0.0, 0.0, 0.0);
//                spherePositionInitial = Vec3f(newRotObjX, 0.0, newRotObjY);
//                clickFlag = true;
//            }
//            
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            rotObjX = rotObjX + newRotObjX - prevRotObjX;
//            rotObjY = rotObjY + newRotObjY - prevRotObjY;
//            prevRotObjX = newRotObjX;
//            prevRotObjY = newRotObjY;
//        }
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
//        if(clickFlag){
//            spherePositionFinal = Vec3f(newRotObjX, 0.0, newRotObjY);
//            clickFlag = false;
//            startFlag = true;
//        }
//        
//        
//        glfwGetCursorPos(window, &newRotPlaneX, &newRotPlaneY);
////        fprintf(stdout, " Mouse Release position: %.2f, %.2f\n", &newRotPlaneX, &newRotPlaneY);
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
//    
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
//    //create mesh
//    TriMesh mesh;
//    mesh.LoadFromFileObj(args[1]); //loading sphere
//    mesh.ComputeBoundingBox();
//    mesh.ComputeNormals();
//
//    if(argc > 1){
//        std::string arg1(args[1]);
//        fprintf(stdout, "\n\n\n\n\n\n Argument: %s\n", arg1.c_str());
//        std::string arg2(args[2]);
//        fprintf(stdout, " Argument 2: %s\n", arg2.c_str());
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
//    GLSLProgram progTeapot; //use for both teapot and plane
//    progTeapot.CreateProgram();
//    if(progTeapot.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    progTeapot.BuildFiles("shader.vert", "shader.frag");
//
//    GLSLProgram prog; //use for both teapot and plane
//    prog.CreateProgram();
//    if(prog.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    prog.BuildFiles("shader.vert", "shader.frag");
//
////    GLSLProgram progPlane;
////    progPlane.CreateProgram();
////    if(progPlane.IsNull()){
////        fprintf(stderr, "Error creating shader program. \n");
////        return 1;
////    }
////    progPlane.BuildFiles("shader.vert", "shader.frag");
//
//    GLSLProgram shadowProgram;
//    shadowProgram.CreateProgram();
//    shadowProgram.BuildFiles("shader1.vert", "shader1.frag");
//    if(shadowProgram.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//
//
//
//    createVertexArray();
//    createVertexBuffer(&mesh);//teapot
//    createVertexBufferPlane();
//
//    //calculate bounding box and centre obj, this works irrespective of the object size changes
//    boundMin = mesh.GetBoundMin();
//    boundMax = mesh.GetBoundMax();
//    centre.x =  (boundMin.x + boundMax.x) / 2.0;
//    centre.y =  (boundMin.y + boundMax.y) / 2.0;
//    centre.z =  (boundMin.z + boundMax.z) / 2.0;
//
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
//
//        getMouseCoordinates(window);
//
//        //rotate object
////        Matrix4f rotMatrix;
////        Matrix4f rotMatX;
////        Matrix4f rotMatY;
//        
////        rotMatX = Matrix4f::RotationX(-rotObjY * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
////        rotMatY = Matrix4f::RotationY(-rotObjX * (M_PI/180.0));
////        rotMatrix = rotMatX * rotMatY;
//        
////        rotMatrix = Matrix4f::RotationXYZ(-rotObjY * (M_PI/180.0), -rotObjX * (M_PI/180.0), 0);
//        
//
//        //rotate light
//        Matrix4f rotLightMatrix;
//        Matrix4f rotLightMatX;
//        Matrix4f rotLightMatY;
////        rotLightMatX = Matrix4f::RotationX(-rotLightY * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
////        rotLightMatY = Matrix4f::RotationZ(rotLightX * (M_PI/180.0));
//        rotLightMatX = Matrix4f::RotationX(0.0 * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
//        rotLightMatY = Matrix4f::RotationZ(0.0 * (M_PI/180.0));
//        rotLightMatrix = rotLightMatX * rotLightMatY;
//
//        //shifting based on bounding box // SPHERE movement based on mouse
////        Matrix4f translationMatrix = Matrix4f::Translation(-centre.XYZ());
//        
////        Matrix4f translationMatrix = Matrix4f::Translation(Vec3f(0.0, 0.0, 0.0));
////        Matrix4f translationMatrix = Matrix4f::Translation(Vec3f(limitPlane, 0.0, limitPlane));
////        if(abs(rotObjX) <= (3*limitPlane) && abs(rotObjY) <= (3*limitPlane)){
////            translationMatrix = Matrix4f::Translation(Vec3f(-rotObjX/3, 0.0, -rotObjY/3));
////        }
//        
//        // for velocity
//        sphereVelocity = spherePositionFinal - spherePositionInitial;
////        Vec3f sphereVelocityN = Normalize(sphereVelocity);
////        sphereVelocity = Normalize(sphereVelocity);
//        sphereVelocity = sphereVelocity / 50;
////        if(startFlag){
//            spherePosition.x = spherePosition.x - sphereVelocity.x;
//            spherePosition.z = spherePosition.z - sphereVelocity.z;
////        }
//        fprintf(stdout, " Sphere Velocity: %.2f, %.2f, %.2f\n", sphereVelocity.x, sphereVelocity.y, sphereVelocity.z);
//        Matrix4f translationMatrix = Matrix4f::Translation(Vec3f(spherePosition)); // the /3 is for making the movement similar to the aomunt of the mouse
//        
////        Matrix4f translationMatrix = Matrix4f::Translation(Vec3f(-rotObjX/3, 0.0, -rotObjY/3)); //Mouse movement, the /3 is for making the movement similar to the aomunt of the mouse
//        Matrix4f scaleMatrix = Matrix4f::Scale(0.01);
//        Matrix4f modelMatrix = scaleMatrix * translationMatrix;
//
////        cameraRot = rotMatrix * Vec4f(camera,1);//rotating the camera
//        cameraRot = Vec4f(camera,1);//rotating the camera
//        //for env
//        Matrix4f viewMatrix = Matrix4f::View(cameraRot.XYZ(), trans.XYZ(), up.XYZ());//camera, movees the angle with the obj also
//
//        Matrix4f projMatrix = Matrix4f::Perspective(40.0 * (M_PI/180.0), width/height, 0.1f, 1000.0f);
//        Matrix4f transMatrix = projMatrix * viewMatrix * modelMatrix;
//        
//        // for plane
//        Matrix4f translationMatrixP = Matrix4f::Translation(-planeShift.XYZ());
////        Vec3f planeTrans(rotObjY, rotObjY, 0.0);
////        Matrix4f translationMatrixP = Matrix4f::Translation(Vec3f(rotObjX, rotObjY, 0.0));
//        Matrix4f scaleMatrixP = Matrix4f::Scale(0.08);
//        Matrix4f modelMatrixP = scaleMatrixP * translationMatrixP;
//        Matrix4f transMatrixP = projMatrix * viewMatrix * modelMatrixP;
//
//        //for lighting take from view only
//        Matrix4f mvMatrix = viewMatrix * modelMatrixP;// changed from modelMatrix
//        Matrix3f normalMatrix = mvMatrix.GetSubMatrix3().GetInverse().GetTranspose();
//
//        //direction of light
//        Vec4f rotLightDirection = viewMatrix * rotLightMatrix * lightDirection;//used for light Light Direction
//
//        cy::Vec4f rotLightDirectionL =  rotLightMatrix * lightDirection;
//        Matrix4f lightMatrix = Matrix4f::View(rotLightDirectionL.XYZ() , trans.XYZ(), up.XYZ());
//
//        Matrix4f matrixMLP = projMatrix * lightMatrix ;
//        Matrix4f matrixShadow = Matrix4f::Translation(transBias) * Matrix4f::Scale(0.5) * matrixMLP;
//
//        float matrixMlp[16];
//        
//        
//        
//        
//        
//        
//        
//        
//        
//
//        //SHADOW everything, render the depth map
//        shadowMap.Bind();
//
//        glClear( GL_DEPTH_BUFFER_BIT );
//        glUseProgram( shadowProgram.GetID());
//
//        matrixMLP.Get(matrixMlp);
//        GLint samplerMLP = glGetUniformLocation(shadowProgram.GetID(), "mvp");//can directly use in next line
//        glUniformMatrix4fv( samplerMLP, 1, GL_FALSE, matrixMlp );//can do outside loop
//
//        glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//        GLuint pos_location4 = glGetAttribLocation(shadowProgram.GetID(), "pos");
//        glEnableVertexAttribArray(pos_location4);
//        glVertexAttribPointer(pos_location4, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//        glDrawElements(GL_TRIANGLES, sizeof(cy::Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0); //the shadow
//        shadowMap.Unbind();
//
//        glViewport( 0, 0, width, height );
//        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//        glUseProgram(progTeapot.GetID());
//        
//        
//        
//        
//        
//        
//        
//        
//        
//
//
//        //SPHERE rendering everything
//        float matrixMvp[16];
//        float matrixMv[16];
//        float matrixNorm[9];
//        float matrixShad[16];
//
//        matrixShadow.Get(matrixShad);
//        GLint shadow_pos = glGetUniformLocation( progTeapot.GetID(), "matrixShadow" );
//        glUniformMatrix4fv(shadow_pos, 1, GL_FALSE, matrixShad );
//
//        transMatrix.Get(matrixMvp);
//        GLint mvp_pos = glGetUniformLocation(progTeapot.GetID(), "mvp");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
//
//        mvMatrix.Get(matrixMv);
//        GLint mv_pos = glGetUniformLocation(progTeapot.GetID(), "mv");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mv_pos, 1, GL_FALSE, matrixMv);
//
//        normalMatrix.Get(matrixNorm);
//        GLint normal_pos = glGetUniformLocation(progTeapot.GetID(), "normalMatrix");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix3fv(normal_pos, 1, GL_FALSE, matrixNorm);
//
//        GLint lightDirection = glGetUniformLocation(progTeapot.GetID(), "lightDirection");
//        glUseProgram(progTeapot.GetID());
////        glUniform3f(lightDirection, 25.0,25.0,25.0);
//        glUniform3f(lightDirection, rotLightDirection.x, rotLightDirection.y, rotLightDirection.z);
////        fprintf(stdout, " Light position: %.2f, %.2f, %.2f\n", rotLightDirection.x, rotLightDirection.y, rotLightDirection.z);
//
//
//        GLint shine = glGetUniformLocation(progTeapot.GetID(), "shine");
//        glUseProgram(progTeapot.GetID());
//        glUniform1f(shine, 110.0);
//
//        //location = 0
//        glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//        GLuint pos_loc = glGetAttribLocation(progTeapot.GetID(), "pos");
//        glUseProgram(progTeapot.GetID());
//        glEnableVertexAttribArray(pos_loc);
//        glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE,
//                              0, (void*) 0);
//
//        //location = 1
//        glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//        GLuint normal_loc = glGetAttribLocation(progTeapot.GetID(), "normal");
//        glUseProgram(progTeapot.GetID());
//        glEnableVertexAttribArray(normal_loc);
//        glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//
//        glEnable(GL_DEPTH_TEST);
//        glUseProgram(progTeapot.GetID());
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//        glDrawElements(GL_TRIANGLES, sizeof(cy::Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0);
//
//        
//        
//        
//        
//        
//        
//        
//        
//        
//        
//
//        //PLANE everything
//        //matrix for plane
//        transMatrixP.Get(matrixMvp);
//        mvp_pos = glGetUniformLocation(progTeapot.GetID(), "mvp");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
//        
//        GLint samplerPlane = glGetUniformLocation(progTeapot.GetID(), "shadow");
//        glActiveTexture( GL_TEXTURE0 );
//        shadowMap.BindTexture(0);
//        glUniform1i(samplerPlane, 0);
//
//        GLuint pos_loc_plane = glGetAttribLocation(progTeapot.GetID(), "pos");
//        glUseProgram(progTeapot.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
//        glEnableVertexAttribArray(pos_loc_plane);
//        glVertexAttribPointer(pos_loc_plane, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//
//        GLuint normal_loc_plane = glGetAttribLocation(progTeapot.GetID(), "normal");
//        glUseProgram(progTeapot.GetID());
//        glBindBuffer(GL_ARRAY_BUFFER, planevertexnormalbuffer);
//        glEnableVertexAttribArray(normal_loc_plane);
//        glVertexAttribPointer(normal_loc_plane, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//
//        glUseProgram(progTeapot.GetID());
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
////-----------------------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//
//
