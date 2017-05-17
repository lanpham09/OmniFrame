#include "virticalSupportAssy.h"
#include "math.h"

virticalSupportAssy::virticalSupportAssy()
{
    modelList.push_back(new Model("Solidworks Models/Base Plate - Rotating.obj"));
    transList.push_back(new Math::HomogeneousTransform( Math::Orientation(0,Math::Vector(1,0,0),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME),
                                                        Math::Displacement(0,0,-.75,Math::UNDEFINED_FRAME,INCH)));

    modelList.push_back(new Model("Solidworks Models/40-8080 - 600mm or 24in.obj"));
    transList.push_back(new Math::HomogeneousTransform( Math::Orientation(0,Math::Vector(1,0,0),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME),
                                                        Math::Displacement(0,0,11.25,Math::UNDEFINED_FRAME,INCH)));

    modelList.push_back(new Model("Solidworks Models/8020-40-2050 - Endcap for 40-8080.obj"));
    transList.push_back(new Math::HomogeneousTransform( Math::Orientation(M_PI,Math::Vector(1,0,0),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME),
                                                        Math::Displacement(0,0,-23.125,Math::UNDEFINED_FRAME,INCH)));


    assembly = new Assembly( modelList, transList );

}

virticalSupportAssy::~virticalSupportAssy()
{
    for( int i=0; i<modelList.size(); i++ )
    {
        if( modelList[i] )
            delete modelList[i];
    }
    for( int i=0; i<transList.size(); i++ )
    {
        if( transList[i] )
            delete transList[i];
    }

    delete assembly;
}

 virticalSupportAssy::operator Assembly*()
{
    return assembly;
}
