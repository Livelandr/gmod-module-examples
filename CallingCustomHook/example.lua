hook.Add("CallFromCPP", "TestHook", function(text)
    print("Hook called from C++:", text)
end)


require("example") -- Require our module

hook.Call("CustomCPPHook")