#ifndef OPENGL_OBJECT_H
#define OPENGL_OBJECT_H
#include "Utilities/Math.h"

class OpenGL_Object
{
protected:
    Math::HomogeneousTransform objectTransform;
public:
    OpenGL_Object();
    virtual ~OpenGL_Object() { return; }
    virtual void render(bool wireframe = false, bool normals = false) const= 0;
    virtual void pushObject( const Math::HomogeneousTransform & push);
    virtual void placeObject( const Math::HomogeneousTransform & place);
};

#endif // OPENGL_OBJECT_H
