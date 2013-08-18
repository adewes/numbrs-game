for x = 1, 100, 1 do
  Object.Add("tank",10+math.random(120.0)+0.5,10+math.random(120.0)+0.5,1);
  Object.Add("tank",10+math.random(120.0)+0.5,10+math.random(120.0)+0.5,2);
end
for x = 1, 100, 1 do
  Object.Add("energy",10+math.random(120.0)+0.5,10+math.random(120.0)+0.5,0);
  Object.Add("building",10+math.random(120.0)+0.5,10+math.random(120.0)+0.5,2);
  Object.Add("building",10+math.random(120.0)+0.5,10+math.random(120.0)+0.5,1);
end
Logic.SetRotation(30);
print("done logic startup...");