


const type nulv;


template<class type> class tree
{
	public:
	// one vertice of tree
	class vertice
	{
	public:
	vertice *l;
	vertice *r;
	vertice *p;
	type v;

	int ln;
	int rn;
	vertice(){l = 0;r = 0;p = 0;ln = 0;rn = 0;}
	};


	
	vertice *root;

	tree(){root = 0;}

	// add a new vertice with value v, as child of vertice i
	void add(vertice *i,type v)
	{
		// create new vertice;
		vertice *t = new vertice;
		t->v = v; t->p = i;

		// set new vertice as child of i; 
		if(v < i->v){i->l = t; i->ln = 1;}
		else if (v > i->v){i->r = t; i->rn = 1;}
	}


	// place vertice j at position of i. j is always 0 or 1 childed.
	void replace(vertice *i,vertice *j)
	{


		// removes j by placing its child, at its position
		if(j != 0)
		{
			vertice *jc = 0;
			if(j->l != 0){jc = j->l;}
			else{jc = j->r;}

			if(leftchild(j)){j->p->l = jc;j->p->ln--;}
			else if(rightchild(j)){j->p->r = jc;j->p->rn--;}
			if(jc != 0){jc->p = j->p;}
		}


		// swaps i by j
		if(j != 0)
		{
			j->p = i->p;
			j->l = i->l;
			j->r = i->r;
			j->ln = i->ln;
			j->rn = i->rn;
		}

		// sets i's neighbour to point to j
		if(leftchild(i)){i->p->l = j;}
		else if(rightchild(i)){i->p->r = j;}
		if(i->l != 0){i->l->p = j;}
		if(i->r != 0){i->r->p = j;}
	}

	// returns true if i is a leftchild;
	bool leftchild(vertice *i)
	{
		if(i->p != 0 && i->p->l == i){return true;}
		return false;
	}

	// returns true if i ia a rightchild;
	bool rightchild(vertice *i)
	{
		if(i->p != 0 && i->p->r == i){return true;}
		return false;
	}

	// rotate vertice i to left
	vertice *leftrotate(vertice *i)
	{
		// store i, i's right, i's parent;
		vertice *ip, *ir, *irl;
		ip = i->p;
		ir = i->r;
		irl = i->r->l;


		// set i's right child
		i->r = irl; i->rn = 0;
		if(irl != 0){irl->p = i; i->rn = irl->ln + irl->rn + 1;}


		// set i as its right-child's left-child
		ir->l = i;
		i->p = ir;
		ir->ln = i->ln+i->rn+1;

		// set i's parent as parent of its right-child
		ir->p = ip;
		if(ip != 0 && ip->l == i){ip->l = ir; ip->ln = ir->ln + ir->rn +1;}
		else if(ip != 0 && ip->r == i){ip->r = ir; ip->rn = ir->ln + ir->rn +1;}

		// check if i is root;
		if(root == i){root = ir;}
		return ir;
	}
	// rotate vertice i to right
	vertice *rightrotate(vertice *i)
	{
		// store i, i's left-child, i's parent
		vertice *ip, *il, *ilr;
		ip = i->p;
		il = i->l;
		ilr = i->l->r;


		// set i's left-child
		i->l = ilr; i->ln = 0;
		if(ilr != 0){ilr->p = i; i->ln = ilr->ln + ilr->rn + 1;}


		// set i as its left-child's right-child
		il->r = i;
		i->p = il;
		il->rn = i->ln + i->rn +1;


		// set i's parent as parent of its left-child
		il->p = ip;
		if(ip != 0 && ip->l == i){ip->l = il; ip->ln = il->ln + il->rn + 1;}
		else if(ip != 0 && ip->r == i){ip->r = il; ip->rn = il->ln + il->rn + 1;}


		// check if i is root
		if(root == i){root = il;}
		return il;
	}
	// starts from i, goes to root, perform rotate when required;
	void balance(vertice *i)
	{
		// while i is not above root(i's parent is 0)
		while(i != 0)
		{
			// set i's left-child and right-child to appropriate value.
			if(i->l != 0){i->ln = i->l->ln + i->l->rn +1;}
			if(i->r != 0){i->rn = i->r->ln + i->r->rn +1;}


			// check for rotation condition
			if(i->ln > i->rn+1){i = rightrotate(i);}
			else if(i->rn > i->ln+1){i = leftrotate(i);}
			i = i->p;
		}
	}
	// push value v into tree.
	void push(type v)
	{
		// if tree is empty, insert v into root
		if(root == 0){root = new vertice;root->v = v;}
		else
		{
			vertice *i = root;

			// search for appropriate vertice to insert v, add v when found
			while(true)
			{
				if(v < i->v && i->l != 0){i = i->l;}
				else if(v > i->v && i->r != 0){i = i->r;}
				else if(v < i->v && i->l == 0){add(i,v);i = i->l;break;}
				else if(v > i->v && i->r == 0){add(i,v);i = i->r;break;}
				else{break;}
			}

			// call balance on inserted vertice, which has value v.
			balance(i);
		}
	}
	// search for vertice with value v;
	vertice *search(type v)
	{
		vertice *i = root;
		// if tree is empty, return 0;
		if(i == 0){return 0;}

		// search for appropriate vertice with value v, set to 0 if not found
		while(true)
		{
			if(v == i->v){break;}
			else if(v < i->v && i->l != 0){i = i->l;}
			else if(v > i->v && i->r != 0){i = i->r;}
			else{i = 0;break;}
		}

		return i;
	}
	// search for predecessor, given a vertice
	vertice *predecessor(vertice *i)
	{
		// if any vertices with smaller-values exists on left-side
		if(i->l != 0)
		{
			i = i->l;
			while(i->r != 0){i = i->r;}
		}
		// if any vertice with smaller-values exists on above vertice i
		else if(i->p != 0)
		{
			while(leftchild(i)){i = i->p;}
			if(rightchild(i)){i = i->p;}
			else{i = 0;}
		}
		// no smaller-value exists.
		else{i = 0;}

		return i;
	}
	// search for successor, given a vertice
	vertice *successor(vertice *i)
	{
		// if any larger value exists on right-side
		if(i->r != 0)
		{
			i = i->r;
			while(i->l != 0){i = i->l;}
		}
		// if any larger value exist above vertice i;
		else if(i->p != 0)
		{
			while(rightchild(i)){i = i->p;}
			if(leftchild(i)){i = i->p;}
			else{i = 0;}
		}
		// no larger value exists;
		else{i = 0;}

		return i;
	}
	// erases vertice with value v;
	void erase(type v)
	{
		// search for vertice with value v;
		vertice *i = search(v);
		if(i == 0){return;}

		// put one child of i in c;
		vertice *c = 0;
		if(i->l != 0){c = i->l;}
		else{c = i->r;}

		// if i is 0-1 childed
		if(i->l == 0 || i->r == 0)
		{
			// replace i with its child.
			if(leftchild(i)){i->p->l = c; i->p->ln--;}
			else if(rightchild(i)){i->p->r = c; i->p->rn--;}
			if(c != 0){c->p = i->p;}
			if(root == i){root = c;}
			delete i;
		}
		// i has both child
		else
		{
			// find predecessor , and replace with it;
			vertice *pre = predecessor(i);
			replace(i,pre);
			if(root == i){root = pre;}
			delete i;
		}
	}
	// returns value equal to or greater than v, if none returns nulv;
	type lowerbound(type v)
	{

		vertice *i = root;
		if(i == 0){return nulv;}

		// search for appropriate vertice
		while(true)
		{
			if(v == i->v){break;}
			else if(v < i->v && i->l != 0){i = i->l;}
			else if(v > i->v && i->r != 0){i = i->r;}
			else{break;}
		}

		// if v not found, search for successor
		if(i->v == v){return v;}
		else if(v < i->v){return i->v;}
		else
		{
			while(i != 0 && i->v < v){i = successor(i);}
			if(i == 0){return nulv;}
			else{return i->v;}
		}
	}
	// returns value equal to or less than v, if none return nulv;
	type upperbound(type v)
	{
		vertice *i = root;
		if(i == 0){return nulv;}

		// search for appropriate vertice
		while(true)
		{
			if(v == i->v){break;}
			else if(v < i->v && i->l != 0){i = i->l;}
			else if(v > i->v && i->r != 0){i = i->r;}
			else{break;}
		}

		// if v not found, search for predecessor
		if(i->v == v){return v;}
		else if(i->v < v){return i->v;}
		else
		{
			while(i != 0 && i->v > v){i = predecessor(i);}
			if(i == 0){return nulv;}
			else{return i->v;}
		}
	}
};
