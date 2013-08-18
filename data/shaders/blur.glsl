texture framebuffer
float direction
float size

effect
{
    float x;
    float n=5;
    vec4 color=vec4(0,0,0,0);
    for(x=-n;x<=n;x++)
    {
		if (direction==0)
			color+=framebuffer(vec2(_in.x+x/size,_in.y));
		else
			color+=framebuffer(vec2(_in.x,_in.y+x/size));
    }
    color/=2*n+1;
    _out=color;
}