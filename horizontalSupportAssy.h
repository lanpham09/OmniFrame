#ifndef HORIZONTALSUPPORTASSY_H
#define HORIZONTALSUPPORTASSY_H

#include "Assembly.h"
#include "model.h"
#include "OpenGL_Object.h"

#include "Utilities/Math.h"

class horizontalSupportAssy
{
private:
    std::vector<OpenGL_Object*> modelList;
    std::vector<Math::HomogeneousTransform* > transList;
public:
    horizontalSupportAssy();
    ~horizontalSupportAssy();
    Assembly* assembly;
    operator Assembly*();
};

#endif // HORIZONTALSUPPORTASSY_H
