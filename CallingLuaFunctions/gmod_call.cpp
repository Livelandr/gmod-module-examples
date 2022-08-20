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

		LUA->GetField(-1, "print"); // Pushing _G.print to the stack
		LUA->PushString("Hello C++!"); // _G.print("Hello C++!")

		LUA->Call(1, 0); // Calling _G.print("Hello C++!"), 1 arg, returning 0

		LUA->GetField(-1, "math"); // Pushing _G.math to the stack
		LUA->GetField(-1, "random"); // Pushing _G.math.random to the stack
		LUA->PushNumber(1); // Pushing first arg
		LUA->PushNumber(10); // Pushing second arg

		LUA->Call(2, 1); // Calling _G.math.random(1, 10)

		double result = LUA->GetNumber(-1); // Getting result
		LUA->Pop(2); // Removing random and math from the stack

		// Custom hook call
		LUA->GetField(-1, "print"); // Pushing _G.print to the stack
		LUA->PushNumber(result); // _G.print(result)

		LUA->Call(1, 0); // Calling _G.print(result)


	LUA->Pop(); // Removing global table from stack


	return 0; 
}


GMOD_MODULE_CLOSE() { // Called when module closed
	return 0; 
}