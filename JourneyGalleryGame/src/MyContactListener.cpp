#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact) {
    b2BodyUserData bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
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
    std::cout << "poutch";
}

void MyContactListener::EndContact(b2Contact* contact) {
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
    std::cout << "poutch";
}