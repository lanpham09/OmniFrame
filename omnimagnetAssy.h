#ifndef OMNIMAGNETASSY_H
#define OMNIMAGNETASSY_H

#include "Assembly.h"
#include "model.h"
#include "OpenGL_Object.h"

#include "Utilities/Math.h"

class omnimagnetAssy
{
private:
    std::vector<OpenGL_Object*> modelList;
    std::vector<Math::HomogeneousTransform* > transList;
public:
    omnimagnetAssy();
    ~omnimagnetAssy();
    Assembly* assembly;
    operator Assembly*();
};

#endif // OMNIMAGNETASSY_H
