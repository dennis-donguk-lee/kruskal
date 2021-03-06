/*!
  \brief  Disoint sets using quick find implementation (linked lists and 
  a look-up table)

Implements:
	ctor (size)
	Make( id )      initialize
	Join( id,id )   join 2 sets
	GetRepresentative( id )

Rationale:
	elements of the set are assumed to be contiguous 0,1,2,3,....
*/

#ifndef DISJOINT_SETS_H
#define DISJOINT_SETS_H
#include <cstdlib>
#include <fstream> //ostream, istream

class Node
{
public:
  Node(size_t const& value);
  Node* Next() const;
  void SetNext(Node* new_next);
  size_t Value() const;

  friend  std::ostream& operator<< (std::ostream& os, Node const& node);

private:
  size_t value;
  Node* next;
};

class Head
{
public:
  Head();
  ~Head();
  size_t Size() const;
  void Reset();
  Node* GetFirst() const;
  Node* GetLast() const;
  void Init(size_t value);
  void Join(Head* pHead2);

  Head(Head const&) = delete;
  Head& operator=(Head const&) = delete;

  friend std::ostream& operator<< (std::ostream& os, Head const& head);

private:
  size_t counter;
  Node* first;
  Node* last;
};

class DisjointSets {
public:
  DisjointSets(size_t const& capacity);
  ~DisjointSets();
  void   Make();
  void   Join(size_t const& id1, size_t const& id2) const;
  size_t GetRepresentative(size_t const& id) const;
  size_t operator[](size_t const& id) const;
  friend std::ostream& operator<< (std::ostream& os, DisjointSets const& ds);
  DisjointSets(DisjointSets const&) = delete;
  DisjointSets& operator=(DisjointSets const&) = delete;
private:
  size_t size;
  size_t capacity;
  size_t* representatives;
  Head* heads;
};


#endif
