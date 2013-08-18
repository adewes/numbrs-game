cnt=cnt+1;
if cnt>200/(1+l.Points/10000) or l:nObjects()<60 then
	cnt=0;
	balls[n]=Object();
	s=Shape();
	radius=math.random(30)+20;
	balls[n]:SetPosition(250+math.random(500),1000);
	number=math.random(10)-1;
	if math.random(4)==1 then
		balls[n]:SetOperator(math.random(4));
		radius=30;
		s:Circle(radius,0,0);
		balls[n]:SetScale(1.6);
		balls[n]:SetRadius(radius);
	else
		balls[n]:SetNumber(number);	
		radius=(1.0+math.log(1.0+number))*15;
		balls[n]:SetRadius(radius);
		s:Circle(radius,0,0);
		balls[n]:SetScale(radius*0.03);
	end
	balls[n]:AddShape(s);
	l:AddObject(balls[n]);
	n=n+1;
end