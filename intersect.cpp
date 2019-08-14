


class xy
{
	public:
	int x;
	int y;
};
// returns cross-product of p0p1, ans p0p2
int cross(xy p0,xy p1,xy p2)
{
	p1.x -= p0.x;
	p1.y -= p0.y;
	p2.x -= p0.x;
	p2.y -= p0.y;
	return p1.x*p2.y - p2.x*p1.y;
}
// return true if p0->p1->p2 makes a left turn
bool left(xy p0,xy p1,xy p2)
{
	return cross(p0, p1, p2) > 0;
}
// returns true is p0->p1->p2 makes a right turn
bool right(xy p0,xy p1,xy p2)
{
	return cross(p0, p1, p2) < 0;
}
// returns if p0, p1, p2 are colinear
bool colinear(xy p0,xy p1,xy p2)
{
	return cross(p0, p1, p2) == 0;
}
// returns true if p2 is on line p0, p1. assumes p1, p2, p3 are colinear
bool onsegment(xy p1,xy p2,xy p3)
{
	if (min(p1.x,p2.x) <= p3.x && p3.x <= max(p1.x,p2.x) && min(p1.y,p2.y) <= p3.y && p3.y <= max(p1.y,p2.y)){return true;}
	return false;
}
// returns true if line p1p2, p3p4 intersects
bool intersect(xy p1,xy p2,xy p3,xy p4)
{
	int d1 = cross(p3,p4,p1);
	int d2 = cross(p3,p4,p2);
	int d3 = cross(p1,p2,p3);
	int d4 = cross(p1,p2,p4);
	if(((d1>0 && d2<0)||(d1<0 && d2>0)) && ((d3>0 && d4<0)||(d3<0 && d4>0))){return true;}
	else if(d1 == 0 && onsegment(p3,p4,p1)){return true;}
	else if(d2 == 0 && onsegment(p3,p4,p2)){return true;}
	else if(d3 == 0 && onsegment(p1,p2,p3)){return true;}
	else if(d4 == 0 && onsegment(p1,p2,p4)){return true;}
	return false;
}