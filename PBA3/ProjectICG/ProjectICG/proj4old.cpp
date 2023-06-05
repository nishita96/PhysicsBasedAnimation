////
////  proj4.cpp
////  ICGAsst
////
////  Created by Nishita Kharche on 2/4/22.
////
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
//// check the order of the header files
//using namespace std;
//using namespace cy;
//
//GLuint vao;
//GLuint vbo0;
//GLuint vbo1;
//GLuint ebuffer;
//GLuint texID;
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
//double prevZoomX = 0.0f;
//double prevZoomY = 0.0f;
//double newZoomX = 0.0f;
//double newZoomY = 0.0f;
//
//Vec3f camera(0.0,0.0,-20.0);
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
//
//unsigned int widthImg;
//unsigned int heightImg;
//
//static void createVertexArray(){
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//}
//
//static void createVertexBuffer(TriMesh *mesh){
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
//    
//    //for texture
//    glGenBuffers(1, &txc);
//    glBindBuffer(GL_ARRAY_BUFFER, txc);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NVT(), &mesh->VT(0), GL_STATIC_DRAW);
//}
//
//static void buildProgram( GLSLProgram prog){
//    prog.BuildFiles("shader.vert", "shader.frag");
//    prog.Bind();
//}
//
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
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
//
//    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE){
//        ctrlPressed = false;
//    }
//
//}
//
//int main( int argc, char* args[] )
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        exit(EXIT_FAILURE);
//
//    //to change the versions of glsl and opengl
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(1020, 680, "ICG Projects", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//
//    //create mesh
//    TriMesh mesh;
//    mesh.LoadFromFileObj(args[1]);
//    mesh.ComputeBoundingBox();
//    mesh.ComputeNormals();
//    
//    //change this
//    std::string rootDir;
//    if(argc > 1){
//        std::string ptr(args[1]);
//        rootDir = ptr.substr(0, ptr.find_last_of('/')+1);
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
//    //create vertex array object, do this first
//    createVertexArray();
//
//    //creating vertex buffer object
//    createVertexBuffer(&mesh);
//
//    GLSLProgram prog;
//    prog.CreateProgram();
//    if(prog.IsNull()){
//        fprintf(stderr, "Error creating shader program. \n");
//        return 1;
//    }
//    buildProgram(prog);
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
//        /* Render here */
//        glClearColor(0, 0, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && ctrlPressed == false){
//            //rotation
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            rotObjX += newRotObjX - prevRotObjX;
//            prevRotObjX = newRotObjX;
//            rotObjY += newRotObjY - prevRotObjY;
//            prevRotObjY = newRotObjY;
//        }
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && ctrlPressed == false){ //store value when released
//            //rotation
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            prevRotObjX = newRotObjX;
//            prevRotObjY = newRotObjY;
//        }
//
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && ctrlPressed == true){
//            //light move
////            fprintf(stdout, "WORKSSSSS\n");
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            rotLightX += newRotLightX - prevRotLightX;
//            prevRotLightX = newRotLightX;
//            rotLightY += newRotLightY - prevRotLightY;
//            prevRotLightY = newRotLightY;
//        }
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && ctrlPressed == true){
//            //light move
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            prevRotLightX = newRotLightX;
//            prevRotLightY = newRotLightY;
//        }
//
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
//            //zoom in and out along z
//            glfwGetCursorPos(window, &newZoomX, &newZoomY);
//            camera.z = camera.z + 0.05 * (prevZoomX - newZoomX); //zooming, 'pos' is the camera location
//            prevZoomX = newZoomX;
//        }
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
//            //release right click
//            glfwGetCursorPos(window, &newZoomX, &newZoomY);
//            prevZoomX = newZoomX;
//        }
//
//        // adding the rotation from the mouse coordinates
//        Matrix4f rotMatrix;
//        Matrix4f rotMatX;
//        Matrix4f rotMatY;
//        Matrix4f modelMatrix;
//        rotMatX = Matrix4f::RotationX(-rotObjY * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
//        rotMatY = Matrix4f::RotationZ(rotObjX * (M_PI/180.0));
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
//        //shifting based on bounding box
//        Matrix4f translationMatrix = Matrix4f::Translation(-centre.XYZ());
//
//        Matrix4f scaleMatrix = Matrix4f::Scale(0.15);
//        modelMatrix = rotMatrix * scaleMatrix * translationMatrix;
//
//        Matrix4f viewMatrix = Matrix4f::View(camera.XYZ(), trans.XYZ(), up.XYZ());
//        Matrix4f projMatrix = Matrix4f::Perspective(40.0 * (M_PI/180.0), 1020.0/680.0, 0.1f, 1000.0f);
//
//        Matrix4f transMatrix = projMatrix * viewMatrix * modelMatrix;
//
//        //for lighting take from view only
//        Matrix4f mvMatrix = viewMatrix * modelMatrix;
//        //normals
//        Matrix3f normalMatrix = mvMatrix.GetSubMatrix3().GetInverse().GetTranspose();
//
//        Vec4f rotLightDirection = viewMatrix * rotLightMatrix * lightDirection;
//
//        float matrixMvp[16];
//        float matrixMv[16];
//        float matrixNorm[9];
//        transMatrix.Get(matrixMvp);
//        mvMatrix.Get(matrixMv);
//        normalMatrix.Get(matrixNorm);
//
//        GLint mvp_pos = glGetUniformLocation(prog.GetID(), "mvp");
//        glUseProgram(prog.GetID());
//        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
//
//        GLint mv_pos = glGetUniformLocation(prog.GetID(), "mv");
//        glUseProgram(prog.GetID());
//        glUniformMatrix4fv(mv_pos, 1, GL_FALSE, matrixMv);
//
//        GLint normal_pos = glGetUniformLocation(prog.GetID(), "normalMatrix");
//        glUseProgram(prog.GetID());
//        glUniformMatrix3fv(normal_pos, 1, GL_FALSE, matrixNorm);
//
//        GLint lightDir = glGetUniformLocation(prog.GetID(), "lightDirection");
//        glUseProgram(prog.GetID());
////        glUniform3f(lightDir, 0.0, 0.0, 0.0);
//        glUniform3f(lightDir, rotLightDirection.x, rotLightDirection.y, rotLightDirection.z);
//
//        GLint shine = glGetUniformLocation(prog.GetID(), "shine");
//        glUseProgram(prog.GetID());
//        glUniform1f(shine, 40.0);
//
//        //location = 0
//        GLuint pos_loc = glGetAttribLocation(prog.GetID(), "pos");
//        glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//        glEnableVertexAttribArray(pos_loc);
//        glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//
//        //location = 1
//        GLuint normal_loc = glGetAttribLocation(prog.GetID(), "normal");
//        glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//        glEnableVertexAttribArray(normal_loc);
//        glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//        
//        //texture things
//        
//        
//        glGenBuffers(1, &texID);
////        glBindTexture(GL_TEXTURE_2D, texID);
//        
//        
//        //change this
//        std::string filename = rootDir + std::string(mesh.M(0).map_Kd);
//        std::vector<unsigned char> png;
//        std::vector<unsigned char> texImage; //the raw pixels
//        unsigned error = lodepng::load_file(png, filename.c_str()); //load the image file with given filename
//        if(!error) error = lodepng::decode(texImage, widthImg, heightImg, png);
//        //if there's an error, display it
//        if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//        
//        glTexImage2D(GL_TEXTURE_2D,
//                     0,
//                     GL_RGBA,
//                     widthImg,
//                     heightImg,
//                     0,
//                     GL_RGBA,
//                     GL_UNSIGNED_BYTE,
//                     texImage.data()); //pixel data
//        glGenerateMipmap(GL_TEXTURE_2D);
//        glTexParameteri(
//                        GL_TEXTURE_2D,
//                        GL_TEXTURE_MIN_FILTER,
//                        GL_LINEAR_MIPMAP_LINEAR
//            );
//        glTexParameteri(
//                       GL_TEXTURE_2D,
//                       GL_TEXTURE_MAG_FILTER,
//                       GL_LINEAR
//           );
//        glTexParameteri(
//                        GL_TEXTURE_2D,
//                        GL_TEXTURE_WRAP_S,
//                        GL_REPEAT
//            );
//
//        glTexParameteri(
//                        GL_TEXTURE_2D,
//                        GL_TEXTURE_WRAP_T,
//                        GL_CLAMP_TO_BORDER
//            );
//        glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
//        glBindTexture(GL_TEXTURE_2D, texID); //GL_TEXTURE0 will use texID
//        
//        //connect uniform variable to the texture unit
//        GLint sampler = glGetUniformLocation(prog.GetID(), "tex");
//        glUseProgram(prog.GetID());
//        glUniform1i(sampler, 0);//0 coz texture unit 0
//        
//        //location = 2
//        GLuint txc_loc = glGetAttribLocation(prog.GetID(), "txc");
//        glBindBuffer(GL_ARRAY_BUFFER, txc);
//        glEnableVertexAttribArray(txc_loc);
//        glVertexAttribPointer(txc_loc, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//        
//        glDrawElements(GL_TRIANGLES, sizeof(Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0);
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
////------------------------------------------------------------------------------------------------------------
