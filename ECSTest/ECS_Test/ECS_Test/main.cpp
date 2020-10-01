#include <iostream>
#include <ctime>

#include "ComponentContainer.h"
#include "ComponentManager.h"

int main()
{
	std::cout << "Start Test" << "\n";

	class Vec2
	{
	public:
		Vec2() { x = 0; y = 0; }
		Vec2(int a, int b) { x = a; y = b; }
		double x;
		double y;
	};

	class Vec3
	{
	public:
		Vec3() { x = 0; y = 0; z = 0; }
		Vec3(int a, int b, int c) { x = a; y = b; z = c; }
		double x;
		double y;
		double z;
	};


	struct SmallStruct
	{
		int x;
		int y;
	};


	struct SomeData
	{
		const char* k;
	};

	struct DisplayData
	{
		const char* model;
		Vec2 loc;
		Vec2 scale;
		Vec3 color;
		float angle;
		int frame;
	};

	ComponentManager manager;
	manager.RegisterComponent<SomeData>();
	manager.RegisterComponent<SmallStruct>();	
	manager.RegisterComponent<DisplayData>();

	int a = manager.GetArraySize<SmallStruct>();
	int b = manager.GetArraySize<SomeData>();
	int c = manager.GetArraySize<DisplayData>();

	std::cout << "Component Arrays Created" << "\n" << "Component Count -> " << a + b + c << "\n";

	int max_objects = 50000;

	std::clock_t start = std::clock();
	double time;
	double total = 0;


	std::cout << "\n" << "COMPONENT MANAGER" << "\n" << "\n";

	//CREATE
	
	start = std::clock();

	for (int i = 1; i < max_objects; i++)
	{
		object obj = i;

		SmallStruct strct = { i * 2,i * 3 };
		manager.AddComponent<SmallStruct>(obj, strct);
	}
	for (int i = 1; i < max_objects; i++)
	{
		object obj = i;

		SomeData n = { "LONG NAME" };
		manager.AddComponent<SomeData>(obj, n);

	}
	for (int i = 1; i < max_objects; i++)
	{
		object obj = i;

		DisplayData d = { "MODEL",Vec2(100,220),Vec2(5,5),Vec3(1,1,1),80.5f,0 };
		manager.AddComponent<DisplayData>(obj, d);
	}

	time = ((double)std::clock() - (double)start) / (double)CLOCKS_PER_SEC*1000;

	a = manager.GetArraySize<SmallStruct>();
	b = manager.GetArraySize<SomeData>();
	c = manager.GetArraySize<DisplayData>();

	std::cout << "Components Added" << "\n" << "Component Count -> " << a + b + c << "\n";
	std::cout << "Run Time->" << time << "\n";

	//ACCESS
	
	start = std::clock();

	total = 0;

	for (int i = 1; i < manager.GetArraySize<SmallStruct>()+1; i++)
	{

		object obj = manager.GetObject<SmallStruct>(i);

		DisplayData dp = manager.GetComponent<DisplayData>(obj);

		int x1 = manager.GetComponent<SmallStruct>(obj).x;
		double x2 = dp.angle;
		int x3 = dp.scale.x;
		int x4 = dp.scale.y;
		int x5 = dp.loc.x;
		int x6 = dp.loc.y;

		const char* z1 = manager.GetComponent<SomeData>(obj).k;
		const char* z2 = dp.model;
		total += x1;
		total += x2;
		total += x3;
		total += x4;
		
	}

	time = ((double)std::clock() - (double)start) / (double)CLOCKS_PER_SEC * 1000;


	std::cout << "Components Accessed" << "\n" << "Value Calcutalted -> " << total << "\n";
	std::cout << "Run Time->" << time << "\n";

	//DELETE

	start = std::clock();

	for (int i = 1; i < max_objects; i++)
	{
		object obj = i;

		manager.DeleteComponent<SmallStruct>(obj);
		manager.DeleteComponent<SomeData>(obj);
		manager.DeleteComponent<DisplayData>(obj);

	}

	time = ((double)std::clock() - (double)start) / (double)CLOCKS_PER_SEC * 1000;

	a = manager.GetArraySize<SmallStruct>();
	b = manager.GetArraySize<SomeData>();
	c = manager.GetArraySize<DisplayData>();

	std::cout << "Components Deleted" << "\n" << "Component Count -> " << a + b + c << "\n";
	std::cout << "Run Time->" << time << "\n";

	




	

	char tempchar;
	std::cin >> tempchar;

	return 0;
}