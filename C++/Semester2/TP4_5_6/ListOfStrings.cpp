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

void ListOfStrings::splice(ListOfStrings& other)
{
    // 1. Si l'autre liste est vide, il n'y a rien à faire
    if (other.first == nullptr)
        return;

    // 2. Si NOTRE liste est vide, on récupère directement les pointeurs de l'autre
    if (first == nullptr)
    {
        first = other.first;
        last = other.last;
    }
    // 3. on accroche l'autre liste à la fin de la nôtre
    else
    {
        last->next = other.first;  
        last = other.last;         
    }
    count += other.count;

    // 5. On vide l'autre liste pour lui enlever les droit de OWNER sur la liste
    other.first = nullptr;
    other.last = nullptr;
    other.count = 0;
}

void ListOfStrings::reverse()
{
    // 1. S'il n'y a qu'un maillon ou zéro, c'est déjà à l'envers
    if (first == nullptr || first == last)
        return;

    StringNode* precedent = nullptr;
    StringNode* courant = first;
    StringNode* suivant = nullptr;

    // 2. L'actuel "first" va devenir le "last"
    last = first;

    // 3. On parcourt la liste et on retourne chaque flèche vers l'arrière
    while (courant != nullptr)
    {
        suivant = courant->next;    
        courant->next = precedent;  
        precedent = courant;        
        courant = suivant;          
    }

    // 4. À la fin, "precedent" est sur l'ancien dernier maillon
    // qui devient donc notre nouveau premier maillon
    first = precedent;
    
    precedent = nullptr;
}

void ListOfStrings::insert_sorted(StringNode* node)
{
    // 1. Cas : la liste est vide OU le nouveau mot est "plus petit" que le premier
    // on peut comparer grâce à <= pour l'ordre alphabétique
    if (first == nullptr || node->value <= first->value)
    {
        node->next = first;
        first = node;
        if (last == nullptr) // Si la liste était vide
            last = node;
        count++;
        return;
    }

    // 2. Cas général : on parcourt la liste pour trouver où insérer
    // On s'arrête quand on arrive à la fin OU quand la valeur suivante est "trop grande"
    StringNode* courant = first;
    while (courant->next != nullptr && courant->next->value < node->value)
    {
        courant = courant->next;
    }

    // 3. On coupe la chaîne et on insère notre maillon ici
    node->next = courant->next;
    courant->next = node;

    // 4. Si on a inséré tout à la fin, on met à jour "last"
    if (node->next == nullptr)
        last = node;

    count++;
}

void ListOfStrings::insert_sorted(string str)
{
    insert_sorted(new StringNode(str));
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