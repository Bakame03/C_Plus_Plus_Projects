#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <stdexcept> 

template <typename T>
class List
{
    private:
        // StringNode devient simplement Node et stocke un type générique T
        class Node
        {
            public:
                T value;
                Node* next;
                
                Node(T val, Node* suivant = nullptr) : value(val), next(suivant) {}
                Node(const Node& other) : value(other.value), next(nullptr) {}
                ~Node() {}
        };

        size_t count;
        Node* first;
        Node* last;

        void push_front(Node* node);
        void push_back(Node* node);
        void insert_sorted(Node* node);

    public:
        List();
        List(const List<T>& other);
        List<T>& operator=(const List<T>& other);
        ~List();
        
        inline size_t size() const { return count; }

        // --- Sous-classes Itérateurs ---
        class Iterator {
            private:
                Node* current;
            public:
                Iterator(Node* n) : current(n) {}
                T& operator*() { return current->value; }
                Iterator& operator++() { current = current->next; return *this; }
                bool operator!=(const Iterator& other) const { return current != other.current; }
        };

        class ConstIterator {
            private:
                Node* current;
            public:
                ConstIterator(Node* n) : current(n) {}
                const T& operator*() const { return current->value; }
                ConstIterator& operator++() { current = current->next; return *this; }
                bool operator!=(const ConstIterator& other) const { return current != other.current; }
        };

        // --- Méthodes pour utiliser le range-based for loop ---
        Iterator begin() { return Iterator(first); }
        Iterator end() { return Iterator(nullptr); }
        ConstIterator begin() const { return ConstIterator(first); }
        ConstIterator end() const { return ConstIterator(nullptr); }

        // --- Opérateur d'accès par index ---
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        
        // Ici je remplace les std::string par T
        const T& front() const;
        const T& back() const;
        void push_front(T val);
        void push_back(T val);
        void pop_front();
        void pop_back();
        void clear();
        void splice(List<T>& other);
        void reverse();
        void insert_sorted(T val);
        void sort();

        friend std::ostream& operator<<(std::ostream& os, const List<T>& liste)
        {
            os << "{";
            Node* courant = liste.first;
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
};

// --- IMPLÉMENTATION ---
// Constructeur par défaut
template <typename T>
List<T>::List() : count(0), first(nullptr), last(nullptr) 
{}

// Destructeur
template <typename T>
List<T>::~List()
{
    Node* courant = first;
    while (courant != nullptr)
    {
        Node* suivant = courant->next;
        delete courant;
        courant = suivant;      
    }
}

// Constructeur de copie
template <typename T>
List<T>::List(const List<T>& other) : count(0), first(nullptr), last(nullptr)
{
    Node* courant = other.first;
    while (courant != nullptr)
    {
        push_back(courant->value);
        courant = courant->next;
    }
}

// Opérateur d'affectation 
template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
    if (this != &other) // Éviter l'auto-affectation
    {
        clear(); // On vide notre liste actuelle
        Node* courant = other.first;
        while (courant != nullptr)
        {
            push_back(courant->value);
            courant = courant->next;
        }
    }
    return *this;
}

// --- Méthodes d'accès ---
template <typename T>
const T& List<T>::front() const { return first->value; }

template <typename T>
const T& List<T>::back() const { return last->value; }

// --- Méthodes d'ajout ---
template <typename T>
void List<T>::push_front(Node* node)
{
    if(first == nullptr) { last = first = node; }
    else { node->next = first; first = node; }
    count++;
}

template <typename T>
void List<T>::push_front(T val)
{
    push_front(new Node(val));
}

template <typename T>
void List<T>::push_back(Node* node)
{
    if(last == nullptr) { first = last = node; }
    else { last->next = node; last = node; }
    count++;
}

template <typename T>
void List<T>::push_back(T val)
{
    push_back(new Node(val));
}

// --- Méthodes de retrait ---
template <typename T>
void List<T>::pop_front()
{
    if (first == nullptr) return;

    Node* aSupprimer = first; 
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

template <typename T>
void List<T>::pop_back()
{
    if (last == nullptr) return;

    Node* aSupprimer = last; 
    if (first == last)
    {
        first = nullptr;
        last = nullptr;
    }
    else
    {
        Node* avantDernier = first;
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

// --- Méthode clear ---
template <typename T>
void List<T>::clear()
{
    Node* courant = first;
    while (courant != nullptr)
    {
        Node* suivant = courant->next;
        delete courant;
        courant = suivant;
    }
    first = nullptr;
    last = nullptr;
    count = 0;
}

template <typename T>
void List<T>::splice(List<T>& other)
{
    if (other.first == nullptr) return;

    if (first == nullptr)
    {
        first = other.first;
        last = other.last;
    }
    else
    {
        last->next = other.first;  
        last = other.last;         
    }
    count += other.count;

    other.first = nullptr;
    other.last = nullptr;
    other.count = 0;
}

template <typename T>
void List<T>::reverse()
{
    if (first == nullptr || first == last) return;

    Node* precedent = nullptr;
    Node* courant = first;
    Node* suivant = nullptr;

    last = first;

    while (courant != nullptr)
    {
        suivant = courant->next;    
        courant->next = precedent;  
        precedent = courant;        
        courant = suivant;          
    }
    first = precedent;
}

template <typename T>
void List<T>::insert_sorted(Node* node)
{
    // L'opérateur <= devra être supporté par le type T !
    if (first == nullptr || node->value <= first->value)
    {
        node->next = first;
        first = node;
        if (last == nullptr) last = node;
        count++;
        return;
    }

    Node* courant = first;
    while (courant->next != nullptr && courant->next->value < node->value)
    {
        courant = courant->next;
    }

    node->next = courant->next;
    courant->next = node;

    if (node->next == nullptr) last = node;
    count++;
}

template <typename T>
void List<T>::insert_sorted(T val)
{
    insert_sorted(new Node(val)); 
}

template <typename T>
void List<T>::sort()
{
    if (first == nullptr || first == last) return;

    List<T> listeTriee;

    Node* courant = first;
    while (courant != nullptr)
    {
        Node* suivant = courant->next;
        courant->next = nullptr;
        listeTriee.insert_sorted(courant);
        courant = suivant;
    }

    first = listeTriee.first;
    last = listeTriee.last;

    listeTriee.first = nullptr;
    listeTriee.last = nullptr;
    listeTriee.count = 0;
}

// --- Implémentation de l'opérateur [] ---
template <typename T>
T& List<T>::operator[](size_t index)
{
    Node* courant = first;
    for (size_t i = 0; i < index && courant != nullptr; i++)
        courant = courant->next;
    
    if (courant == nullptr) throw std::out_of_range("Index out of range");
    return courant->value;
}

template <typename T>
const T& List<T>::operator[](size_t index) const
{
    Node* courant = first;
    for (size_t i = 0; i < index && courant != nullptr; i++)
        courant = courant->next;
        
    if (courant == nullptr) throw std::out_of_range("Index out of range");
    return courant->value;
}

#endif