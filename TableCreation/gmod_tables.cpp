#include <iostream>

// Including all gmod lua c api files
#include "GarrysMod/Lua/Interface.h" 
#include "GarrysMod/Lua/Types.h"
#include "GarrysMod/Lua/LuaBase.h"
#include "GarrysMod/Lua/SourceCompat.h"
#include "GarrysMod/Lua/UserData.h"


using namespace GarrysMod::Lua;

ILuaBase* g_LUA;



LUA_FUNCTION(ReturnPhrase) { // Creating function "Sum"

	std::string phrase = "Hello world!";

	LUA->PushString(phrase.c_str()); // Pushing phrase to the stack

	return 1; // Returning 1 value from the stack to Lua

}


GMOD_MODULE_OPEN() { // Called when module required 
	g_LUA = LUA; // Creating global reference


	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Pushing global table (_G) to stack

		LUA->CreateTable(); // Creating table

			LUA->PushString("Test phrase"); // Pushing string to the stack
			LUA->SetField(-2, "text"); // Setting variable name in the table (-2 is table position in stack)

			LUA->PushNumber(15); // Pushing number to the stack
			LUA->SetField(-2, "value"); // Setting variable name in the table

			LUA->PushCFunction(ReturnPhrase); // Pushing function to the stack
			LUA->SetField(-2, "getPhrase"); // Setting variable (function) name in the table

		LUA->SetField(-2, "CTable"); // Setting table name in the global table (_G.CTable)


	LUA->Pop(); // Deleting global table from stack



	return 0; 
}


GMOD_MODULE_CLOSE() { // Called when module closed
	return 0; 
}