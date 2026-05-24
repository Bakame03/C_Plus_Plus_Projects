#ifndef LABEL_HPP
#define LABEL_HPP

#include "Shape.hpp"

class Label : public Shape {
private:
    string text;
    int fontNum; // Attribut ajouté

protected:
    virtual void write(ostream& os) const override;

public:
    Label(EZColor col, uint x, uint y, string txt, int font, uint thick = 1);
    Label(istream& is);
    virtual ~Label();

    // Accesseurs et Mutateurs
    inline string getText() const { return text; }
    inline void setText(string t) { text = t; }
    inline int getFontNum() const { return fontNum; }
    inline void setFontNum(int f) { fontNum = f; }

    virtual string getTypeName() const override { return "Label"; }
    virtual void draw(EZWindow& win) const override;
    virtual void modifyAttributes() override;
};

#endif