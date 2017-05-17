#ifndef VIRTICALSUPPORTASSY_H
#define VIRTICALSUPPORTASSY_H

#include "Assembly.h"
#include "model.h"
#include "OpenGL_Object.h"

#include "Utilities/Math.h"


class virticalSupportAssy
{
private:
    std::vector<OpenGL_Object*> modelList;
    std::vector<Math::HomogeneousTransform* > transList;
public:
    virticalSupportAssy();
    ~virticalSupportAssy();
    Assembly* assembly;
    operator Assembly*();
};

#endif // VIRTICALSUPPORTASSY_H
