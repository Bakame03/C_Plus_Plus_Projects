#ifndef __LISTOFSTRINGS_HPP__
#define __LISTOFSTRINGS_HPP__

#include <iostream>
#include <string>

class ListOfStrings
{
    private:
        class StringNode
        {
            public:
                std::string value;
                StringNode* next;
                StringNode(std::string, StringNode* = nullptr);
                StringNode(const StringNode&);
                ~StringNode();
        };
        size_t count;
        StringNode* first;
        StringNode* last;
        void push_front(StringNode* node);
        void push_back(StringNode* node);
        

    public:
        ListOfStrings();
        ListOfStrings(const ListOfStrings&);
        ~ListOfStrings();
        inline size_t size() const { return count; };
        const std::string& front() const;
        const std::string& back() const;
        void push_front(std::string str);
        void push_back(std::string str);
        

};

#endif //__LISTOFSTRINGS_HPP__
