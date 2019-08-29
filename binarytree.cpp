


const type nulv = -1;
template<class type> class tree
{
	public:
	// type for one vertice of tree
	class vertice
	{
	public:
	vertice *l;
	vertice *r;
	vertice *p;
	type  v;
	vertice(){l = 0;r = 0;p = 0;}
	};


	vertice *root;

	tree(){root = 0;}
	// add a new vertice with value v, with i as parent
	void add(vertice *i,type v,int dir)
	{
		vertice *t = new vertice;
		t->v = v;

		t->p = i;
		if(dir == 0){i->l = t;}
		else{i->r = t;}
	}

	// replace i by j. j is always 0 or 1 childed.
	void replace(vertice *i,vertice *j)
	{
		// remove j, by replacing j by its child
		if(j != 0)
		{
			vertice *jc = 0;
			if(j->l != 0){jc = j->l;}
			else{jc = j->r;}

			if(leftchild(j)){j->p->l = jc;}
			else if(rightchild(j)){j->p->r = jc;}
			if(jc != 0){jc->p = j->p;}
		}

		// swap i by j;
		if(j != 0)
		{
			j->p = i->p;
			j->l = i->l;
			j->r = i->r;
		}


		// set i's neighbour to point to j;
		if(leftchild(i)){i->p->l = j;}
		else if(rightchild(i)){i->p->r = j;}
		if(i->l != 0){i->l->p = j;}
		if(i->r != 0){i->r->p = j;}

	}
	// return true if i is left child;
	bool leftchild(vertice *i)
	{
		if(i->p == 0){return false;}
		else if(i->p->l == i){return true;}
		return false;
	}
	// returns true if i is right child
	bool rightchild(vertice *i)
	{
		if(i->p == 0){return false;}
		else if(i->p->r == i){return true;}
		return false;
	}
	// push a vertice with value v, if not already present;
	void push(type v)
	{
		// if tree is empty, set root to value v;
		if(root == 0){root = new vertice;root->v = v;}
		else
		{
			vertice *i = root;
			// search for appropriate vertice to push new vertice, and add
			while(true)
			{
				if(v < i->v && i->l == 0){add(i,v,0);break;}
				else if(v > i->v && i->r == 0){add(i,v,1);break;}
				else if(v < i->v){i = i->l;}
				else if(v > i->v){i = i->r;}
				else if(v == i->v){break;}						// code for v == i->v
			}
		}
	}
	// returns vertice with value v
	vertice *search(type v)
	{
		// if tree is empty, return 0
		if(root == 0){return 0;}
		else
		{
			vertice *i = root;
			// search for vertice with value v, set i to 0 if not found
			while(true)
			{
				if(v == i->v){break;}
				else if(v < i->v && i->l != 0){i = i->l;}
				else if(v > i->v && i->r != 0){i = i->r;}
				else{i = 0;break;}
			}

			return i;
		}
	}
	// return predecessor of vertice i;
	vertice *predecessor(vertice *i)
	{
		// check if value lower than i's value exist below it;
		if(i->l != 0)
		{
			i = i->l;
			while(i->r != 0){i = i->r;}
			return i;
		}
		// check if value lower than i's value exist above it;
		else if(i->p != 0)
		{
			while(leftchild(i)){i = i->p;}
			if(rightchild(i)){return i->p;}
			else{return 0;}
		}
		// no lower value exist;
		else{return 0;}
	}
	// returns successor of vertice i;
	vertice *successor(vertice *i)
	{
		// check if larger values exists below i;
		if(i->r != 0)
		{
			i = i->r;
			while(i->l != 0){i = i->l;}
			return i;
		}
		// check if larger values exists above i;
		else if(i->p != 0)
		{
			while(rightchild(i)){i = i->p;}
			if(leftchild(i)){return i->p;}
			else{return 0;}
		}
		// no larger value exists
		else{return 0;}
	}
	// erase vertice with value v;
	void erase(type v)
	{
		// search for vertice with value v;
		vertice *i = search(v);
		if(i == 0){return;}

		// set c to one of its child
		vertice *c = 0;
		if(i->l != 0){c = i->l;}
		else{c = i->r;}

		// if i is 0-1 childed.
		if(i->l == 0 || i->r == 0)
		{
			// replace i by its child
			if(leftchild(i)){i->p->l = c;}
			else if(rightchild(i)){i->p->r = c;}
			if(c != 0){c->p = i->p;}
			if(root == i){root = c;}
		}	
		// i has both child
		else
		{
			// relace i by its predecessor
			vertice *pre = predecessor(i);
			replace(i, pre);
			if(root == i){root = pre;}
		}
		delete i;
	}
	// returns value equal to or greater then v, if none return nulv;
	type lowerbound(type v)
	{
		// returns nulv if tree is empty;
		vertice *i = root;
		if(i == 0){return nulv;}

		// search for appropriate vertice with value v
		while(true)
		{
			if(v == i->v){break;}
			else if(v < i->v && i->l != 0){i = i->l;}
			else if(v > i->v && i->r != 0){i = i->r;}
			else{break;}
		}

		if(i->v == v){return v;}
		else if(v < i->v){return i->v;}
		else
		{
			// if value v is not found, search for successor
			while(i != 0 && i->v < v){i = successor(i);}
			if(i == 0){return nulv;}
			else{return i->v;}
		}
	}
	// returns value equal to or less than v, if none return nulv
	type upperbound(type v)
	{
		// if tree is empty, return nulv
		vertice *i = root;
		if(i == 0){return nulv;}

		// search for appropriate vertice with value v
		while(true)
		{
			if(v == i->v){break;}
			else if(v < i->v && i->l != 0){i = i->l;}
			else if(v > i->v && i->r != 0){i = i->r;}
			else{break;}
		}

		if(i->v == v){return v;}
		else if(i->v < v){return i->v;}
		else
		{
			// if vertice with value v not found, search predecessor
			while(i != 0 && i->v > v){i = predecessor(i);}
			if(i == 0){return nulv;}
			else{return i->v;}
		}
	}
	/*
	void preorder()
	{
		vertice *i = root;
		if(i == 0){return;}
		// stack s//
		cout << i->v << " ";
		if(i->r != 0){s.push(i->r);}
		if(i->l != 0){s.push(i->l);}
		while(s.size())
		{
			vertice *top = s.top();s.pop();
			cout << top->v << " ";
			if(top->r != 0){s.push(tpp->r);}
			if(top->l != 0){s.push(top->l);}
		}
	}
	void inorder()
	{
		vertice *i = root;
		if(i == 0){return;}
		// stack s//
		if(i->r != 0){s.push(i->r,0);}
		s.push(i,1);
		if(i->l != 0){s.push(i->l,0);}
		while(s.size())
		{
			vertice *top,b = s.top();s.pop();
			if(b == 0)
			{
				if(top->r != 0){s.push(top->r,0);}
				s.push(top,1);
				if(top->l != 0){s.push(top->l,0);}
			}else
			{
				cout << top->v << " ";
			}
		}
	}
	*/
};
