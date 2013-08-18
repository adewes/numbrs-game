texture framebuffer
vec3 color
float param

effect
{
	vec2 coord;

	float x;

    float strokes=100;

    float strokes2=100;

    float stroke_x;
    float stroke_y;

    stroke_x=floor(_in.x*strokes2)/strokes2;
    stroke_y=floor(_in.y*strokes2)/strokes2;
	vec2 px=_in;

    vec4 pixel = framebuffer(px);
    vec4 pixel2 = framebuffer(vec2(px.x,px.y-1/strokes2));
    vec4 pixel3 = framebuffer(vec2(px.x-1/strokes2,px.y));


    float x1,y1,xn,yn,a,b;
    a=cos(param*0.5)*2.0;
    b=sin(param*0.7)*2.0;
    vec4 pd1=pixel3-pixel;
    vec4 pd2=pixel2-pixel;
    x1=(pd1.r+pd1.b+pd1.g)/5;
    y1=(pd2.g+pd2.b+pd2.r)/5;
	for(x=0;x<5;x++)
	{
		xn=y1;
		yn=-b*x1+a*y1-y1*y1*y1;
		x1=xn;
		y1=yn;
	}

	float cx=(_in.x)*strokes;
	float cy=(_in.y)*strokes;
	
	float seedx=x1*4;
    float seedy=y1*4;
    
    stroke_x=floor(cx+strokes*seedx*0.01)/strokes;
    stroke_y=floor(cy+strokes*seedy*0.01)/strokes;
	
	vec4 c=framebuffer(vec2(stroke_x,stroke_y));

    _out =vec4(c.rgb, 1.0);
}
