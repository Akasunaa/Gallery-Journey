#pragma once
#include "box2d/box2d.h"
#include <InteractableObject.h>
#include <iostream>
#include <Player.h>

class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};