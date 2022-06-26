#ifndef SHAPE_H
#define SHAPE_H

enum shapeTag
{
    SPHERE,
    PLANE
};

struct S_vector3
{
    double _x, _y, _z;
};

struct S_ray
{
    S_vector3 _o, _d;
};

struct S_sphere
{
    S_vector3 _origin;
    double _r, _rs;
};

struct S_plane
{
    S_vector3 _origin, _normal;
};

struct S_intersection
{
    S_ray _r;
    double t;
};

union U_shape
{
    S_sphere _sphere;
    S_plane _plane;
};

struct T_shape
{
    shapeTag tag;
    U_shape shape;
};

S_intersection intersect(T_shape s, S_ray r)
{
    S_intersection intersection;
    switch (s.tag)
    {
    case SPHERE:
        intersection.t = 0;
        break;

    case PLANE:
        intersection.t = 10;
        break;

    default:
        break;
    }
    return intersection;
};

#endif
// SHAPE_H