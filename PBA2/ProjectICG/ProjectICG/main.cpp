////
////  main.cpp
////  ProjectICG
////
////  Created by Nishita Kharche.
////
////int main(int argc, const char * argv[]) {
////    // insert code here...
////    std::cout << "Hello, World!\n";
////    return 0;
////}
//
//
//#define GL_SILENCE_DEPRECATION
//
//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <GLUT/glut.h>
//#include "cyTriMesh.h"
//#include "cyCore.h"
//#include "cyVector.h"
//#include "cyGL.h"
//#include "cyMatrix.h"
//// check the order of the header files
//using namespace std;
//using namespace cy;
//
////float blue = 0.0f;
////int direction = 1;
//
//GLuint vao; //vertex array object
//GLuint vbo; //vertex buffer object
//
//double newRotX = 0.0f;
//double newRotY = 0.0f;
//double prevRotX = 0.0f;
//double prevRotY = 0.0f;
//
//double prevTransX = 0.0f;
//double prevTransY = 0.0f;
//double newTransX = 0.0f;
//double newTransY = 0.0f;
//
//float mat[16];
//Vec3f trans(0.0,0.0,0.0);
//Vec3f up(0.0,1.0,0.0);
//Vec3f camera(0.0,0.0,-5.0);
//Vec3f minBound(0.0,0.0,0.0);
//Vec3f maxBound(1.0,1.0,1.0);
//Vec3f centre(0.0,0.0,0.0);
//
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, 1); //GLFW_TRUE is 1
//
//}
//
//int main( int argc, char* argv[] )
//{
//    GLFWwindow* window;
//    /* Initialize the library */
//    if (!glfwInit())
//        exit(EXIT_FAILURE);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(720, 580, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//    
//    //load object
//    TriMesh mesh;
//    mesh.LoadFromFileObj(argv[1]);
//    
//    glfwSetKeyCallback(window, key_callback);
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    GLenum err = glewInit();
//    if (GLEW_OK != err)
//    {
//      /* if glewInit failed */
//      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
//        return 1;
//    }
//    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
//
//
//    
//    GLSLProgram progShader; //prog in her program
//    progShader.CreateProgram();
//    progShader.BuildFiles("shader.vert", "shader.frag");
//    progShader.Bind();
//    
//    
//    //create vertex array object, do this first
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    
//    //creating vertex buffer object
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh.NV(), &mesh.V(0), GL_STATIC_DRAW);
//    //(multiple vbo can go to 1 vao)
//
//    GLuint pos_loc = glGetAttribLocation(progShader.GetID(), "pos");
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClearColor(0, 0, 0, 1);
//
//        /* Animate Background (blue - black - blue)
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        if(blue>1.0)
//            direction = -1;
//        if(blue<0.0)
//            direction = 1;
//        blue = blue + (0.02 * direction);
//
//        //Set colour
//        glClearColor(0,0,blue,0);
//        */
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //recheck
//
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//            glfwGetCursorPos(window, &newRotX, &newRotY);
//        }
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
//            glfwGetCursorPos(window, &newTransX, &newTransY);
//            camera.z = camera.z + 0.05 * (prevTransX - newTransX); //zooming, 'pos' is the camera location
//            prevTransX = newTransX;
//        }
//
//        // adding the rotation from the mouse coordinates
//        Matrix4f modelMatrix;
//        Matrix4f modelMatrixX;
//        Matrix4f modelMatrixY;
//        modelMatrixX = modelMatrix.RotationX(-newRotY * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
//        modelMatrixY = modelMatrix.RotationZ(newRotX * (M_PI/180.0));
//
//        // resets from the original 0 rotation
////        modelMatrixX = modelMatrix.RotationX(-(prevRotY-newY) * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
////        modelMatrixY = modelMatrix.RotationY(-(prevRotX-newX) * (M_PI/180.0));
////        if(prevRotX != newX)
////            prevRotX = newX;
////        if(prevRotY != newY)
////            prevRotY = newY;
//
//        modelMatrix = modelMatrixX * modelMatrixY;
//
//        // bounding box
//        mesh.ComputeBoundingBox();
//        if(mesh.IsBoundBoxReady()){
//            minBound = mesh.GetBoundMin();
//            maxBound = mesh.GetBoundMax();
//        }
//        centre.x = (minBound.x + maxBound.x) / 2.0;
//        centre.y = (minBound.y + maxBound.y) / 2.0;
//        centre.z = (minBound.z + maxBound.z) / 2.0;
//        Matrix4f transMatrix = cy::Matrix4f::Translation(-centre.XYZ());
//
//        // scaling to fit in the screen
//        Matrix4f scaleMatrix = Matrix4f::Scale(0.04f);
//        // final matrix after adding all up
//        Matrix4f finMatrix = modelMatrix * scaleMatrix * transMatrix;
//
//        Matrix4f viewMatrix = Matrix4f::View(camera.XYZ(), trans.XYZ(), up.XYZ()); //position of camera, target(initially 0, then bounding box center), Y //what we are seeing of the model
//        Matrix4f projMatrix = Matrix4f::Perspective(40.0 * (M_PI/180.0), 1920.0/1080.0, 0.1f, 1000.0f);//perspective (or orthographic). field of view, aspect ratio, near plane, far plane
//
//        Matrix4f finalMatrix = projMatrix * viewMatrix *finMatrix; //rotation, scaling(to fit in our view), translation(bounding box)
//        finalMatrix.Get(mat); // putting values of matrix in the float array
//
//        GLint mvpLocation = glGetUniformLocation(progShader.GetID(), "mvp"); //mvp_pos, getting the location of var in shader
//        glUseProgram(progShader.GetID()); //bind program
//        //progShader["mvp"] = mat; //not working
//        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mat); //'matrix' in her code, putting matrix in mvp location
//
//        glEnableVertexAttribArray(pos_loc);
//        glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0); //how to pick the data , 3 floats
//        
//        // draw the object
//        glDrawArrays(GL_POINTS, 0, mesh.NV());
//        
//        glDisableVertexAttribArray(pos_loc);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}
//
