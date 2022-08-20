#include <iostream>

// Including all gmod lua c api files
#include "GarrysMod/Lua/Interface.h" 
#include "GarrysMod/Lua/Types.h"
#include "GarrysMod/Lua/LuaBase.h"
#include "GarrysMod/Lua/SourceCompat.h"
#include "GarrysMod/Lua/UserData.h"


using namespace GarrysMod::Lua;

ILuaBase* g_LUA;

LUA_FUNCTION(hookFunction) {


	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Pushing global table (_G) to stack

		LUA->GetField(-1, "print"); // Pushing _G.print to the stack
		
			LUA->PushString("C++ hook called!"); // _G.print("C++ hook called!")

		LUA->Call(1, 0); // Calling _G.print("C++ hook called!")

	LUA->Pop(); // Removing global table from stack


	return 0; // Returing 0 variables

}

GMOD_MODULE_OPEN() { // Called when module required 
	g_LUA = LUA; // Creating global reference


	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Pushing global table (_G) to stack

		// Calling hook from Lua
		LUA->GetField(-1, "hook"); // Getting _G.hook
		LUA->GetField(-1, "Call"); // Getting _G.hook.Call
		LUA->PushString("CallFromCPP"); // Pushing "CallFromCPP" to stack
		LUA->PushNil(); // Pushing nil to stack
		LUA->PushString("Hello world!"); // Pushing "Hello world!" to stack

		LUA->Call(3, 0); // Calling _G.hook.Call("CallFromCPP", nil, "Hello world!")
		LUA->Pop(); // Removing hook from the stack


		// Creating custom hook
		LUA->GetField(-1, "hook"); // Getting _G.hook
		LUA->GetField(-1, "Add"); // Getting _G.hook.Add
		LUA->PushString("CustomCPPHook"); // Pushing "CustomCPPHook" to stack
		LUA->PushString("SomeIdentifier"); // Pushing "SomeIdentifier" to stack
		LUA->PushCFunction(hookFunction); // Pushing C++ function to stack

		LUA->Call(3, 0); // Calling _G.hook.Add("CustomCPPHook", "SomeIdentifier", hookFunction)
		LUA->Pop(); // Removing hook from the stack


	LUA->Pop(); // Removing global table from stack


	return 0; 
}


GMOD_MODULE_CLOSE() { // Called when module closed
	return 0; 
}