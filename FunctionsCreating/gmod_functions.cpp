#include <iostream>

// Including all gmod lua c api files
#include "GarrysMod/Lua/Interface.h" 
#include "GarrysMod/Lua/Types.h"
#include "GarrysMod/Lua/LuaBase.h"
#include "GarrysMod/Lua/SourceCompat.h"
#include "GarrysMod/Lua/UserData.h"


using namespace GarrysMod::Lua;

ILuaBase* g_LUA;



LUA_FUNCTION(Sum) { // Creating function "Sum"

	double a = LUA->CheckNumber(1); // Checking is that the first argument is a number
	double b = LUA->CheckNumber(2); // Checking is that the second argument is a number


	LUA->PushNumber(a + b); // Pushing sum to stack

	return 1; // Returning 1 value from the stack to Lua

}

LUA_FUNCTION(Echo) { // Creating function "Echo"

	std::string a = LUA->CheckString(1); // Checking is that the first argument is a string
	a = "C++ Echo: " + a; // Adding "C++ Echo: " to beginning of the string


	LUA->PushString( a.c_str() ); // Converting to const char* and pushing to stack

	return 1; // Returning 1 value from the stack to Lua

}


GMOD_MODULE_OPEN() { // Called when module required 
	g_LUA = LUA; // Creating global reference


	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Pushing global table (_G) to stack

		LUA->PushCFunction(Sum);	// Pushing function to stack
		LUA->SetField(-2, "CppSum"); // _G.CppSum = Sum    -2 is global table (_G) position in stack

		LUA->PushCFunction(Echo);	// Pushing function to stack  
		LUA->SetField(-2, "CppEcho"); // _G.CppEcho = Echo    -2 is global table (_G) position in stack

	LUA->Pop(); // Deleting global table from stack



	return 0; 
}


GMOD_MODULE_CLOSE() { // Called when module closed
	return 0; 
}