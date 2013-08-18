#ifndef _VECTOR

#define _VECTOR

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Vector
{
public:
	float operator*(Vector b){return x*(b.x)+y*(b.y)+z*(b.z);};
	bool Parallel(Vector b){if (fabs(Normalize()*b.Normalize()-1.f)<1e-3)return true;return false;};
	Vector rotate(float angle){Vector r;r.x=cos(angle)*x-sin(angle)*y;r.y=sin(angle)*x+cos(angle)*y;return r;};
	Vector operator*(float b){Vector r;r.x=x*b;r.y=y*b;r.z=z*b;return r;};
	Vector operator/(float b){Vector r;r.x=x/b;r.y=y/b;r.z=z/b;return r;};
	float Norm(){return sqrt((float)(x*x+y*y+z*z));};
	Vector operator+(Vector b){Vector r;r.x=x+b.x;r.y=y+b.y;r.z=z+b.z;return r;};
	Vector operator-(Vector b){Vector r;r.x=x-b.x;r.y=y-b.y;r.z=z-b.z;return r;};
	Vector operator-(){Vector r;r.x=-x;r.y=-y;r.z=-z;return r;}
	Vector cross(Vector b){Vector r;r.x=y*b.z-z*b.y;r.y=z*b.x-x*b.z;r.z=x*b.y-y*b.x;return r;};
	Vector Normalize(){Vector r=*this;float norm=Norm();r.x/=norm;r.y/=norm;r.z/=norm;return r;};
	Vector operator*=(float a){x*=a;y*=a;z*=a;return *this;}
	Vector operator/=(float a){x/=a;y/=a;z/=a;return *this;}
	Vector(){x=0;y=0;z=0;};
	Vector(float xx,float yy,float zz){x=xx;y=yy;z=zz;}
	float x,y,z;

	friend ostream& operator<<(ostream& os,Vector a)
	{
		os << "(" << a.x << "," << a.y << "," << a.z << ")";
		return os;
	}
	friend Vector operator*(float a,Vector b){return b*a;}
};

#endif