


// define intersect//
const int psize = 100;
// array of input points
xy points[psize];
// points in convex-hull
xy hull[psize];
// left-buttom most point
xy p0;



// less function for sorting
bool sortxy(xy p1,xy p2)
{
	return left(p0,p1,p2);
}
// returns true if p2 is more distant from p0, than p1 from p0;
bool far(xy p0,xy p1,xy p2)
{
	p1.x -= p0.x;
	p1.y -= p0.y;
	p2.x -= p0.x;
	p2.y -= p0.y;
	return ((p1.x*p1.x) + (p1.y*p1.y)) < ((p2.x*p2.x) + (p2.y*p2.y));
}
// sort points in anti-clockwise order, remove points with same angle.
int sortpoints(int n)
{
	// set left-buttom most point;
	p0 = points[0];
	int ip = 0;
	for(int i = 1;i < n;i++)
	{
		if(p0.y > points[i].y || (p0.y == points[i].y && p0.x > points[i].x)){p0 = points[i];ip = i;}
	}
	swap(points[ip], points[0]);
	
	// sort points in anti-clockwise order from p0;
	sort(points+1, points+n, sortxy);

	// remove points with same angle, leaving most distant point
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

	// returns len of remaining array
	return c+1;
}
// runs jarvismarch algorithm for convex-hull.
int jarvismarch(int n)
{
	// sort points according to anti-clockwise order
	n = sortpoints(n);
	
	// add first two points in hull
	int c = 2;
	hull[0] = points[0];
	hull[1] = points[1];
	for(int i = 2;i < n;i++)
	{
		xy cmax = points[i];
		int im = i;

		// search for point making biggest right turn;
		for(int j = i+1;j < n;j++)
		{
			if(right(points[c-1],cmax,points[j]))
			{
				cmax = points[j];
				im = j;
			}
		}
		// add found point to convex-hull
		hull[c++] = cmax;
		i = im;
	}
	// return len of points in hull;
	return c;
}