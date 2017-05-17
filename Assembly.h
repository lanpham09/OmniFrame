#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "GL/glu.h"
#include "GL/gl.h"

#include <vector>

#include "model.h"
#include "OpenGL_Object.h"

#include "Utilities/Math.h"

class Assembly:public OpenGL_Object
{
public:
    Assembly( const std::vector< OpenGL_Object* >& part_list, const std::vector< Math::HomogeneousTransform* >& base_transforms );

    bool addPart(  OpenGL_Object* partPointer, Math::HomogeneousTransform* base_transform );
    //bool movePart( Model* partPointer, const Math::HomogeneousTransform& motion );
    //bool moveAssembly( const Math::HomogeneousTransform& motion );
    //bool positionAssembly( const Math::HomogeneousTransform& motion );

    virtual void render(bool wireframe = false, bool normals = false) const;

private:
    std::vector< Math::HomogeneousTransform* > part_transforms;
    Math::HomogeneousTransform  base_transform;
    std::vector< OpenGL_Object* > parts;

};

#endif // ASSEMBLY_H
