#include <iostream>

// Including all gmod lua c api files
#include "GarrysMod/Lua/Interface.h" 
#include "GarrysMod/Lua/Types.h"
#include "GarrysMod/Lua/LuaBase.h"
#include "GarrysMod/Lua/SourceCompat.h"
#include "GarrysMod/Lua/UserData.h"


using namespace GarrysMod::Lua;

ILuaBase* g_LUA;




class Human { // Creating human class

private:
	std::string name;
	int age;

public:

	Human(std::string _name = "John Doe", int _age = 0) { // Constructor
		name = _name;
		age = _age;
	}

	void setName(std::string _name) {
		name = _name;
	}

	void setAge(int _age) {
		age = _age;
	}

	std::string getName() {
		return name;
	}

	int getAge() {
		return age;
	}

};


LUA_FUNCTION(CreateHuman) { // Human creation function

	std::string name = LUA->CheckString(1); // Getting name of human
	int age = LUA->CheckNumber(2); // Getting age of human

	Human* newHuman = new Human(name, age); // Creating new human in the heap and getting pointer on it

	LUA->PushUserType(newHuman, Type::UserData); // Pushing pointer to Lua

	return 1; // We returning 1 value
}

LUA_FUNCTION(DestroyHuman) { // That sounds cruel. Human deletion function
	
	LUA->CheckType(1, Type::UserData); // Is first argument is UserData?
	Human* human = LUA->GetUserType<Human>(1, Type::UserData); // Getting Human pointer

	delete human; // Always delete elements from heap to avoid memory leak!

	return 0; // We don't return anything!
}

LUA_FUNCTION(SetAge) { // Set age function

	LUA->CheckType(1, Type::UserData); // Is first argument is UserData?
	Human* human = LUA->GetUserType<Human>(1, Type::UserData); // Getting Human pointer
	int age = LUA->CheckNumber(2); // Getting int from stack

	human->setAge(age); // Setting human age

	return 0; // We don't return anything again.
}

LUA_FUNCTION(GetAge) { // Get name function

	LUA->CheckType(1, Type::UserData); // Is first argument is UserData?
	Human* human = LUA->GetUserType<Human>(1, Type::UserData); // Getting Human pointer

	LUA->PushNumber(human->getAge()); // Pushing age to stack

	return 1; // We returning 1 value
}


LUA_FUNCTION(SetName) { // Set name function 

	LUA->CheckType(1, Type::UserData); // Is first argument is UserData?
	Human* human = LUA->GetUserType<Human>(1, Type::UserData); // Getting Human pointer
	std::string name = LUA->CheckString(2); // Getting string from stack

	human->setName(name); // Setting human name

	return 0; // We don't return anything again.
}

LUA_FUNCTION(GetName) { // Get name function

	LUA->CheckType(1, Type::UserData); // Is first argument is UserData?
	Human* human = LUA->GetUserType<Human>(1, Type::UserData); // Getting Human pointer

	LUA->PushString(human->getName().c_str()); // Pushing string to stack

	return 1; // We returning 1 value
}



GMOD_MODULE_OPEN() { // Called when module required 
	g_LUA = LUA; // Creating global reference


	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Pushing global table (_G) to stack

		LUA->CreateTable(); // Creating our table
	
			LUA->PushCFunction(CreateHuman); // Creating human creation function
			LUA->SetField(-2, "New"); // Adding function to our table

			LUA->PushCFunction(DestroyHuman); // Creating human destroy function
			LUA->SetField(-2, "Delete"); // Adding function to our table

			// Setting up setters and getters
			LUA->PushCFunction(GetAge);
			LUA->SetField(-2, "GetAge");

			LUA->PushCFunction(GetName);
			LUA->SetField(-2, "GetName");

			LUA->PushCFunction(SetAge);
			LUA->SetField(-2, "SetAge");

			LUA->PushCFunction(SetName);
			LUA->SetField(-2, "SetName");


		LUA->SetField(-2, "Human"); // _G.Human = our table

	LUA->Pop(); // Deleting global table from stack



	return 0;
}


GMOD_MODULE_CLOSE() { // Called when module closed
	return 0;
}