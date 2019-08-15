

// define intersect//
// define set//



const int psize = 100;
const int neginf = -1000000;
xy points[psize];


// class for line end-points; pi- index of point, ty- first/last end-point;
class fst
{
	public:
	int pi;
	int ty;
};
// less function for fst, according to (y, x);
bool operator<(const fst arg1, const fst arg2)
{
	return points[arg1.pi].y < points[arg2.pi].y || (points[arg1.pi].y == points[arg2.pi].y && points[arg1.pi].x < points[arg2.pi].x);
}


fst lines[psize];
// sorting less func for sorting in order by (x, ty, y);
bool sortlines(const fst arg1, const fst arg2)
{
	xy p1, p2;
	p1 = points[arg1.pi];
	p2 = points[arg2.pi];

	return p1.x < p2.x || (p1.x == p2.x && (arg1.ty < arg2.ty || (arg1.ty == arg2.ty && p1.y < p2.y)));
}

set<fst> s;
// line-sweep algorithm for deciding line intersection
bool func(int n)
{
	// sort line endpoints by (x, ty, y);
	sort(lines, lines+n, sortlines);
	int found = 0;
	for(int i = 0;i < n;i++)
	{
		set<fst>::iterator prei;
		set<fst>::iterator succi;
		
		// last point using for searching
		lines[n].pi = n;
		lines[n].ty = 0;


		if(lines[i].ty == 0)			// first end-point
		{
			s.insert(lines[i]);			// add line end-point , sorted by (y,x);

			// find predecessor
			points[lines[n].pi].y = points[lines[i].pi].y-1;
			points[lines[n].pi].x = neginf;
			prei = s.upper_bound(lines[n]);

			// find successor
			points[lines[n].pi].y = points[lines[i].pi].y+1;
			points[lines[n].pi].x = neginf;
			succi = s.lower_bound(lines[n]);

			if(prei != s.end())
			{
				fst pre = *prei;
				// sometime pre is same point as lines[i], which is checked
				// if lines[i].pi is start-point, then lines[i].pi+1 is end-point;
				if(pre.pi != lines[i].pi && intersect(points[pre.pi], points[pre.pi+1], points[lines[i].pi], points[lines[i].pi+1])){found = 1;}
			}
			if(succi != s.end())
			{
				fst succ = *succi;
				if(intersect(points[succ.pi], points[succ.pi+1], points[lines[i].pi], points[lines[i].pi+1])){found = 1;}
			}
		}
		else			// second end-point;
		{
			// find predecessor
			points[lines[n].pi].y = points[lines[i].pi-1].y-1;
			points[lines[n].pi].x = neginf;
			prei = s.upper_bound(lines[n]);

			// find successor
			points[lines[n].pi].y = points[lines[i].pi-1].y+1;
			points[lines[n].pi].x = neginf;
			succi = s.lower_bound(lines[n]);

			lines[i].pi = lines[i].pi-1;
			lines[i].ty = 0;
			s.erase(lines[i]);

			if(prei != s.end() && succi != s.end())
			{
				fst pre = *prei;
				fst succ = *succi;

				if(pre.pi != lines[i].pi && intersect(points[pre.pi], points[pre.pi+1], points[succ.pi], points[succ.pi+1])){found = 1;}
			}
		}
	}
	return found;
}
