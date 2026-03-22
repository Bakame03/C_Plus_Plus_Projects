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

void ListOfStrings::pop_front()
{
    if (first == nullptr)
        return;

    StringNode* aSupprimer = first; 

    if (first == last)
    {
        first = nullptr;
        last = nullptr;
    }
    else
    {
        first = first->next;
    }

    delete aSupprimer;
    count--;
}

void ListOfStrings::pop_back()
{
    if (last == nullptr)
        return; // liste vide, rien à faire

    StringNode* aSupprimer = last; 

    if (first == last)
    {
        first = nullptr;
        last = nullptr;
    }
    else
    {
        StringNode* avantDernier = first;
        while (avantDernier->next != last)
        {
            avantDernier = avantDernier->next;
        }
        avantDernier->next = nullptr;
        last = avantDernier;
    }

    delete aSupprimer;
    count--;
}

void ListOfStrings::clear()
{
    StringNode* courant = first;
    while (courant != nullptr)
    {
        StringNode* suivant = courant->next;
        delete courant;
        courant = suivant;
    }
    first = nullptr;
    last = nullptr;
    count = 0;
}

ostream& operator<<(ostream& os, const ListOfStrings& liste)
{
    os << "{";
    ListOfStrings::StringNode* courant = liste.first;
    while (courant != nullptr)
    {
        os << courant->value;
        if (courant->next != nullptr)
            os << ",";
        courant = courant->next;
    }
    os << "}";
    return os;
}