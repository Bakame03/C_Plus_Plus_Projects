#include "ListOfStrings.hpp"

using namespace std;

ListOfStrings::ListOfStrings()
    : count(0),
      first(nullptr),
      last(nullptr)
{}

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