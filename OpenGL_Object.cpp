#include "OpenGL_Object.h"
#include <string.h>



OpenGL_Object::OpenGL_Object()
{
//    if( originTrans == 0 )
//    {
//        double tmp[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//        memcpy(da_originTransform, tmp, 16*sizeof(double));
//    } else {
//        memcpy(da_originTransform, originTrans, 16*sizeof(double));
//    }
    return;
}

void OpenGL_Object::pushObject( const Math::HomogeneousTransform & push)
{
    objectTransform = objectTransform*push;
}

void OpenGL_Object::placeObject( const Math::HomogeneousTransform & place)
{
    objectTransform = place;
}

