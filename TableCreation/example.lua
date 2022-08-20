require("example") -- Require our module

print(CTable.text) -- => Test phrase
print(CTable.value) -- => 15
print(CTable.value * 2) -- => 30
 
CTable.value = 50

print(CTable.value) -- => 50
print( CTable.getPhrase() ) -- => Hello world!
