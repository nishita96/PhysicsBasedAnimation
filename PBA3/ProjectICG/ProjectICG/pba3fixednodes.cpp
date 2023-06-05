////
////  pba3.cpp
////  ProjectICG
////
////  Created by Nishita Kharche on 3/9/23.
////
//
//#include <stdio.h>
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
//#include <set>
//#include <array>
//#include <map>
//#include "Eigen/Sparse"
//#include "Eigen/IterativeLinearSolvers"
//#include <vector>
//#include "tetgen.h"
//
//using namespace std;
//using namespace cy;
//
//GLuint vao;
//GLuint vbo0;
//GLuint vbo1;
//GLuint ebuffer;
//GLuint vbo0A;
//GLuint vbo1A;
//GLuint ebufferA;
//GLuint txcA;
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
//double transObjX = 0.0f;
//double transObjY = 0.0f;
//double newTransObjX = 0.0f;
//double newTransObjY = 0.0f;
//double prevTransObjX = 0.0f;
//double prevTransObjY = 0.0f;
//
////double clickX = 0.0f;
////double clickY = 0.0f;
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
//// CAMERA viewing changes based on this
////Vec3f camera(0.0, 1.0, -40.0);//0.0,55.0,-0.1);//0,25,-1
////Vec3f camera(0.0,35.0,-40.0);
//Vec3f camera(10.0,10.0,-60.0);
//Vec3f trans(0.0,0.0,0.0);
//Vec3f up(0.0,1.0,0.0);
//
//Vec4f rayTip(0.0, 0.0, 0.0, 0.0);
//
//Vec3f boundMin(0.0,0.0,0.0);
//Vec3f boundMax(1.0,1.0,1.0);
//Vec3f centre(0.0,0.0,0.0);
//
//Vec3f planeShift(0.0,32.0,0.0);
//
//Vec4f lightDirection(0.0,35.0,-70.0, 0.0);//10.0, 50.0, -20.0, 0.0);
////Vec4f lightDirectionVec(0.0,35.0,-70.0, 0.0);// kept same as camera for good view
////Vec3f lightDirectionVec(0.0,1.0,40.0);// for armadillo and dragon
//Vec3f lightDirectionVec(10.0,20.0,40.0);
////Vec4f lightDirectionVec(0.0,35.0,70.0, 0.0);
//
//bool ctrlPressedExplicit = false; // concentric forces
//bool altPressedImplicit = false;
//bool objPressed = false;
//bool rotPressed = false;
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
//Vec4f cameraRot(0.0, 0.0, 0.0, 0.0);
//
////proj7
//GLuint depthMap;
//double shadWidth = 2280;
//double shadHeight = 2020;
//
//float sizePlane = 160.0f ;// was 60
//float limitPlane = 210.0;
//Vec3f spherePosition(0.0, 0.0, 0.0);
//Vec3f sphereVelocity(1.0, 0.0, 1.0);
//Vec3f sphereForce(2.0, 0.0, 1.0);
//Vec3f spherePositionInitial(0.0, 0.0, 0.0);
//Vec3f spherePositionFinal(0.0, 0.0, 0.0);
//bool clickFlag = false;
//bool clickFlagConcentricExplicit = false;
//bool clickFlagConcentricImplicit = false;
//bool startFlag = false;
//float dt = 1/50;
//float timeStep = 1;
//float timeStepConcentric = 0.05;
////float maxMagnitude = 2;
//
//Vec4f com(0.0, 0.0, 0.0, 0.0);
////Vec3f spherePos(-1,0.5,-1);//-50, 5.5, -150);
//Vec3f spherePos(-1,0.5,-10);
////float dragonScaling = 3.0;
////float dragonScaling = 0.00005;//armadilloScaling = 0.00005;
//float dragonScaling = 0.1;//cube
////Vec3f objPosition(0.0, 0.0, 0.0); // CHANGE TODO HERE
//Vec3f objPosition(0.0, 100.0, 0.0);
//Vec3f objRotation(0.0, 0.0, 0.0);
//Vec3f objLinearV(0.0, 0.0, 0.0);
//Vec3f objAngularV(0.0, 0.0, 0.0);
//float objDt = 0.1;
//float limitBox = 20.0;
//double sphereObjX = 0.0f;
//double sphereObjY = 0.0f;
//
//Vec3f transBias(0.5,0.5,0.5 - 0.0000066);
//
//
//
//
//
//
//
//
////PBA3
//struct Face{
//    int v[3];
//};
//
//struct Tetrahedron {
//    int id;
//    int v[4];
//};
//
//struct Tetrahedron tetrahedrons[5]; //dragon - 32959, armadillo - 65496, cube 5, 1 tetra
//struct Face faces[12]; //11640 dragon - 5921, armadillo - 26922 // has all the surface faces only, cube 12, tetra 4
//
//Vec3f vertPosArr[8]; //dragon - 7759, armadillo - 17481, cube 8 // update at each iteration TODO remove translation matrix, tetra 4
//Vec3f normArr[8] = {Vec3f(0.0)}; //dragon - 5921, armadillo - 17482, cube 8, tetra 4
//
//static void createVertexBufferTet(Vec3f vertPosArr[], size_t vertPosArraySize, Vec3f normArr[], size_t normArraySize, struct Face face[], size_t faceArraySize){
//    
//    glGenBuffers(1, &vbo0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * vertPosArraySize, vertPosArr, GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &vbo1);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * vertPosArraySize, normArr, GL_STATIC_DRAW);
//    
//    glGenBuffers(1, &ebuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face[0]) * faceArraySize, face, GL_STATIC_DRAW);
//}
//
//void findNormalForFace(int v1idx, int v2idx, int v3idx, int v4idx){
//    Vec3f v1 = vertPosArr[v1idx];
//    Vec3f v2 = vertPosArr[v2idx];
//    Vec3f v3 = vertPosArr[v3idx];
//    Vec3f v4 = vertPosArr[v4idx];
//    
//    Vec3f norm = (v2-v1).Cross(v3-v1);
//    float dotProduct = norm.Dot(v4-v1);
//    if(dotProduct >= 0.0){
//        norm = -norm;
//    }
//    norm.Normalize();
//    normArr[v1idx] = norm;
//    normArr[v2idx] = norm;
//    normArr[v3idx] = norm;
//    //            cout<<"\n "<<norm.x<<" "<<norm.y<<" "<<norm.z<<endl;
//}
//
//size_t vertPosArrSize = 0;
//size_t faceArrSize = 0;
//size_t normArrSize = 0;
//
//Eigen::VectorXd x, b;
//Eigen::SparseMatrix<double> A;
//Eigen::SparseMatrix<double> M;
//Eigen::SparseMatrix<double> kJacobian;
//typedef Eigen::Triplet<double> Trip;
//vector<Eigen::Triplet<double>> putInJacobian;
//
//struct Particle {
//    int indexV;
//    float mass = 1.0;
//    Vec3f pos = Vec3f(0.0f, 0.0f, 0.0f);
//    Vec3f vel = Vec3f(0.0f, 0.0f, 0.0f);
//    Vec3f force = Vec3f(0.0f, 0.0f, 0.0f);
//    Matrix3f dF = Matrix3f(0.0, 0.0, 0.0,
//                           0.0, 0.0, 0.0,
//                           0.0, 0.0, 0.0);
//};
//struct Particle particles[8];// 8 cube, 4 tetra
//int particleSize = 8;//8 cube,  4 tetra
//
//struct Edge { // gonna populate from tetrahedrals
//    int idxP0;
//    int idxP1;
//    float restDist;
//    Vec3f springForce0 = Vec3f(0.0f, 0.0f, 0.0f);
//    Vec3f springForce1 = Vec3f(0.0f, 0.0f, 0.0f);
//    float kStiff = 10.0;//50.0;
//    Vec3f dampForce0 = Vec3f(0.0f, 0.0f, 0.0f);
//    Vec3f dampForce1 = Vec3f(0.0f, 0.0f, 0.0f);
//    float dampFactor = 5.0;//30.0;
//    bool inwards = false;
//};
//set<Edge> edgesSet;
//
//int edgeSetSize = 0;
//bool operator<(const Edge& e1, const Edge& e2) {
//    if (e1.idxP0 != e2.idxP0) {
//        return e1.idxP0 < e2.idxP0;
//    } else {
//        return e1.idxP1 < e2.idxP1;
//    }
//}
//struct Edge edges[18];//18 cube, 6 tetra
//Vec3f gravity = Vec3f(0.0f, -9.8, 0.0f);
//float dt3 = 0.01;// show at 0.0005
//float floorHeight = -50.0;
//
//void initiateParticlePos(){
//    int i=0;
//    for (auto v : vertPosArr){
//        particles[i].indexV = i;
//        particles[i].pos = v;
//        particles[i].force = gravity; // MAY NEED CHANGE
//        i++;
//    }
//}
//// legendary tenasity
//void calcEdgeForces(){
//    
//    putInJacobian.clear();
//    putInJacobian.reserve(9 * 4 * edgeSetSize);
//    for (int i=0; i<edgeSetSize; i++){
//        Edge e = edges[i];
//        int p0 = e.idxP0;
//        int p1 = e.idxP1;
//        Vec3f vert0 = particles[p0].pos;
//        Vec3f vert1 = particles[p1].pos;
//        
//        Vec3f diffX = vert1 - vert0;
//        float newDist = (vert1 - vert0).Length();
//        
//        if(newDist != 0.0){
//            edges[i].springForce0 = edges[i].kStiff * (newDist - edges[i].restDist) * (diffX) / newDist; // TODO might not be needed to store in edge sturct
//            edges[i].springForce1 = -edges[i].springForce0; // TODO directly use this and save memory for this var
////            cout << "\n vel diff " << particles[edges[i].idxP1].vel.x - particles[edges[i].idxP0].vel.x ;
//            float dot = (particles[edges[i].idxP1].vel - particles[edges[i].idxP0].vel).Dot((diffX) / newDist);
//            
//            edges[i].dampForce0 = edges[i].dampFactor * dot * (diffX) / newDist ;
//            edges[i].dampForce1 = -edges[i].dampForce0;
//            
////            cout << "\n spring" << i << " - "<< edges[i].springForce0.x << edges[i].springForce0.y << edges[i].springForce0.z;
////            cout << "\n   damp" << i << " - "<< edges[i].dampForce0.x << edges[i].dampForce0.y << edges[i].dampForce0.z;
//        
//            // update both vert forces
//            particles[edges[i].idxP0].force += edges[i].springForce0 + edges[i].dampForce0; // acc
//            particles[edges[i].idxP1].force += edges[i].springForce1 + edges[i].dampForce1;
//            
//            // big formulation
//
//            Matrix3f dx = Matrix3f(diffX.x, 0.0, 0.0,
//                                   diffX.y, 0.0, 0.0,
//                                   diffX.z, 0.0, 0.0);
//            Matrix3f dxdxt = dx * dx.GetTranspose();
//    //        cout << "\n Here ";
//    //        for(int i=0; i<3; i++){
//    //            for (int j=0; j<3; j++){
//    //                cout << "\n (" << i << "," << j << ") " << dxdxt(i,j);
//    //            }
//    //        }
//            Matrix3f stuff = Matrix3f::Identity() - (dxdxt / (newDist * newDist));
//            Matrix3f dFspring = edges[i].kStiff * ( -Matrix3f::Identity() + ((edges[i].restDist/newDist)*stuff) );
//            Matrix3f dt = dt3 * Matrix3f::Identity();
//            Matrix3f dFdamp = edges[i].dampFactor * (dxdxt/(newDist*newDist)) * dt;
//            Matrix3f dFtotal = dFspring + dFdamp;
//            
//            // update 3x3 force for both vert
//            particles[edges[i].idxP0].dF += dFtotal; // acc
//            particles[edges[i].idxP1].dF += (-1 * dFtotal);
//            
//            
//            for(int row=0; row<3; row++){
//                for(int col=0; col<3; col++){ // filling in column major order
//                    putInJacobian.push_back(Trip(p0 + col, p0 + row, dFtotal(row, col)));
//                    putInJacobian.push_back(Trip(p0 + col, p1 + row, -dFtotal(row, col)));
//                    putInJacobian.push_back(Trip(p1 + col, p0 + row, -dFtotal(row, col)));
//                    putInJacobian.push_back(Trip(p1 + col, p1 + row, dFtotal(row, col)));
//                }
//            }
//            
//            // may need to add gravity here
//        }
//
//    }
//    
//    // populate jacobian
//    kJacobian.resize(3*vertPosArrSize, 3*vertPosArrSize);
//    kJacobian.setFromTriplets(putInJacobian.begin(), putInJacobian.end());
////    cout << "\n kJacobian values:" ;
////    for (int i = 0; i < kJacobian.outerSize(); ++i) {
////        for (Eigen::SparseMatrix<double>::InnerIterator it(kJacobian, i); it; ++it) {
////            cout << "\n (" << it.row() << ", " << it.col() << "): " << it.value();
////        }
////    }
//
//    M.resize(3*vertPosArrSize, 3*vertPosArrSize);
//    M.setIdentity();
////    cout << "\n M values:" ;
////    for (int i = 0; i < M.outerSize(); ++i) {
////        for (Eigen::SparseMatrix<double>::InnerIterator it(M, i); it; ++it) {
////            cout << "\n (" << it.row() << ", " << it.col() << "): " << it.value();
////        }
////    }
//    
//    A.resize(3*vertPosArrSize, 3*vertPosArrSize);
//    A = M - dt3 * dt3 * kJacobian;
//    // A is 3nx3n
////    cout << "\n A values:" ;
////    for (int i = 0; i < A.outerSize(); ++i) {
////        for (Eigen::SparseMatrix<double>::InnerIterator it(A, i); it; ++it) {
////            cout << "\n (" << it.row() << ", " << it.col() << "): " << it.value();
////        }
////    }
//    
//    // b is column vector 3nx1
//    b.resize(3*vertPosArrSize);
//    for(int i=0; i<vertPosArrSize; i++){
//        Particle p = particles[i];
//        b(i*3) = p.vel.x + dt3 * p.force.x;
//        b(i*3+1) = p.vel.y + dt3 * p.force.y;
//        b(i*3+2) = p.vel.z + dt3 * p.force.z;
////        cout << "\n b " << b(i*3 ) << b(i*3 + 1) << b(i*3 + 2);
//    }
//    
//    
//    
//    x.resize(3*vertPosArrSize);
//    Eigen::ConjugateGradient<Eigen::SparseMatrix<double>, Eigen::Lower|Eigen::Upper> cg(A);
//    cg.setMaxIterations(10); //CHANGE from 50
//    x = cg.solve(b);     // x (v t+1) is 3nx1 vector
//    float err = cg.error();
//     while (err > 0.05) {
//         b = x;
//         x = cg.solve(b);
//         err = cg.error();
//     }
//    
////    for(int i=0; i<vertPosArrSize; i++){
////        cout << "\n x : " << x(3*i) << " " << x(3*i+1) << " " << x(3*i+2) ;
////    }
//    
//    // update vel of all particles
//    for(int i=0; i<vertPosArrSize; i++){
//        particles[i].vel = Vec3f(x(3*i), x(3*i+1), x(3*i+2));
//    }
//    
//    
//}
//
//void bounceFromFloor(int idx){
//    if (particles[idx].pos.y < floorHeight){
//        vertPosArr[idx][1] = floorHeight; // TODO check if this is needed
//        particles[idx].pos.y = floorHeight;
//        particles[idx].vel = -0.9*particles[idx].vel;
//    }
//}
//
//void calcForcePerVert(){
//    
//    // calc other details of vert
//    particles[vertPosArrSize-1].vel = Vec3f(0.0, 0.0, 0.0);
//    particles[vertPosArrSize-1].force = Vec3f(0.0, 0.0, 0.0);
//    
//    for (int i=0; i<vertPosArrSize-1; i++){
//        particles[i].force = gravity;
//        particles[i].pos = particles[i].pos + dt3*particles[i].vel;
//        // update arr to render
//        vertPosArr[particles[i].indexV] = particles[i].pos;
//        
//    }
//
//}
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
//
//static Vec4f findCenterOfMass(TriMesh *mesh){ // assuming point mass 1
//    Vec4f retCom = Vec4f(0.0, 0.0, 0.0, 0.0);// CHECK THE LAST ELEMENT
//    int faceIdx=0;
//    for (faceIdx=0; faceIdx < mesh->NF(); faceIdx++ ){ //go through all faces
//        TriMesh::TriFace currentFace = mesh->F(faceIdx);
//        
//        Vec3f v0 = mesh->V(currentFace.v[0]);
//        Vec3f v1 = mesh->V(currentFace.v[1]);
//        Vec3f v2 = mesh->V(currentFace.v[2]);
//        Vec3f center = (v0 + v1 + v2) /3.0f;
//        // adding all x values, y values, z values
//        retCom.x += center.x; // /3 coz 3 vertices and need center of face to be added
//        retCom.y += center.y;
//        retCom.z += center.z;
//    }
//    return retCom/faceIdx;
//}
//
//bool rayWithEachFace(Vec3f rayOrigin, Vec3f rayDirection, TriMesh::TriFace face, TriMesh mesh, float& t, float& u, float& v){
//    const float EPSILON = 0.000001f;
//    Vec3f v0 = mesh.V(face.v[0]);
//    Vec3f v1 = mesh.V(face.v[1]);
//    Vec3f v2 = mesh.V(face.v[2]);
//    v0 = v0*dragonScaling;
//    v1 = v1*dragonScaling;
//    v2 = v2*dragonScaling; // CHECK scaling here
//    
//    Vec3f edge1 = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
//    Vec3f edge2 = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
//    Vec3f h = {rayDirection.y * edge2.z - rayDirection.z * edge2.y,
//                rayDirection.z * edge2.x - rayDirection.x * edge2.z,
//                rayDirection.x * edge2.y - rayDirection.y * edge2.x};
//    
//    
//    float a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;
//    if (a > -EPSILON && a < EPSILON) { // floating point error
//        return false;
//    }
//    float f = 1.0f / a;
//    Vec3f s = {rayOrigin.x - v0.x, rayOrigin.y - v0.y, rayOrigin.z - v0.z};
//    u = f * (s.x * h.x + s.y * h.y + s.z * h.z);
//    if (u < 0.0f || u > 1.0f) {
//        return false;
//    }
//
//    Vec3f q = {s.y * edge1.z - s.z * edge1.y,
//                s.z * edge1.x - s.x * edge1.z,
//                s.x * edge1.y - s.y * edge1.x};
//    v = f * (rayDirection.x * q.x + rayDirection.y * q.y + rayDirection.z * q.z);
//    if (v < 0.0f || u + v > 1.0f) {
//        return false;
//    }
//
//    t = f * (edge2.x * q.x + edge2.y * q.y + edge2.z * q.z);
//    
//    return true;
//}
//
//bool rayIntersectingFace(Vec3f rayOrigin1, Vec3f rayDirection1, TriMesh mesh, Vec3f& intersectP){
//    float t1[2] = {0.0f, 0.0f};
//    int idx = 0;
//    bool found = false;
//    for (int faceIdx=0; faceIdx < mesh.NF(); faceIdx++ ){ //go through all faces
//        TriMesh::TriFace currentFace = mesh.F(faceIdx);
//        float u = 0.0f;
//        float v = 0.0f;
//        if(rayWithEachFace(rayOrigin1, rayDirection1, currentFace, mesh, t1[idx], u, v)){
//            idx++;
//            found = true;
//        }
//        
//    }
//    float t = 0.0f;
//    if(t1[0] < t1[1]){
//        t = t1[0];
//    }
//    else{
//        t = t1[1];
//    }
//    intersectP = {rayOrigin1.x + t * rayDirection1.x,
//                                    rayOrigin1.y + t * rayDirection1.y,
//                                    rayOrigin1.z + t * rayDirection1.z};
//    return found;
//}
//
//void checkReboundBox(Vec3f& objPosition, Vec3f& objRotation, Vec3f& objLinearV, Vec3f& objAngularV, TriMesh mesh){
//
//    
//    Vec3f norm(0.0, 0.0, 0.0);
//    if(objPosition.x >= limitBox){
//        norm.x = -1.0;
//    }
//    else if(objPosition.x <= -limitBox){
//        norm.x = 1.0;
//    }
//    else if(objPosition.y >= limitBox){
//        norm.y = -1.0;
//    }
//    else if(objPosition.y <= -limitBox){
//        norm.y = 1.0;
//    }
//    else if(objPosition.z >= limitBox){
//        norm.z = -1.0;
//    }
//    else if(objPosition.z <= -limitBox){
//        norm.z = 1.0;
//    }
//    float crossToFindDirection = norm.Dot(objLinearV);
//    if(crossToFindDirection < 0){
////        fprintf(stdout, "\n --going towards ");
//        objLinearV.x = (norm.x==0? 1 : -1) * objLinearV.x;
//        objLinearV.y = (norm.y==0? 1 : -1) * objLinearV.y;
//        objLinearV.z = (norm.z==0? 1 : -1) * objLinearV.z;
////        objAngularV.z = -1 * objAngularV.z;
//        objAngularV.x = (norm.x==0? 1 : -1) * objAngularV.x;
//        objAngularV.y = (norm.y==0? 1 : -1) * objAngularV.y;
//        objAngularV.z = (norm.z==0? 1 : -1) * objAngularV.z;
//
//    }
////    else{
////        fprintf(stdout, "\n --going away ");
////    }
//    
//
//    
//
//}
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
//static void createVertexBufferArrow(TriMesh *mesh){
//
//    //all vertices are vec3f
//    cy::Vec3f vPos[mesh->NV() * 7]; //need space to add more, hence *7
//    cy::Vec3f vNorm[mesh->NVN() * 7];
//    cy::Vec3f vTex[mesh->NV() * 7];
//    //face list
//    cy::TriMesh::TriFace face[mesh->NF()];
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
//    glGenBuffers(1, &vbo0A);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo0A);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*vCnt, vPos, GL_STATIC_DRAW);
//
//    glGenBuffers(1, &vbo1A);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo1A);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*vCnt, vNorm, GL_STATIC_DRAW);
//
//    //faces with texture
//    glGenBuffers(1, &ebufferA);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebufferA);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face[0])*mesh->NF(), face, GL_STATIC_DRAW);
//
//    //for texel
//    glGenBuffers(1, &txcA);
//    glBindBuffer(GL_ARRAY_BUFFER, txcA);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NVT(), &mesh->VT(0), GL_STATIC_DRAW);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f)*mesh->NF(), &mesh->FT(0), GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cy::Vec3f)*vCnt, vTex, GL_STATIC_DRAW);
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
//static void buildProgram( GLSLProgram prog){
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
//        ctrlPressedExplicit = true;
//    }
//    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE){
//        ctrlPressedExplicit = false;
//    }
//    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS){
//        altPressedImplicit = true;
//    }
//    if (key == GLFW_KEY_LEFT_ALT && action == GLFW_RELEASE){
//        altPressedImplicit = false;
//    }
//    if (key == GLFW_KEY_O && action == GLFW_PRESS){ //for object moving
//        objPressed = true;
//        fprintf(stdout, " O clicked \n");
//    }
//    if (key == GLFW_KEY_O && action == GLFW_RELEASE){
//        objPressed = false;
//    }
//    if (key == GLFW_KEY_R && action == GLFW_PRESS){ //for object moving
//        rotPressed = true;
//        fprintf(stdout, " R clicked \n");
//    }
//    if (key == GLFW_KEY_R && action == GLFW_RELEASE){
//        rotPressed = false;
//    }
//
//}
//
//static void getMouseCoordinates(GLFWwindow* window){
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        if (ctrlPressedExplicit){
//            if(!clickFlagConcentricExplicit){// if false
//                //it is first click
//                spherePosition = Vec3f(1.0, 0.0, 1.0);
//                sphereVelocity = Vec3f(1.0, 0.0, 1.0);
//                clickFlagConcentricExplicit = true;
//            }
//            
////            glfwGetCursorPos(window, &newRotLightX, &newRotLightY);
////            rotLightX = rotLightX + newRotLightX - prevRotPlaneX;
////            rotLightY = rotLightY + newRotLightY - prevRotPlaneY;
////            prevRotPlaneX = newRotLightX;
////            prevRotPlaneY = newRotLightY;
//            
//        }
//        if(altPressedImplicit){
//            if(!clickFlagConcentricImplicit){// if false
//                //it is first click
//                spherePosition = Vec3f(70.0, 0.0, 70.0);
//                sphereVelocity = Vec3f(1.0, 0.0, 1.0);
//                clickFlagConcentricImplicit = true;
//                
//            }
//        }
//        if(rotPressed ){// rotate OR translate
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
//            rotObjX = rotObjX + newRotObjX - prevRotObjX;// using for both obj rotation and translation
//            rotObjY = rotObjY + newRotObjY - prevRotObjY;
//            prevRotObjX = newRotObjX;
//            prevRotObjY = newRotObjY;
//        }
//        if(objPressed){
//            glfwGetCursorPos(window, &newTransObjX, &newTransObjY);
//            transObjX = transObjX + newTransObjX - prevTransObjX;
//            transObjY = transObjY + newTransObjY - prevTransObjY;
//            prevTransObjX = newTransObjX;
//            prevTransObjY = newTransObjY;
//            if(!clickFlag){// if false
//                //it is first click
//                clickFlag = true;
////                startFlag = false;
//            }
//        }
//        else{
//            glfwGetCursorPos(window, &newRotObjX, &newRotObjY);
////            if(!clickFlag){// if false
//                //it is first click
////                sphereVelocity = Vec3f(0.0, 0.0, 0.0);
////                spherePositionInitial = Vec3f(newRotObjX, 0.0, newRotObjY);
////                clickFlag = true;
////                startFlag = true;
////            }
////            rotObjX = rotObjX + newRotObjX - prevRotObjX;// using for both obj rotation and translation
////            rotObjY = rotObjY + newRotObjY - prevRotObjY;
////            prevRotObjX = newRotoObjX;
////            prevRotObjY = newRotObjY;
//            
//            
//            
////            clickX = newRotObjX;
////            clickY = newRotObjY;
//        }
//        
//        
//    }
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){
//        
//        glfwGetCursorPos(window, &newRotPlaneX, &newRotPlaneY);
//        if(clickFlag){
////            if(clickFlag){// check - first one weird
////                startFlag = true;
////            }
//            spherePositionFinal = Vec3f(newRotObjX, 0.0, newRotObjY);
//            clickFlag = false;
//            startFlag = true;
//            sphereVelocity = spherePositionFinal - spherePositionInitial;
//            sphereVelocity = sphereVelocity / 50;
//            
//        }
//        prevRotPlaneX = newRotPlaneX;
//        prevRotPlaneY = newRotPlaneY;
//        
//        if(rotPressed ){
//            prevRotObjX = newRotPlaneX;
//            prevRotObjY = newRotPlaneY;
//        }
//        
//        if(objPressed){
//            if(clickFlag){
//                startFlag = true;
//                clickFlag = false;
//            }
//            prevTransObjX = newRotPlaneX;
//            prevTransObjY = newRotPlaneY;
//            sphereObjX = transObjX;
//            sphereObjY = transObjY;
//        }
//        
////        prevRotObjX = newRotPlaneX;
////        prevRotObjY = newRotPlaneY;
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
///**
//     * Computes the color gradiant
//     * color: the output vector
//     * x: the gradiant (beetween 0 and 360)
//     * min and max: variation of the RGB channels (Move3D 0 -> 1)
//     */
//    void GroundColorMix(float color[], float x, float min, float max)
//{
//   /*
//    * Red = 0
//    * Green = 1
//    * Blue = 2
//    */
//    double posSlope = (max-min)/60;
//    double negSlope = (min-max)/60;
//
//    if( x < 60 )
//    {
//        color[0] = max;
//        color[1] = posSlope*x+min;
//        color[2] = min;
//        return;
//    }
//    else if ( x < 120 )
//    {
//        color[0] = negSlope*x+2*max+min;
//        color[1] = max;
//        color[2] = min;
//        return;
//    }
//    else if ( x < 180  )
//    {
//        color[0] = min;
//        color[1] = max;
//        color[2] = posSlope*x-2*max+min;
//        return;
//    }
//    else if ( x < 240  )
//    {
//        color[0] = min;
//        color[1] = negSlope*x+4*max+min;
//        color[2] = max;
//        return;
//    }
//    else if ( x < 300  )
//    {
//        color[0] = posSlope*x-4*max+min;
//        color[1] = min;
//        color[2] = max;
//        return;
//    }
//    else
//    {
//        color[0] = max;
//        color[1] = min;
//        color[2] = negSlope*x+6*max;
//        return;
//    }
//}
//
//int main( int argc, char* args[] )
//{
//    
//    
//    // CHANGE
//    string arg6(args[6]);
//    string objectFileRoot(args[6]);
//    //.node - list of vertices
//    ifstream nodeFile((objectFileRoot + "cube.node").c_str());
//    if (nodeFile.is_open()) {
//      string line;
//        int num_vertices, dimension, num_attributes, num_boundary_markers;
//      getline(nodeFile, line);
//      sscanf(line.c_str(), "%d %d %d %*d", &num_vertices, &dimension, &num_attributes, &num_boundary_markers);
//      for (int i = 0; i < num_vertices; i++) {
//        getline(nodeFile, line);
//        Vec3f vertex;
//        sscanf(line.c_str(), "%*d %f %f %f", &vertex.x, &vertex.y, &vertex.z);
//        vertPosArr[i] = vertex;
//      }
//        nodeFile.close();
//    }
//    else {
//      cout << "Error: Failed to open node file" << endl;
//      return -1;
//    }
//    //.ele - list of tetrahedrons
//    ifstream eleFile((objectFileRoot + "cube.ele").c_str());
//    if (eleFile.is_open()) {
//      string line;
//      int num_elements, num_nodes_per_element, num_attributes;
//      getline(eleFile, line);
//      sscanf(line.c_str(), "%d %d %d", &num_elements, &num_nodes_per_element, &num_attributes);
//      for (int i = 0; i < num_elements; i++) {
//        getline(eleFile, line);
//        Tetrahedron tetrahedron;
//        tetrahedron.id = i;
//        sscanf(line.c_str(), "%*d %d %d %d %d", &tetrahedron.v[0], &tetrahedron.v[1], &tetrahedron.v[2], &tetrahedron.v[3]);
//        tetrahedrons[i] = tetrahedron;
//      }
//        eleFile.close();
//    }
//    else {
//      cout << "Error: Failed to open ele file" << endl;
//      return -1;
//    }
//    
////    for (int i = 0; i < sizeof(tetrahedrons)/sizeof(tetrahedrons[0]); i++) {
////        cout << "Tetrahedron " << i << ": [" << tetrahedrons[i].n[0] << ", " << tetrahedrons[i].n[1] << ", " << tetrahedrons[i].n[2] << ", " << tetrahedrons[i].n[3] << "]" << endl;
////      }
//
//    int index = 0;
//    map<array<int, 3>,set<int>> faceMap;
//    
//    // get all the faces from the tettrahedrons
//    for (Tetrahedron& t : tetrahedrons) {
//        array<int, 4> tV = {t.v[0], t.v[1], t.v[2], t.v[3]}; // sorting so that it can compare later
//        sort(tV.begin(), tV.end());
//        faceMap[{tV[0], tV[1], tV[2]}].insert(t.id);
//        faceMap[{tV[1], tV[2], tV[3]}].insert(t.id);
//        faceMap[{tV[0], tV[2], tV[3]}].insert(t.id);
//        faceMap[{tV[0], tV[1], tV[3]}].insert(t.id);
//    }
//    
//    // calculate normal for al the faces vertices
//    for (const auto& [key, value] : faceMap) {
//        if(value.size() == 1){  // surface faces
//            set<int>::iterator it=value.begin();
//            
//            faces[index].v[0] = key[0];
//            faces[index].v[1] = key[1];
//            faces[index].v[2] = key[2];
//            for (Tetrahedron& t : tetrahedrons) {
//                if(t.id == *it){
//                    for (int i=0; i<4; i++) {
//                        if(t.v[i] != key[0] && t.v[i] != key[1] && t.v[i] != key[2]){
//                            findNormalForFace(key[0], key[1], key[2], t.v[i]);
//                        }
//                    }
//                    continue;
//                }
//            }
//            index++;
//        }
//    }
////    cout << "\n surface faces " ;
////    for (auto f : faces){
////        cout << "\n " << f.v[0] << " " << f.v[1] << " " << f.v[2];
////    }
////    cout << "\n";
//    
//    // finding all edges
//    for (Tetrahedron& t : tetrahedrons){
//        for (int i=0; i<3; i++){
//            for (int j=i+1; j<4; j++){
//                cout << "\n " << t.v[i] << " " << t.v[j];
//                Edge singleEdge;
//                if(t.v[i] < t.v[j]){
//                    singleEdge.idxP0 = t.v[i];
//                    singleEdge.idxP1 = t.v[j];
//                }
//                else{
//                    singleEdge.idxP0 = t.v[j];
//                    singleEdge.idxP1 = t.v[i];
//                }
//                Vec3f edgeVec = vertPosArr[t.v[i]] - vertPosArr[t.v[j]];
//                singleEdge.restDist = edgeVec.Length();
//                edgesSet.insert(singleEdge);
//            }
//        }
//    }
//    edgeSetSize = edgesSet.size();
//    
////    cout << "\n edgesSet ";
////    for (auto e : edgesSet){
////        cout << "\n " << e.idxP0 << " " << e.idxP1 << " " << e.restDist ;
////    }
////    cout << "\n";
//    
//    // populate edges array
//    int i=0;
//    for (auto e : edgesSet){
//        edges[i].idxP0 = e.idxP0;
//        edges[i].idxP1 = e.idxP1;
//        edges[i].restDist = e.restDist;
//        i++;
//    }
//    
////    cout << "\n edges ";
////    for (auto e : edges){
////        cout << "\n " << e.idxP0 << " " << e.idxP1 << " " << e.restDist ;
////    }
////    cout << "\n";
//    
//    vertPosArrSize = sizeof(vertPosArr)/sizeof(vertPosArr[0]);
//    faceArrSize = sizeof(faces)/sizeof(faces[0]);
//    normArrSize = sizeof(normArr)/sizeof(normArr[0]);
//    
////    cout << "\n vertPosArrSize " << vertPosArrSize << "\n";
//    
//    // force(per EDGE) - spring forces + dampening forces
//    // force(per VERT) - gravity + all force(per EDGE)
//    // vel(per VERT) - based on force
//    // pos change(per VERT) - based on vel
//    
//    initiateParticlePos();
////    cout << "\n particles ";
////    for (auto e : particles){
////        cout << "\n " << e.indexV << " " << e.pos.x << " " << e.pos.y << " " << e.pos.z;
////    }
////    cout << "\n";
//    
//    calcEdgeForces();
//    
////    for (auto e : edgesSet){
////        cout << "\n " << e.indexV << " " << e.pos.x << " " << e.pos.y << " " << e.pos.z;
////    }
//    calcForcePerVert();
//    
////    cout << "\n particle forces";
////    for (auto e : particles){
////        cout << "\n " << e.force.x << " " << e.force.y << " " << e.force.z;
////    }
////    cout << "\n particle position";
////    for (auto e : particles){
////        cout << "\n " << e.pos.x << " " << e.pos.y << " " << e.pos.z;
////    }
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
//
//    
//
//    //create mesh
////    TriMesh mesh;
////    mesh.LoadFromFileObj(args[5]); //loading sphere 1, dragon 5, armadillo 4
////    mesh.ComputeBoundingBox();
////    mesh.ComputeNormals();
//
//    //create mesh - arrow
////    TriMesh meshArrow;
////    meshArrow.LoadFromFileObj(args[1]); //loading arrow 3
////    meshArrow.ComputeBoundingBox();
////    meshArrow.ComputeNormals();
////
////    if(argc > 1){
////        std::string arg1(args[1]);
//////        fprintf(stdout, "\n\n\n\n\n\n Argument: %s\n", arg1.c_str());
////        std::string arg2(args[2]);
//////        fprintf(stdout, " Argument 2: %s\n", arg2.c_str());
////        path = arg2;
////        std::string arg3(args[3]);
//////        fprintf(stdout, " Argument 3: %s\n", arg3.c_str());
////
////        //new objs
////        std::string arg4(args[4]);
//////        fprintf(stdout, " Argument 4: %s\n", arg4.c_str());
////        std::string arg5(args[5]);
//////        fprintf(stdout, " Argument 5: %s\n", arg5.c_str());
////    }
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
//
//    createVertexArray();
//    createVertexBufferTet(vertPosArr, vertPosArrSize, normArr, normArrSize, faces, faceArrSize);
//
//    // CENTER OF MASS
////    com = findCenterOfMass(&mesh);
////    com = com*dragonScaling; // CHANGE ACC TO OBJ
////    fprintf(stdout, "\n COM %f, %f, %f ", com.x, com.y, com.z);
//
//    // BEHAVIOUR INITIALIZAIONS
////    objPosition = -com.XYZ(); // CHECK TODO
//
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
//        glClearColor(0.1,0.1,0.1, 1);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//
//        getMouseCoordinates(window);
//
//
//
//        //rotate object
////        Matrix4f rotMatrix;
////        rotMatrix = Matrix4f::RotationXYZ(-rotObjY * (M_PI/180.0), -rotObjX * (M_PI/180.0), 0);
//
//
//        //rotate light - useless ?
//
//        Matrix4f rotLightMatrix;
//        Matrix4f rotLightMatX;
//        Matrix4f rotLightMatY;
//        rotLightMatX = Matrix4f::RotationX(0.0 * (M_PI/180.0)); //returns value for that angle rotation (not particular to the point, creating the rotation matrix)
//        rotLightMatY = Matrix4f::RotationZ(0.0 * (M_PI/180.0));
//        rotLightMatrix = rotLightMatX * rotLightMatY;
//
//
//        
//        // PBA3
//        calcEdgeForces();
////        for(int i=0; i<edgeSetSize; i++){
////            cout << "\n 0:" << edges[i].springForce0.x << " " << edges[i].springForce0.y << " " << edges[i].springForce0.x;
////            cout << "\n 1:" << edges[i].springForce1.x << " " << edges[i].springForce1.y << " " << edges[i].springForce1.x;
////        }
//        calcForcePerVert();
////        cout << "\n particle position";
////        for (auto e : vertPosArr){
////            cout << "\n " << e[0] << " " << e[1] << " " << e[2];
////        }
//        
////        // VELOCITY
////        //----------------------------For Concentric Explicit Force--------------------------------------
//////        if(ctrlPressedExplicit){
////        float timeS = 0.0;
////        double theta = 0.0;
////        Vec3f colourArrow = Vec3f(0.0, 0.0, 0.0);
////        float colour[3] = {0.0, 0.0, 0.0};
////        float magnitude = 0.0;
////        if(clickFlagConcentricExplicit){
////            // tangential acc direction at point (x,y) is (-y,x)
////            sphereForce = Vec3f(spherePosition.z, 0.0, (-1*spherePosition.x));
////            magnitude = sqrt(pow(sphereForce.x, 2) + pow(sphereForce.z, 2));
////            GroundColorMix(colour, magnitude, 0.0, 1.0);
////            // red - big force
////            // blue - small force
////            colourArrow.x = colour[2] + colour[1]/2;
////            colourArrow.z = colour[0] + colour[1]/2;
////            sphereForce = sphereForce * timeStepConcentric;
////            sphereVelocity = sphereVelocity + sphereForce * timeStepConcentric;
////            timeS = timeStepConcentric;
////            theta = atan2(-sphereForce.z, sphereForce.x); //CHECK
////        }
////        //----------------------------For Concentric Implicit Force--------------------------------------
////        if(clickFlagConcentricImplicit){
////            // tangential acc direction at point (x,y) is (-y,x)
////            timeStep = 0.005;
////            Vec4f rhsVec = Vec4f(spherePosition + sphereVelocity * 0.1, 0.0);
////            Matrix4f cMatrix;
////            cMatrix.SetRow(0, 1.0, timeStep*timeStep, 0.0, 0.0);
////            cMatrix.SetRow(1, -timeStep*timeStep, 1.0, 0.0, 0.0);
////            cMatrix.SetRow(2, 0.0, 0.0, 1.0, 0.0);
////            cMatrix.SetRow(3, 0.0, 0.0, 0.0, 1.0);
////            Matrix4f cMatrixInverse = cMatrix.GetInverse();
////            Vec4f rhs = cMatrixInverse * rhsVec;
////            spherePosition = rhs.XYZ();
////
////            //reset velocity
//////            sphereVelocity = sphereVelocity + Vec3f(-spherePosition.z, 0.0, spherePosition.x) * timeStep;
//////            sphereForce = Vec3f(-spherePosition.z, 0.0, spherePosition.x) * timeStep;
//////            magnitude = sqrt(pow(sphereVelocity.x, 2) + pow(sphereVelocity.z, 2));
//////            GroundColorMix(colour, magnitude, 0.0, 1.0);
//////            // red - big force
//////            // blue - small force
//////            colourArrow.x = colour[2] + colour[1]/2;
//////            colourArrow.z = colour[0] + colour[1]/2;
//////            theta = atan2(-sphereForce.z, sphereForce.x); //CHECK
////        }
////        //-----------------------------------------------------------------------------------------------
////        else{
////            timeS = timeStep;
////            theta = atan2(-sphereVelocity.z, sphereVelocity.x);
////            magnitude = sqrt(pow(sphereVelocity.x, 2) + pow(sphereVelocity.z, 2));
////            GroundColorMix(colour, magnitude*5.0, 0.0, 1.0);
////            // red - big force
////            // blue - small force
////            colourArrow.x = colour[2] + colour[1]/2;
////            colourArrow.z = colour[0] + colour[1]/2;
////        }
////
////
////        // REBOUND IN A CUBE OR SIZE 10
////        checkReboundBox(objPosition, objRotation, objLinearV, objAngularV, mesh);
////
////
////        // RAY INTERSECTS WITH FACE TO CALCULATE ALL MOVEMENTS
////        Vec3f spherePosDisplay = spherePos + Vec3f(-transObjX/50, -transObjY/50, 0.0f);
////        Vec3f newSpherePos = spherePos + Vec3f(-sphereObjX/50, -sphereObjY/50, 0.0f);
////        Vec3f rayOrigin = camera;
////        Vec3f rayDirection = newSpherePos - camera;
////        rayDirection.Normalize();
////        Vec3f intersectionPoint(0.0, 0.0, 0.0);
////        bool intersectFlag = rayIntersectingFace(rayOrigin, rayDirection, mesh, intersectionPoint);
////        if(intersectFlag && startFlag && clickFlag){
//////            fprintf(stdout, "\n Intersects");
////            //Intersection point %f, %f , %f ", intersectionPoint.x, intersectionPoint.y, intersectionPoint.z);
////            float forceMagnitude = 4;
////            objLinearV = rayDirection * forceMagnitude;
////    //        fprintf(stdout, "\n Force, objLinearV %f, %f, %f ", objLinearV.x, objLinearV.y, objLinearV.z);
////            Vec3f r = intersectionPoint - com.XYZ();
////            Vec3f F = rayDirection * forceMagnitude;
////            objAngularV = r.Cross(F);
////        }
////        else{
//////            fprintf(stdout, "\n Intersection not found");
////        }
////
////
////        // UPDATE TRANSLATION AND ROTATION
////        if(startFlag){
////            objPosition = objPosition + objDt*objLinearV;
////            objRotation = objRotation + objDt*objAngularV;
////        }
//
//        Matrix4f rotMatrix = Matrix4f::Identity() ;
//        Matrix4f translationMatrix = Matrix4f::Identity() ;
////        translationMatrix = Matrix4f::Translation(objPosition);// CHANGE , NEEDS FIX, THIS WORKS
//        rotMatrix = Matrix4f::RotationXYZ(objRotation.x * (M_PI/180.0), objRotation.y * (M_PI/180.0), objRotation.z * (M_PI/180.0));
//        Matrix4f scaleMatrix = Matrix4f::Scale(dragonScaling);// CHANGE, 0.00005 for armadillo, 3.0 for dragon
//        Matrix4f modelMatrix = scaleMatrix;//translationMatrix * rotMatrix * scaleMatrix; //rotMatrix * scaleMatrix * translationMatrix;// transalte rotate scaling
//
////        cameraRot = rotMatrix * Vec4f(camera,1);//rotating the camera
//        cameraRot = Vec4f(camera,1);//rotating the camera, position
//
//
//        //for OBJECT        env
//        Matrix4f viewMatrix = Matrix4f::View(cameraRot.XYZ(), trans.XYZ(), up.XYZ());//camera, movees the angle with the obj also
//        Matrix4f projMatrix = Matrix4f::Perspective(40.0 * (M_PI/180.0), width/height, 0.1f, 1000.0f);
//        Matrix4f transMatrix = projMatrix * viewMatrix * modelMatrix;// written op in code as compared to understand
//        Matrix4f mvMatrixO = viewMatrix * modelMatrix;// changed from modelMatrix
//        Matrix3f normalMatrixO = mvMatrixO.GetSubMatrix3().GetInverse().GetTranspose();
//
//
//
//        // GET stuff from screen
////        float ndcX = 2* (clickX - width/2) / width;
////        float ndcY = 2* (-clickY - height/2) / height;
////        float ndcZ = -1.0;
////        float ndcW = 1.0;
////        ndcX *= 0.1f;
////        ndcY *= 0.1f;
////        ndcZ = (-0.1f * (1000.0f + 0.1f) + 2 * 1000.0f * 0.1f) / (0.1f-1000.0f);
////        ndcW *= 0.1f;
////        Vec4f screenCoord = Vec4f(ndcX, ndcY, ndcZ, ndcW);
////        Vec4f rayTip = viewMatrix.GetInverse() * projMatrix.GetInverse() * screenCoord ;
////        rayTip = rayTip/rayTip.w;
////        fprintf(stdout, "\n RayTip %f, %f, %f, %f", rayTip.x, rayTip.y, rayTip.z, rayTip.w);
//
//
//
////        // FOR ARROW/ NOW SPHERE
////        Matrix4f rotMatrixYA = Matrix4f::Identity();
//////        rotMatrixYA = Matrix4f::RotationY(theta);// CHECK
//////        Matrix4f translationMatrixA = Matrix4f::Translation(spherePos + Vec3f(-transObjX/50, -transObjY/50, 0.0f));
////        Matrix4f translationMatrixA = Matrix4f::Translation(spherePosDisplay);
//////        Matrix4f translationMatrixA = Matrix4f::Translation(Vec3f( rayTip.x, rayTip.y, rayTip.z));//Vec3f(-1,0.5,-1));//0.0, 5.0, 0.0 ));//clickX/10, 0.5, clickY/10));//Vec3f( rayTip.x, rayTip.y, rayTip.z));
//////        translationMatrixA = Matrix4f::Translation(Vec3f(-transObjX/50, -transObjY/50, 0.0f));
////        Matrix4f scaleMatrixA = Matrix4f::Scale(0.015);// 0.05 for arrow
////        Matrix4f modelMatrixA = translationMatrixA * rotMatrixYA * scaleMatrixA ;//rotMatrixYA * scaleMatrixA * translationMatrixA;
////        Matrix4f transMatrixA = projMatrix * viewMatrix * modelMatrixA;
//
//
//
//
//        // FOR PLANE
////        Matrix4f translationMatrixP = Matrix4f::Translation(-planeShift.XYZ());
//////        Vec3f planeTrans(rotObjY, rotObjY, 0.0);
//////        Matrix4f translationMatrixP = Matrix4f::Translation(Vec3f(rotObjX, rotObjY, 0.0));
////        Matrix4f scaleMatrixP = Matrix4f::Scale(0.08);
////        Matrix4f modelMatrixP = scaleMatrixP * translationMatrixP;
////        Matrix4f transMatrixP = projMatrix * viewMatrix * modelMatrixP;
//
//
//
//        //for lighting take from view only
////        Matrix4f mvMatrix = viewMatrix * modelMatrixP;// changed from modelMatrix
////        Matrix3f normalMatrix = mvMatrix.GetSubMatrix3().GetInverse().GetTranspose();
////
////        //direction of light
////        Vec4f rotLightDirection = viewMatrix * rotLightMatrix * lightDirection;//used for light Light Direction
////
//////        Vec4f rotLightDirectionL =  rotLightMatrix * lightDirection;
////        Vec4f rotLightDirectionL =  rotMatrix * lightDirection;
////        Matrix4f lightMatrix = Matrix4f::View(rotLightDirectionL.XYZ() , trans.XYZ(), up.XYZ());
////
////        Matrix4f matrixMLP = projMatrix * lightMatrix ;
////        Matrix4f matrixShadow = Matrix4f::Translation(transBias) * Matrix4f::Scale(1.0) * matrixMLP;
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
////        shadowMap.Bind();
////
////        glClear( GL_DEPTH_BUFFER_BIT );
////        glUseProgram( shadowProgram.GetID());
////
////        matrixMLP.Get(matrixMlp);
////        GLint samplerMLP = glGetUniformLocation(shadowProgram.GetID(), "mvp");//can directly use in next line
////        glUniformMatrix4fv( samplerMLP, 1, GL_FALSE, matrixMlp );//can do outside loop
////
////        glBindBuffer(GL_ARRAY_BUFFER, vbo0);
////        GLuint pos_location4 = glGetAttribLocation(shadowProgram.GetID(), "pos");
////        glEnableVertexAttribArray(pos_location4);
////        glVertexAttribPointer(pos_location4, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
////
////        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
//////        glDrawElements(GL_TRIANGLES, sizeof(cy::Vec3f)*mesh.NF(), GL_UNSIGNED_INT, 0); //the shadow
////        shadowMap.Unbind();
////
////        glViewport( 0, 0, width, height );
////        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
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
//        //SPHERE rendering everything // NOW DRAGON AND ARMADILLO
//        float matrixMvp[16];
//        float matrixMv[16];
//        float matrixNorm[9];
//        float matrixShad[16];
//
////        matrixShadow.Get(matrixShad);
////        GLint shadow_pos = glGetUniformLocation( progTeapot.GetID(), "matrixShadow" );
////        glUniformMatrix4fv(shadow_pos, 1, GL_FALSE, matrixShad );
//
//        transMatrix.Get(matrixMvp);
//        GLint mvp_pos = glGetUniformLocation(progTeapot.GetID(), "mvp");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
//
//        mvMatrixO.Get(matrixMv);
//        GLint mv_pos = glGetUniformLocation(progTeapot.GetID(), "mv");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix4fv(mv_pos, 1, GL_FALSE, matrixMv);
//
//        normalMatrixO.Get(matrixNorm);
//        GLint normal_pos = glGetUniformLocation(progTeapot.GetID(), "normalMatrix");
//        glUseProgram(progTeapot.GetID());
//        glUniformMatrix3fv(normal_pos, 1, GL_FALSE, matrixNorm);
//
//        GLint lightDirection = glGetUniformLocation(progTeapot.GetID(), "lightDirection");
//        glUseProgram(progTeapot.GetID());
//        glUniform3f(lightDirection, lightDirectionVec.x, lightDirectionVec.y, lightDirectionVec.z);// 0.0,35.0,-70.0);//50.0,50.0,50.0);
//
//        GLint shine = glGetUniformLocation(progTeapot.GetID(), "shine");
//        glUseProgram(progTeapot.GetID());
//        glUniform1f(shine, 1100.0);
//
//        GLint itemColourVec3 = glGetUniformLocation(progTeapot.GetID(), "itemColour");
//        glUseProgram(progTeapot.GetID());
//        glUniform3f(itemColourVec3, 0.2, 0.3, 0.7);
//
//        //location = 0
//        glBindBuffer(GL_ARRAY_BUFFER, vbo0);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * vertPosArrSize, vertPosArr, GL_STATIC_DRAW);
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
//        glDrawElements(GL_TRIANGLES, sizeof(faces[0]) * faceArrSize, GL_UNSIGNED_INT, 0); // CHANGE THIS
////        glDrawArrays(GL_POINTS, 0, vertPosArraySize);
//
//
//
//
//
//
////        //ARROW rendering everything // NOW SPHERE
////        transMatrixA.Get(matrixMvp);
////        mvp_pos = glGetUniformLocation(progTeapot.GetID(), "mvp");
////        glUseProgram(progTeapot.GetID());
////        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
////        glUniform3f(itemColourVec3, colourArrow.x, colourArrow.y, colourArrow.z);
////
////        GLuint pos_loc_arrow = glGetAttribLocation(progTeapot.GetID(), "pos");
////        glUseProgram(progTeapot.GetID());
////        glBindBuffer(GL_ARRAY_BUFFER, vbo0A);
////        glEnableVertexAttribArray(pos_loc_arrow);
////        glVertexAttribPointer(pos_loc_arrow, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
////
////        GLuint normal_loc_arrow = glGetAttribLocation(progTeapot.GetID(), "normal");
////        glUseProgram(progTeapot.GetID());
////        glBindBuffer(GL_ARRAY_BUFFER, vbo1A);
////        glEnableVertexAttribArray(normal_loc_arrow);
////        glVertexAttribPointer(normal_loc_arrow, 3, GL_FLOAT, GL_FALSE,
////                                  0, (void*) 0);
////
////        GLint itemColourVec4 = glGetUniformLocation(progTeapot.GetID(), "itemColour");
////        glUseProgram(progTeapot.GetID());
////        glUniform3f(itemColourVec4, 0.9, 0.0, 0.3);
////
////        glEnable(GL_DEPTH_TEST);
////        glUseProgram(progTeapot.GetID());
////        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebufferA);
////        glDrawElements(GL_TRIANGLES, sizeof(cy::Vec3f)*meshArrow.NF(), GL_UNSIGNED_INT, 0);
//
//
//
//
//
//
//
//
////        //PLANE everything
////        //matrix for plane
////        transMatrixP.Get(matrixMvp);
////        mvp_pos = glGetUniformLocation(progTeapot.GetID(), "mvp");
////        glUseProgram(progTeapot.GetID());
////        glUniformMatrix4fv(mvp_pos, 1, GL_FALSE, matrixMvp);
////
////        glUniform3f(itemColourVec3, 1.0, 1.0, 1.0);
////
//////        GLint samplerPlane = glGetUniformLocation(progTeapot.GetID(), "shadow");
//////        glActiveTexture( GL_TEXTURE0 );
//////        shadowMap.BindTexture(0);
//////        glUniform1i(samplerPlane, 0);
////
////        GLuint pos_loc_plane = glGetAttribLocation(progTeapot.GetID(), "pos");
////        glUseProgram(progTeapot.GetID());
////        glBindBuffer(GL_ARRAY_BUFFER, planevertexbuffer);
////        glEnableVertexAttribArray(pos_loc_plane);
////        glVertexAttribPointer(pos_loc_plane, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
////
////        GLuint normal_loc_plane = glGetAttribLocation(progTeapot.GetID(), "normal");
////        glUseProgram(progTeapot.GetID());
////        glBindBuffer(GL_ARRAY_BUFFER, planevertexnormalbuffer);
////        glEnableVertexAttribArray(normal_loc_plane);
////        glVertexAttribPointer(normal_loc_plane, 3, GL_FLOAT, GL_FALSE,
////                                  0, (void*) 0);
////
////        glUseProgram(progTeapot.GetID());
////        glDrawArrays(GL_TRIANGLES, 0, 6);
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
