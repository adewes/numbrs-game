texture framebuffer
vec3 color
float param

effect
{
	float x;

    float x1,y1,xn,yn,a,b;
    a=(_in.x);
    b=(_in.y+0.8)*3;
    x1=a;
	for(x=0;x<param*10;x++)
	{
		x1=x1*b*sin(1.0-x1);
	}
	
    _out =vec4(x1,1.0-x1,0, 1.0);
}
