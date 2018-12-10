#include "disjoint_sets.h"

//class Node implementation
Node::Node( size_t const& value ) : value(value), next() {}

Node* Node::Next() const { return next; }

void  Node::SetNext( Node* new_next ) { next = new_next; }

size_t Node::Value() const { return value; }

std::ostream& operator<< (std::ostream& os, Node const& node) {
	os << "(" << node.value << " ) -> ";
	return os;
}

//class Head implementation
Head::Head() : counter(), first(), last() {}

Head::~Head() {
  auto* walker = first;
  while (walker)
  {
    auto* tmp = walker->Next();
    delete walker;
    walker = tmp;
  }
}

size_t Head::Size() const      { return counter; }

void   Head::Reset()           { counter = 0; last = first = nullptr; }

Node*  Head::GetFirst() const  { return first; }

Node*  Head::GetLast()  const  { return last; }

void   Head::Init(const size_t value ) {
	first = last = new Node( value );
	counter = 1;
}

void   Head::Join( Head* pHead2 )
{
  // Update nodes and counter which are being joined.
  last->SetNext(pHead2->GetFirst());
  last = pHead2->GetLast();
  counter += pHead2->counter;

  // Update the vacant head.
  pHead2->counter = 0;
  pHead2->first = pHead2->last = nullptr;
}

std::ostream& operator<< (std::ostream& os, Head const& head) {
	os << "[" << head.counter << " ] -> ";
	return os;
}

//class DisjointSets implementation
DisjointSets::DisjointSets( size_t const& capacity ) : 
	size(0),
	capacity(capacity),
	representatives(new size_t[capacity]),
	heads          (new Head[capacity])
{ }

DisjointSets::~DisjointSets() {
	delete [] heads;
	delete [] representatives;
}

void DisjointSets::Make( ) {
	if ( size == capacity ) throw "DisjointSets::Make(...) out of space";
	heads[size].Init( size );
	representatives[size] = size;
	++size;
}

void DisjointSets::Join( size_t const& id1, size_t const& id2 ) const
{
  if (!heads[id1].Size() || !heads[id2].Size())
  {
    return;
  }
  // Join id2->id1
  else if (heads[id1].Size() <= heads[id2].Size() && heads[id1].Size())
  {
    heads[id2].Join(&heads[id1]);
    representatives[id1] = representatives[id2];
  }
  // Join id1->id2
  else
  {
    for (size_t i = 0; i < size; ++i)
    {
      // Skip the different representatives or zero size heads.
      if (representatives[i] == representatives[id1] && heads[i].Size())
      {
        heads[i].Join(&heads[id2]);
        representatives[id2] = representatives[id1];
        break;
      }
    }
  }
}

size_t DisjointSets::GetRepresentative( size_t const& id ) const {
	return representatives[id];
}

size_t DisjointSets::operator[]( size_t const& id ) const {
	return representatives[id];
}

std::ostream& operator<< (std::ostream& os, DisjointSets const& ds) {
	for (size_t i=0; i<ds.size; ++i ) {
		os << i << ":  ";
		Head *p_head = &ds.heads[i];
		os << *p_head;
		Node* p_node = p_head->GetFirst();
		while ( p_node ) {
			os << *p_node;
			p_node = p_node->Next();
		}
		os << "NULL (representative " << ds.representatives[i] << ")\n";
	}
	return os;
}
