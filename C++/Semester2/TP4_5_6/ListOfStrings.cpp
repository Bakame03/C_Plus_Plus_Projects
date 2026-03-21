#include "ListOfStrings.hpp"

using namespace std;

ListOfStrings::StringNode::StringNode(string val, StringNode* suivant)
    : value(val),
      next(suivant)
{}


ListOfStrings::StringNode::StringNode(const StringNode& other)
    : value(other.value),
      next(nullptr)
{}

ListOfStrings::StringNode::~StringNode()
{}

ListOfStrings::ListOfStrings()
    : count(0),
      first(nullptr),
      last(nullptr)
{}

ListOfStrings::ListOfStrings(const ListOfStrings& other)
    : count(0),
      first(nullptr),
      last(nullptr)
{
    StringNode* courant = other.first;
    while (courant != nullptr)
    {
        push_back(courant->value);
        courant = courant->next;
    }
}


ListOfStrings::~ListOfStrings()
{
    StringNode* courant = first;
    while (courant != nullptr)
    {
        StringNode* suivant = courant->next;
        delete courant;
        courant = suivant;      
    }
}

const string& ListOfStrings::front() const
{
    return first->value;
}

const string& ListOfStrings::back() const
{
    return last->value;
}

void ListOfStrings::push_front(StringNode* node)
{
    if(first == nullptr)
    {
        last = first = node;
    }
    else
    {
        node->next = first;
        first = node;
    }
    count++;
}

void ListOfStrings::push_front(string str)
{
    push_front(new StringNode(str));
}

void ListOfStrings::push_back(StringNode* node)
{
    if(last == nullptr)
    {
        first = last = node;
    }
    else
    {
        last->next = node;
        last = node;
    }
    count++;
}

void ListOfStrings::push_back(string str)
{
    push_back(new StringNode(str));
}