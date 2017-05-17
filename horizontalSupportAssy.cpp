#include "horizontalSupportAssy.h"

#include "math.h"

horizontalSupportAssy::horizontalSupportAssy()
{
    modelList.push_back(new Model("Solidworks Models/40-4040 - 4.obj"));
    transList.push_back(new Math::HomogeneousTransform( Math::Orientation(0,Math::Vector(1,1,1),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME),
                                                        Math::Displacement(0,1.5,-5.5,Math::UNDEFINED_FRAME,INCH)));

    modelList.push_back(new Model("Solidworks Models/40-4080 - 762mm or 30in.obj"));
    transList.push_back(new Math::HomogeneousTransform( Math::Orientation(-M_PI/2.0,Math::Vector(0,0,1),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME),
                                                        Math::Displacement(-.75,0,-15,Math::UNDEFINED_FRAME,INCH)));

    modelList.push_back(new Model("Solidworks Models/Omnimagnet Capping Plate.obj"));
    Math::Matrix3x3 orient;
    orient << 0, 0, -1,
              0, 1, 0,
              1, 0, 0;
    transList.push_back(new Math::HomogeneousTransform( orient, Math::Displacement(3,-2.5,-0,Math::UNDEFINED_FRAME,INCH), Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME) );

    modelList.push_back(new Model("Solidworks Models/Omnimagnet Holding Plate.obj"));
    transList.push_back(new Math::HomogeneousTransform( orient, Math::Displacement(3,2.5,0,Math::UNDEFINED_FRAME,INCH), Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME) );


    assembly = new Assembly( modelList, transList );

}

horizontalSupportAssy::~horizontalSupportAssy()
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

 horizontalSupportAssy::operator Assembly*()
{
    return assembly;
}

