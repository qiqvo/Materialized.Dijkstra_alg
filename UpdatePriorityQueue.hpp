#ifndef _UPDATEPRIORITYQUEUE_H_
#define _UPDATEPRIORITYQUEUE_H_

#include <functional>
#include <list>

// top is least

/*
	Container should be equipped with bi-way iterator
	and erase, emplace operations
*/
template <class T, 
    class Container = std::list<T>,
    class Compare = std::less<typename Container::value_type>,
    class Equals = std::equal_to<typename Container::value_type> >
class UpdatePriorityQueue {
	// Container elems;
	Compare compare;
	Equals equal_to;
	
	// places element `el` after iterator `it` and increases iterator
	template <class ContIterator>
	void place(ContIterator it, const T& el){
		// TODO: check list documentation
		elems.emplace(it, el);
	}

	template <class ContIterator>
	void remove(ContIterator it){
		elems.erase(it);
	}
public:
	Container elems;

	// TODO check if std queue have same constructor
	UpdatePriorityQueue(Compare compare = std::less<typename Container::value_type>(), 
			Equals equal_to = std::equal_to<typename Container::value_type>()) 
			: compare(compare), equal_to(equal_to) {};

	void push(const T& el){
		auto it = std::begin(elems);
		for (; it != std::end(elems); ++it){
			if (! compare(*it, el)){ 
				// el < v
				--it;
				place(it, el);
				break;
			}
		}
		if (it == std::end(elems)){
			place(it, el);
		}
		else{
			for(; it != std::end(elems); ++it){
				if (equal_to(*it, el)){
					remove(it);
					break;
				}
			}
		}
	}

	auto top() const {
		return *(std::begin(elems));
	}

	auto pop() {
		return elems.pop_front();
	}

	auto empty(){
		return elems.empty();
	}
	auto size(){
		return elems.size();
	}
};

#endif // _UPDATEPRIORITYQUEUE_H_