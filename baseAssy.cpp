#include "baseAssy.h"

baseAssy::baseAssy()
{
    Math::Matrix3x3 orient;
    orient << 1, 0, 0,
              0, 1, 0,
              0, 0, 1;
    modelList.push_back(new Model("Solidworks Models/Base Plate Top - Fixed.obj"));
    transList.push_back(new Math::HomogeneousTransform( orient, Math::Displacement(0,0,.275/2.0+.375/2,Math::UNDEFINED_FRAME,INCH), Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME) );


    orient << 0, -1, 0,
              0, 0, 1,
              1, 0, 0;
    modelList.push_back(new Model("Solidworks Models/Base Plate - Table.obj"));
    transList.push_back(new Math::HomogeneousTransform( orient, Math::Displacement(0,.75,-.75,Math::UNDEFINED_FRAME,INCH), Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME) );




    assembly = new Assembly( modelList, transList );

}

baseAssy::~baseAssy()
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

 baseAssy::operator Assembly*()
{
    return assembly;
}
