//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4FieldManager.cc,v 1.4.2.1 2001/06/28 19:08:18 gunter Exp $
// GEANT4 tag $Name:  $
//
#include "G4FieldManager.hh"

G4FieldManager::G4FieldManager()
{ 
   fDetectorField= 0;
   fAllocatedChordFinder= false;

   fDelta_One_Step_Value= fDefault_Delta_One_Step_Value;
   fDelta_Intersection_Val= fDefault_Delta_Intersection_Val;
}

G4FieldManager::G4FieldManager(G4MagneticField *detectorField)
{
   fDetectorField= detectorField;

   this->CreateChordFinder(detectorField);

   fDelta_One_Step_Value= fDefault_Delta_One_Step_Value;
   fDelta_Intersection_Val= fDefault_Delta_Intersection_Val;
}


G4FieldManager::~G4FieldManager()
{
   if( fAllocatedChordFinder ){
      delete fChordFinder;
   }
}

void
G4FieldManager::CreateChordFinder(G4MagneticField *detectorMagField)
{
   if ( fAllocatedChordFinder )
      delete fChordFinder;
   fChordFinder= new G4ChordFinder( detectorMagField );
   fAllocatedChordFinder= true;
}

