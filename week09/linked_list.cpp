#include <iostream>

template<typename Elem>
struct Link
{
	Link(const Elem& v = Elem(), Link* p = 0, Link* s = 0) : prev(p), succ(s), val(v) {}

	Link* prev;
	Link* succ;
	Elem val;
};

template<typename Elem>
class my_list
{
public:
	my_list(): first(new Link<Elem>()), last(first) {}

	class iterator;

	iterator begin() { return iterator(first); }
	iterator end() { return iterator(last); }

	iterator insert(iterator p, const Elem& v);
	iterator erase(iterator p);

	void push_back(const Elem& val);
	void push_front(const Elem& val);

	Elem& front() { return *first; }
	Elem& back() { return *last; }

	Link<Elem>* first;
	Link<Elem>* last;

};

template<typename Elem>
class my_list<Elem>::iterator
{
	Link<Elem>* curr;

public:
	iterator(Link<Elem>* p): curr{p} {}
	iterator& operator++() { curr = curr->succ; return *this;}
	iterator& operator--() { curr = curr->prev; return *this;}
	Elem& operator*() { return curr->val; }

	bool operator==(const iterator& b) const { return curr==b.curr; }
	bool operator!=(const iterator& b) const { return curr!=b.curr; }
};

template<typename Elem>
void my_list<Elem>::push_front(const Elem& v)
{
	first = new Link<Elem>(v, 0, first);
}

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
	{
		if(*high < *p) high = p;
	}
	return high;
}


int main()
{
	my_list<int> ml;
	for (int i = 0; std::cin >> i; )
	{
		ml.push_front(i);
	}

	for(const auto& e : ml)
	{
		std::cout << e << "-->";
	}
	std::cout << "nil\n";
	my_list<int>::iterator highest = high(ml.begin(), ml.end());

	std::cout << "Highest value: " << *highest << std::endl;

	return 0;
}
