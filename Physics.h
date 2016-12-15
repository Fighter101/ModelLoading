//
// Created by madara on 11/12/16.
//

#ifndef MODELLOADING_PHYSICS_H
#define MODELLOADING_PHYSICS_H

#include "Includes.h"
#include "Model.h"
struct PhysicsObject {
    bool dynamic;

    ////////////DynamicShape Params/////////////////
    btConvexHullShape * unoptimizedHull;
    btShapeHull * hullOptimizer;
    btConvexHullShape * hullShape;

    btTriangleMesh * triangleMesh;
    btBvhTriangleMeshShape * triangleMeshShape;

    btCollisionShape * collisionShape;
    btDefaultMotionState * motionState;
    btScalar mass;
    btVector3 inertia;
    btRigidBody * rigidBody;
    Model * model;

};
class Physics {

private:
    btBroadphaseInterface * broadphaseInterface;
    btDefaultCollisionConfiguration  * collisionConfiguration;
    btCollisionDispatcher * collisionDispatcher;
    btSequentialImpulseConstraintSolver * constraintSolver;
    btDiscreteDynamicsWorld * world;
public:
    void intialize();
    void laodDynamicCollisionShape (PhysicsObject * physicsObject , const Model &   model );
    void loadStaticCollisionShaoe (PhysicsObject *physicsObject , const Model & model );

};


#endif //MODELLOADING_PHYSICS_H
