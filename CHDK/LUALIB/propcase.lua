--[[ 
This module loads a table which maps camera property case names to 
their respective numbers. It also takes care to load the correct property 
case set for the camera.

Usage: 
  proptable=require "propcase"
  Tv=get_prop(proptable.TV)
--]]

if get_propset()==1 then
  return require("gen/propset1")
elseif get_propset()==2 then
  return require("gen/propset2")
elseif get_propset()==3 then
  return require("gen/propset3")
elseif get_propset()==4 then
  return require("gen/propset4")
else
  error('Unsupported propset ' .. get_propset(), 1)
end
