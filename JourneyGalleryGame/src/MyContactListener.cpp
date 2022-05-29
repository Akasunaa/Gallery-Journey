#include "MyContactListener.h"


void MyContactListener::BeginContact(b2Contact* contact) {
    b2BodyUserData bodyA = contact->GetFixtureA()->GetBody()->GetUserData();
    b2BodyUserData bodyB = contact->GetFixtureB()->GetBody()->GetUserData();
    //InterractableObject* ioA = (InterractableObject*)(bodyA.pointer);
    //InterractableObject* ioB = (InterractableObject*)(bodyB.pointer);
    if (bodyA.pointer) {
        std::cout << "broooooooooooo" << '\n';
    }
    if (bodyB.pointer) {
        std::cout << "broooooooooooo" << '\n';
    }
    std::cout << "poutch" << '\n';
}

void MyContactListener::EndContact(b2Contact* contact) {
    //getRadarAndAircraft(contact);
    std::cout << "not poutch" << '\n';
}