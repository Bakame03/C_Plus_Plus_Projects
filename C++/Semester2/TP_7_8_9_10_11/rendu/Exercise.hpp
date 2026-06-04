#ifndef Exercise_HPP
#define Exercise_HPP

#include "Shape.hpp"

class Exercise : public Shape {
    private:
        uint L;   
    protected:
        virtual void write(ostream& os) const override;
    public:
        Exercise(EZColor col, uint x, uint y, uint L, uint thick = 1, bool fill = true);
        Exercise(istream& is);
        virtual ~Exercise();

        inline uint getL() const { return L; }
        inline void setL(uint _L) { L = _L; }

        virtual string getTypeName() const override { return "Exercise"; }
        virtual void draw(EZWindow& win) const override;
        virtual void modifyAttributes() override;
};

#endif
