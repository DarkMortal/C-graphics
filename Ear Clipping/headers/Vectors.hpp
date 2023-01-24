#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vectors{
    private: _Float32 x,y;
    public:
        Vectors(_Float32 a,_Float32 b);
        ~Vectors();
        _Float32 dot(Vectors& v) const { return this->x*v.x + this->y*v.y; }
        _Float32 cross(Vectors& v) const { return this->x*v.y - this->y*v.x; }
        void constMul(_Float32&& m) noexcept { x *= m; y *= m; }
};

Vectors::Vectors(_Float32 a,_Float32 b):x(a),y(b){}

Vectors::~Vectors(){}

#endif // VECTOR_HPP