#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -5.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METERS_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXELS_TO_METERS(p)  ((float) METERS_PER_PIXEL * p)

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
	uint score;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size, bool isStatic);	//Method that creates chains. Has a bool to make the chain static or dynamic.
	PhysBody* CreateStaticChain(int x, int y, int* points, int size);			//Alternative method to draw Static chains


	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

private:

	bool debug;
	b2World* world = nullptr;
	b2MouseJoint* mouse_joint;
	b2Body* ground;

	friend class ModuleSceneIntro; //Gives the ModuleSceneIntro class access to private methods and variables from class ModulePhysics. (friend class) Temporal.
};

//Chains (Revise)
		//Declaring the Background Chains (Maybe move to ModuleIntroScene):

	//No need to create a b2Vec2 as the creation of it is already done in the CreateChain() method.
	//b2Vec2 exterior_Vec[62];				//This array is uninitialized. To initalize all the elements of the array to zero: b2Vec2 bckgndExteriorVec[62] = {};

	//Exterior Background chain.


	/*for (int i = 0; backgroundExterior[i] != NULL; i++)
	{
		exterior_Vec[i].Set(PIXEL_TO_METERS(backgroundExterior[i * 2]), PIXEL_TO_METERS(backgroundExterior[i * 2 + 1]));
	}*/

	//b2BodyDef exteriorChain_Def;				//Defines the frame of a geometrical body/shape
	//exteriorChain_Def.type = b2_staticBody;		//Sets the type of the body definition to static. Static bodies cannot be affected by any forces.

	//exteriorChain_Def.position.Set(0, 0);		//Sets the initial position of the exterior chain.

	//b2Body * extChain_Body = world->CreateBody(&exteriorChain_Def);	//The  exterior_chain body definition is passed to the world object to create the body.

	//b2ChainShape exterior_chain;				//Creates the exterior chain. Chains have two-sided collisions and generate smooth collisions with information connectivity. Holds ALL the data required to construct a rigid body. In this case a chain.

	//exterior_chain.CreateLoop(exterior_Vec, 62);

	//Interior Background Chain 
	// Pivot 0, 0