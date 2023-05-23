require("example") -- Require our module


local newHuman = Human.New("Livelandr", 16) -- Creating human

print( Format("Hello, my name is %s and i'm %i years old!", Human.GetName(newHuman), Human.GetAge(newHuman)) )

Human.SetAge(newHuman, Human.GetAge(newHuman) + 1 ) -- Adding 1 year to age

print("Now, i'm ".. Human.GetAge(newHuman) .. " years old")


Human.Delete(newHuman) -- Destroying human to avoid memory leak  
