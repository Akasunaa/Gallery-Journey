#include "MyContactListener.h"

/*
Listener qui vérifie si le joueur est en contact avec d'autre box2d
*/
void MyContactListener::BeginContact(b2Contact* contact) {
    if (contact && contact->IsTouching()) {
        b2BodyUserData bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
        b2BodyUserData bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyA.pointer || bodyB.pointer) {
            auto ptrC = (Player*)bodyA.pointer;
            auto ptrD = (Player*)bodyB.pointer;
            if (ptrC || ptrD) {
                if (bodyA.pointer) {
                    auto ptrA = (InterractableObject*)bodyA.pointer;
                    if (ptrA) {
                        ptrA->interact();
                    }
                }
                if (bodyB.pointer) {
                    auto ptrB = (InterractableObject*)bodyB.pointer;
                    if (ptrB) {
                        ptrB->interact();
                    }
                }
            }
        }
        

    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    if (contact && !contact->IsTouching()) {
        b2BodyUserData bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
        b2BodyUserData bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyA.pointer) {
            auto ptrA = (InterractableObject*)bodyA.pointer;
            if (ptrA) {
                ptrA->dontInteract();
            }
        }
        if (bodyB.pointer) {
            auto ptrB = (InterractableObject*)bodyB.pointer;
            if (ptrB) {
                ptrB->dontInteract();
            }
        }
    }
}