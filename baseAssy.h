#ifndef BASEASSY_H
#define BASEASSY_H

#include "Assembly.h"
#include "model.h"
#include "OpenGL_Object.h"

#include "Utilities/Math.h"

class baseAssy
{
private:
    std::vector<OpenGL_Object*> modelList;
    std::vector<Math::HomogeneousTransform* > transList;
public:
    baseAssy();
    ~baseAssy();
    Assembly* assembly;
    operator Assembly*();
};

#endif // BASEASSY_H
