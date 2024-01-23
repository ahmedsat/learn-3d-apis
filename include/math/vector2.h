#ifndef _SAT_MATH_VECTOR_2_H
#define _SAT_MATH_VECTOR_2_H

typedef struct vector2
{
    float x;
    float y;
};

vector2 vector2Unit();
vector2 vector2Normalize(vector2);
vector2 vector2Add(vector2, vector2);
vector2 vector2Negate(vector2);
vector2 vector2Sub(vector2, vector2);
vector2 vector2Mult(vector2, vector2);
vector2 vector2ScalerMult(vector2, float);
vector2 vector2ScalerAdd(vector2, float);
float vector2LengthSquare(vector2);
float vector2Length(vector2);

#endif //_SAT_MATH_VECTOR_2_H