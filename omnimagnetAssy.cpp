#include "omnimagnetAssy.h"

omnimagnetAssy::omnimagnetAssy()
{
    modelList.push_back(new Model("Solidworks Models/OmnimagPart.obj"));
    transList.push_back(new Math::HomogeneousTransform( Math::Orientation(0,Math::Vector(0,0,1),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME),
                                                        Math::Displacement(0,0,0,Math::UNDEFINED_FRAME,INCH)));

    assembly = new Assembly( modelList, transList );

}

omnimagnetAssy::~omnimagnetAssy()
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

 omnimagnetAssy::operator Assembly*()
{
    return assembly;
}
