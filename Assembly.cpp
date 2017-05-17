#include "Assembly.h"

Assembly::Assembly( const std::vector< OpenGL_Object* >& part_list, const std::vector< Math::HomogeneousTransform* >& base_transforms ):
    OpenGL_Object()
{
    part_transforms = base_transforms;
    objectTransform = Math::HomogeneousTransform(Math::UNDEFINED_FRAME, part_transforms[0]->fromFrame() );
    parts = part_list;

    assert( part_transforms.size() == parts.size() );
}

// Adds a part to the assembly
bool Assembly::addPart(  OpenGL_Object* partPointer, Math::HomogeneousTransform* base_transform )
{
    assert( partPointer != 0 && base_transform != 0 );

    part_transforms.push_back( base_transform );
    parts.push_back( partPointer );
}


/*  Not sure about this one yet...

bool Assembly::movePart( Model* partPointer, const Math::HomogeneousTransform& motion )
{
    std::vector< Model* >::iterator partIterator = parts.begin();
    std::vector< Math::HomogeneousTransform* >::iterator transformationIterator;

    bool found = false;
    while( partIterator != parts.end() && !found )
    {
        found = (*partIterator) == partPointer;
    }
}

*/


//bool Assembly::moveAssembly( const Math::HomogeneousTransform& motion )
//{
//    base_transform = base_transform*motion;

//    return true;
//}

//bool Assembly::positionAssembly( const Math::HomogeneousTransform& motion )
//{

//    base_transform = motion;

//    return true;
//}

// This function does the Open GL rendering of each part in their specified locations
void Assembly::render( bool wireframe, bool normals ) const
{
    std::vector< OpenGL_Object* >::const_iterator partIterator = parts.begin();
    std::vector< Math::HomogeneousTransform* >::const_iterator transformIterator = part_transforms.begin();

    // go though each part
    while( partIterator != parts.end() &&  transformIterator != part_transforms.end() )
    {

        // Find part transformation
        Math::HomogeneousTransform tmpTransform( objectTransform * (*transformIterator)->inverseTransform() );
        //tmpTransform.setFromTransform(  );
        (*partIterator)->placeObject( tmpTransform );

        glEnable(GL_MULTISAMPLE);
        (*partIterator)->render(wireframe, normals); // render part
        glDisable(GL_MULTISAMPLE);

        //glPopMatrix(); // remove model matrix

        partIterator++; // go to next part
        transformIterator++; // go to next transform
    }


    return;
}
