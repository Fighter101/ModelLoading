//
// Created by madara on 11/12/16.
//

#include "Physics.h"

void Physics::intialize() {
    broadphaseInterface = new btDbvtBroadphase{};
    collisionConfiguration = new btDefaultCollisionConfiguration();
    collisionDispatcher = new btCollisionDispatcher{collisionConfiguration};
    btGImpactCollisionAlgorithm::registerAlgorithm(collisionDispatcher);
    constraintSolver = new btSequentialImpulseConstraintSolver{};
    world = new btDiscreteDynamicsWorld{collisionDispatcher, broadphaseInterface, constraintSolver, collisionConfiguration};
    world->setGravity(btVector3(0, -9.8, 0));

}

void Physics::laodDynamicCollisionShape(PhysicsObject *physicsObject, const Model &model) {
    physicsObject->dynamic = true;
    physicsObject->triangleMesh = nullptr;
    physicsObject->triangleMeshShape = nullptr;
    physicsObject->unoptimizedHull = new btConvexHullShape();
    for(GLint i = 0 ;i < model.meshes.size() ; ++i){
        for(GLint j =0 ; j< model.meshes[i].indices.size(); ++i){
            btVector3 vertex (model.meshes[i].vertices[model.meshes[i].indices[j]].Position.x ,model.meshes[i].vertices[model.meshes[i].indices[j]].Position.y , model.meshes[i].vertices[model.meshes[i].indices[j]].Position.z );
            physicsObject->unoptimizedHull->addPoint(vertex);
        }
    }

}
