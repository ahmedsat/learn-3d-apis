#ifndef _SAT_MATH_VECTOR_3_H
#define _SAT_MATH_VECTOR_3_H

typedef float vector3[3];

vector3 *vector3Unit();
vector3 *vector3Normalize(vector3);
vector3 *vector3Add(vector3, vector3);
vector3 *vector3Negate(vector3);
vector3 *vector3Sub(vector3, vector3);
vector3 *vector3Mult(vector3, vector3);
vector3 *vector3ScalerMult(vector3, float);
vector3 *vector3ScalerAdd(vector3, float);
float vector3LengthSquare(vector3);
float vector3Length(vector3);

#endif //_SAT_MATH_VECTOR_3_H