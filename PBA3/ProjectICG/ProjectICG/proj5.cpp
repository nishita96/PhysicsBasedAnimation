//
//
////
////
////  proj5.cpp
////  ICGAsst
////
////  Created by Nishita Kharche on 2/4/22.
//// 4
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
//bool altPressed = false;
//
//unsigned int widthImg = 1920;
//unsigned int heightImg = 1020;
//
//
//double texRotX = 0.0f;
//double texRotY = 0.0f;
//double newtexRotX = 0.0f;
//double newtexRotY = 0.0f;
//double prevtexRotX = 0.0f;
//double prevtexRotY = 0.0f;
//
////GLRenderTexture2D renderTexture;
//
//string path = "";
//string file0 = "";
//vector<unsigned char> png0;
//vector<unsigned char> texImage;
//string file1 = "";
//vector<unsigned char> png1;
//vector<unsigned char> texImage1;
//
//GLuint frameBuffer = 0;
//GLuint renderedTexture;
//GLuint depthBuffer;
//unsigned int textureWidth = 640;
//unsigned int textureHeight = 480;
//
//GLuint quad_vertexbuffer;
//GLuint quad_VertexArrayID;
//
//static void createVertexArray(){
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//}
//
//static void createVertexBuffer(TriMesh *mesh){
//
//    //all vertices are vec3f
//    Vec3f vPos[mesh->NV() * 7]; //need space to add more, hence *7
//    Vec3f vNorm[mesh->NVN() * 7];
//    Vec3f vTex[mesh->NV() * 7];
//    //face list
//    TriMesh::TriFace face[mesh->NF()];
//
//    int vCnt = mesh->NV();
//    for (int i=0; i < vCnt; i++ ){
//        vPos[i] = mesh->V(i);
//    }
//    for (int i=0; i < mesh->NVN(); i++ ){
//        vNorm[i] = mesh->VN(i);
//    }
//    for (int i=0; i < mesh->NVT(); i++ ){
//        vTex[i].Set(0.0,0.0,0.0);
//    }
//    for (int i=0; i < mesh->NF(); i++ ){
//        face[i] = mesh->F(i);
//    }
//
//    for (int i=0; i < mesh->NF(); i++ ){ //check for all faces
//        for (int j=0; j <= 2; j++ ){ //the 3 vertex indices
//            if(mesh->F(i).v[j] == mesh->FT(i).v[j]){//if the indices are same
//                vTex[mesh->F(i).v[j]] = mesh->VT(mesh->F(i).v[j]); //texture vertex of the face texture corner
//            }
//            else{//diff value of face v & face texture v, add this case of the new vertex()
//                face[i].v[j] = vCnt; //change the vertex mapping to the new vertex, cant set value to mesh->F(i)
//                vPos[vCnt] = mesh->V(mesh->F(i).v[j]); //adding new vertex position, copying same value to new index
//                vNorm[vCnt] = mesh->VN(mesh->F(i).v[j]); //adding new vertex normal, copying same value to new index
//                vTex[vCnt] = mesh->VT(mesh->FT(i).v[j]); //adding new texture vertex with the new values
//                vCnt++;
//            }
//        }
//    }
//
//    glGenBuffers(1, &vbo0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*vCnt, vPos, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &vbo1);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*vCnt, vNorm, GL_STATIC_DRAW);
//
//    //faces with texture
//    glGenBuffers(1, &ebuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face[0])*mesh->NF(), face, GL_STATIC_DRAW);
//
//    //for texel
//    glGenBuffers(1, &txc);
//    glBindBuffer(GL_ARRAY_BUFFER, txc);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NVT(), &mesh->VT(0), GL_STATIC_DRAW);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NF(), &mesh->FT(0), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*vCnt, vTex, GL_STATIC_DRAW);
//}
//
//static void buildProgram( GLSLProgram prog){
//    prog.BuildFiles("shader.vert", "shader.frag");
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
//
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS ){ //}&& ctrlPressed == false){
//        if(ctrlPressed == true){
//            //light move
//    //            fprintf(stdout, "WORKSSSSS\n");
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            rotLightX += newRotLightX - prevRotLightX;
//            prevRotLightX = newRotLightX;
//            rotLightY += newRotLightY - prevRotLightY;
//            prevRotLightY = newRotLightY;
//        }
//        if (altPressed){
//            glfwGetCursorPos(window, &newtexRotX, &newtexRotY);
//            texRotX = texRotX + newtexRotX - prevtexRotX;
//            texRotY = texRotX + newtexRotY - prevtexRotY;
//            prevtexRotX = newtexRotX;
//            prevtexRotY = newtexRotY;
//
//        }
//        else{
//            //obj rotation
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            rotObjX += newRotObjX - prevRotObjX;
//            prevRotObjX = newRotObjX;
//            rotObjY += newRotObjY - prevRotObjY;
//            prevRotObjY = newRotObjY;
//        }
//
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){ //&& ctrlPressed == false){ //store value when released
//        if(ctrlPressed == true){
//            //light move
//            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
//            prevRotLightX = newRotLightX;
//            prevRotLightY = newRotLightY;
//        }
//        if(altPressed == true){
//            glfwGetCursorPos(window, &newtexRotX, &newtexRotY);
//            prevtexRotX = newtexRotX;
//            prevtexRotY = newtexRotY;
//        }
//        else {
//            //rotation
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            prevRotObjX = newRotObjX;
//            prevRotObjY = newRotObjY;
//        }
//
//    }
//
////    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && ctrlPressed == true){
////        //light move
//////            fprintf(stdout, "WORKSSSSS\n");
////        glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
////        rotLightX += newRotLightX - prevRotLightX;
////        prevRotLightX = newRotLightX;
////        rotLightY += newRotLightY - prevRotLightY;
////        prevRotLightY = newRotLightY;
////    }
////    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE && ctrlPressed == true){
////        //light move
////        glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
////        prevRotLightX = newRotLightX;
////        prevRotLightY = newRotLightY;
////    }
//
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
//        //zoom in and out along z
//        glfwGetCursorPos(window, &newZoomX, &newZoomY);
//        camera.z = camera.z + 0.05 * (prevZoomX - newZoomX); //zooming, 'pos' is the camera location
//        prevZoomX = newZoomX;
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
//        //release right click
//        glfwGetCursorPos(window, &newZoomX, &newZoomY);
//        prevZoomX = newZoomX;
//    }
//}
//
//static void createTextureUnit(TriMesh *mesh){
//    //generate texture unit 0 for specular
//    file0 = path + string(mesh->M(0).map_Kd);
//    unsigned error = lodepng::load_file(png0, file0.c_str()); //load the image file with given filename
//    if(!error) error = lodepng::decode(texImage, widthImg, heightImg, png0);
//    //if there's an error, display it
//    if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
//
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
//
//    //generate texture unit 1 for diffuse and ambient
//    file1 = path + string(mesh->M(0).map_Ks);
//    unsigned error1 = lodepng::load_file(png1, file1.c_str()); //load the image file with given filename
//    if(!error1) error1 = lodepng::decode(texImage1, widthImg, heightImg, png1);
//    //if there's an error, display it
//    if(error1) std::cout << "decoder error " << error1 << ": " << lodepng_error_text(error1) << std::endl;
//
//    glActiveTexture(GL_TEXTURE1); //specifying texture unit number, here is the default
//    glGenBuffers(1, &texID1);
//    glBindTexture(GL_TEXTURE_2D, texID1);
//    glTexImage2D(GL_TEXTURE_2D,
//                 0,
//                 GL_RGBA,
//                 widthImg,
//                 heightImg,
//                 0,
//                 GL_RGBA,
//                 GL_UNSIGNED_BYTE,
//                 texImage1.data()); //pixel data, this is rendering the texture
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
//
//}
//
//static bool createFrameBuffer(){
//
//    glGenFramebuffers( 1, &frameBuffer );
//
//    glGenTextures( 1, &renderedTexture );
//    glBindTexture( GL_TEXTURE_2D, renderedTexture );
//    glTexImage2D( GL_TEXTURE_2D,
//                 0, GL_RGB, textureWidth, textureHeight, 0,
//                 GL_RGB, GL_UNSIGNED_BYTE, 0 );
////    glGenerateMipmap( renderedTexture );
//    glTexParameteri( GL_TEXTURE_2D,
//                    GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //GL_NEAREST
//    glTexParameteri( GL_TEXTURE_2D,
//                    GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//////    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
//////    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//////    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GL_MAX_TEXTURE_MAX_ANISOTROPY );
//
//    glGenRenderbuffers( 1, &depthBuffer );
//    glBindRenderbuffer( GL_RENDERBUFFER, depthBuffer );
//    glRenderbufferStorage( GL_RENDERBUFFER,
//                          GL_DEPTH_COMPONENT, textureWidth, textureHeight);
//
//    glBindFramebuffer( GL_FRAMEBUFFER, frameBuffer );
//    glFramebufferRenderbuffer( GL_FRAMEBUFFER,
//                              GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer );
//    glFramebufferTexture( GL_FRAMEBUFFER,
//                         GL_COLOR_ATTACHMENT0, renderedTexture, 0 );
//    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
//    glDrawBuffers( 1, drawBuffers );
//    if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE ) return false;
//    return true;
//}
//
//static void createVertexBufferForPlane(){
//    // Vertex buffer for plane
//
//    glGenVertexArrays(1, &quad_VertexArrayID);
//    glBindVertexArray(quad_VertexArrayID);
//
//    static const GLfloat g_quad_vertex_buffer_data[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        -1.0f,  1.0f, 0.0f,
//        -1.0f,  1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        1.0f,  1.0f, 0.0f,
//    };
//    static const GLfloat plane_vertex_buffer_data[] = {
//        0.0f, 0.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        1.0f, 0.0f,0.0f,
//        1.0f, 0.0f,0.0f,
//        0.0f, 1.0f,0.0f,
//        1.0f, 1.0f,0.0f
//
//    };
//
//    glGenBuffers(1, &quad_vertexbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
//    glGenBuffers(1, &txc);
//    glBindBuffer(GL_ARRAY_BUFFER, txc);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_buffer_data), plane_vertex_buffer_data, GL_STATIC_DRAW);
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
//    window = glfwCreateWindow(widthImg, heightImg, "ICG Projects", NULL, NULL);
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
//
//    if(!createFrameBuffer()) return -1;
//    createVertexBufferForPlane();
//
//    //create texture units
//    createTextureUnit(&mesh);
//
//
//
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClearColor(0, 0, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//
//        //------------------------------------
////        prog.BuildFiles("shader.vert", "shader.frag");
////        prog.Bind();
////        glUseProgram(prog.GetID());
//
//        getMouseCoordinates(window);
//
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
//
////        cy::Vec3f lightTrans(-newXRot,-newYRot,0);
////        cy::Matrix4f translationLightMatrix = cy::Matrix4f::Translation(lightTrans.XYZ());
////        cy::Vec4f rotLightDir = viewMatrix_t * rotLightMatrix * translationLightMatrix * lightDirV;
//
//
//        Matrix4f scaleMatrix = Matrix4f::Scale(0.15);
//        modelMatrix = rotMatrix * scaleMatrix * translationMatrix;
//
//        Matrix4f viewMatrix = Matrix4f::View(camera.XYZ(), trans.XYZ(), up.XYZ());
//        Matrix4f projMatrix = Matrix4f::Perspective(40.0 * (M_PI/180.0), 1020.0/680.0, 0.1f, 1000.0f); //val
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
//        glUniform1f(shine, 80.0);
//
//        //connect uniform variable to the texture unit
//        GLint sampler = glGetUniformLocation(prog.GetID(), "tex0");
//        glUniform1i(sampler, 0);//0 coz texture unit 0, texID0
////        glUseProgram(prog.GetID());
//        glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
//        glBindTexture(GL_TEXTURE_2D, texID0);
//
//        //
//        //
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer); //not in vid
//
//        glBindFramebuffer( GL_FRAMEBUFFER, frameBuffer );
//        glViewport( 0, 0, textureWidth, textureHeight );
//        glClearColor(0.5,0.5,0.5,1);
//        glClear(  GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//
//        glDrawElements(GL_TRIANGLES, sizeof(cy::Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0);
//        glGenerateMipmap( renderedTexture );
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
//        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GL_MAX_TEXTURE_MAX_ANISOTROPY );
//        //
//
//        GLint sampler1 = glGetUniformLocation(prog.GetID(), "tex1");
//        glUniform1i(sampler1, 1);//1 coz texture unit 1, texID1
////        glUseProgram(prog.GetID());
//        glActiveTexture(GL_TEXTURE1); //specifying texture unit number, here is the default
//        glBindTexture(GL_TEXTURE_2D, texID1);
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
//        //location = 2
//        GLuint txc_loc = glGetAttribLocation(prog.GetID(), "txc");
//        glBindBuffer(GL_ARRAY_BUFFER, txc);
//        glEnableVertexAttribArray(txc_loc);
//        glVertexAttribPointer(txc_loc, 3, GL_FLOAT, GL_FALSE,
//                                  0, (void*) 0);
//
//
////        glActiveTexture(GL_TEXTURE0); //specifying texture unit number, here is the default
////        glBindTexture(GL_TEXTURE_2D, texID0);
////        prog["tex0"] = 0 ;
////        glActiveTexture(GL_TEXTURE1); //specifying texture unit number, here is the default
////        glBindTexture(GL_TEXTURE_2D, texID1);
////        prog["tex1"] = 1 ;
//
//
//        /* ******************************************************************************************************** */
//        /* Render plane */
//        prog.BuildFiles("shader1.vert", "shader1.frag");
//        prog.Bind();
//        glUseProgram(prog.GetID());
//
//        // Set frame buffer target to the back buffer
//        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );
//        glViewport( 0, 0, widthImg, heightImg );
//        glClearColor(0, 0, 0, 1);
//        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//        cy::Vec3f planeCentre(0.5,0.3,0.0);
//        cy::Matrix4f modelMatrixP = cy::Matrix4f::RotationXYZ(-texRotY * (M_PI/180.0), texRotX * (M_PI/180.0), 0);
//        cy::Matrix4f translationMatrixP = cy::Matrix4f::Translation(-planeCentre.XYZ());
//        cy::Matrix4f viewMatrixP = cy::Matrix4f::View(camera.XYZ(), trans.XYZ(), up.XYZ());
//        cy::Matrix4f projMatrixP = cy::Matrix4f::Perspective(20.0 * (M_PI/180.0), 1920.0/1080.0, 0.1f, 1000.0f);
//        cy::Matrix4f transMatrixP = projMatrixP * viewMatrixP * modelMatrixP * translationMatrixP;
//        float matrixP[16];
//        transMatrixP.Get(matrixP);
//        GLint mvp_posP = glGetUniformLocation(prog.GetID(), "mvp");
//        glUniformMatrix4fv(mvp_posP, 1, GL_FALSE, matrixP);
//        glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
//
//        glBindBuffer(GL_ARRAY_BUFFER, txc);
//        GLuint pos_locationP = glGetAttribLocation(prog.GetID(), "pos");
//        glEnableVertexAttribArray(pos_locationP);
//        glVertexAttribPointer(pos_locationP, 3, GL_FLOAT, GL_FALSE,
//                              0, (void*) 0);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, renderedTexture);
//        GLuint txc_locationP = glGetAttribLocation(prog.GetID(), "txc");
//        glEnableVertexAttribArray(txc_locationP);
//        glVertexAttribPointer(txc_locationP, 3, GL_FLOAT, GL_FALSE,
//                              0, (void*) 0);
//        GLint samplerP = glGetUniformLocation(prog.GetID(), "tex");
//        glUniform1i(samplerP, 0);
//        glViewport( 500, 300, widthImg, heightImg );
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//
////        glDrawElements(GL_TRIANGLES, sizeof(Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0);
////        glDisableVertexAttribArray(pos_loc);
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
