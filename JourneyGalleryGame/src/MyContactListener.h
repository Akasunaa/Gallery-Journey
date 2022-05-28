#pragma once
#include "box2d/box2d.h"

class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();
        std::cout << "poutch" << '\n';
    }

    void EndContact(b2Contact* contact) {
        //getRadarAndAircraft(contact);
        std::cout << "not poutch" << '\n';
    }
};