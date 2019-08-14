


// define stack//
// define intersect//
const int psize = 100;

// array of point
xy points[psize];
// array of points in convex hull
xy hull[psize];

// left-buttom most point
xy p0;


// less function for sorting
bool sortxy(xy p1,xy p2)
{
	return left(p0,p1,p2);
}

// return true if p2 is more distant than p1, from p0. assume p0, p1, p2 are colinear
bool far(xy p0,xy p1,xy p2)
{
	p1.x -= p0.x;
	p1.y -= p0.y;
	p2.x -= p0.x;
	p2.y -= p0.y;
	return ((p1.x*p1.x) + (p1.y*p1.y)) < ((p2.x*p2.x) + (p2.y*p2.y));
}


// sorts points in anti-clockwise order of their angle from p0, return len of array of points
int sortpoints(int n)
{
	// find left-buttom most point, put in p0
	p0 = points[0];
	int ip = 0;
	for(int i = 1;i < n;i++)
	{
		if(p0.y > points[i].y || (p0.y == points[i].y && p0.x > points[i].x)){p0 = points[i];ip = i;}
	}
	swap(points[ip], points[0]);


	// sort points in anti-clockwise order from p0
	sort(points+1, points+n, sortxy);


	// remove points with same angle, leaving most-distant point
	int c = 1;
	for(int i = 2;i < n;i++)
	{
		if(colinear(p0, points[c], points[i]) && far(p0, points[c], points[i]))
		{
			points[c] = points[i];
		}
		else if(colinear(p0, points[c], points[i]) == 0)
		{
			c++;
			points[c] = points[i];
		}
	}
	return c+1;
}

// runs graham-scan algorithm, return len array hull
int grahamscan(int n)
{
	// sort points in anti-clockwise order
	n = sortpoints(n);
	
	// push first three points;
	stack stk;
	stk.push(points[0]);
	stk.push(points[1]);
	stk.push(points[2]);


	// iterate over all points
	for(int i = 3;i < n;i++)
	{
		// remove all points from stack from top, where points[i] make right turn
		xy p1 = stk.top(); stk.pop();
		xy p0 = stk.top(); stk.pop();
		while(right(p0, p1, points[i]))
		{
			p1 = p0;
			p0 = stk.top(); stk.pop();
		}

		stk.push(p0);
		stk.push(p1);
		stk.push(points[i]);
	}

	// place all point in stack, in array hull
	int c = 0;
	while(stk.size())
	{
		hull[c++] = stk.top(); stk.pop();
	}
	// return len of array hull
	return c;
}