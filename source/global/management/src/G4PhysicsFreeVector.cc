// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4PhysicsFreeVector.cc,v 2.0 1998/07/02 17:33:22 gunter Exp $
// GEANT4 tag $Name: geant4-00 $
//
// 
//--------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//  G4PhysicsFreeVector.cc
//
//  History:
//    02 Dec. 1995, G.Cosmo : Structure created based on object model
//    06 June 1996, K.Amako : The 1st version of implemented.
//    01 Jul. 1996, K.Amako : Cache mechanism and hidden bin from the 
//                            user introduced.
//    26 Sep. 1996, K.Amako : Constructor with only 'bin size' added.
//
//--------------------------------------------------------------------

#include "G4PhysicsFreeVector.hh"


G4PhysicsFreeVector::G4PhysicsFreeVector()
{
  ptrNextTable = 0;
  edgeMin = 0.0;
  edgeMax = 0.0;
  numberOfBin = 0;
}


G4PhysicsFreeVector::G4PhysicsFreeVector(size_t theNbin)
{
  numberOfBin = theNbin;

  // Add extra one bin (hidden to user) to handle correctly when 
  // Energy=theEmax in getValue.
  dataVector.resize(numberOfBin+1);
  binVector.resize(numberOfBin+1);

  ptrNextTable = 0;

  edgeMin = 0.;
  edgeMax = 0.;

  lastBin = INT_MAX;
  lastEnergy = -DBL_MAX;
  lastValue = DBL_MAX;

}  


G4PhysicsFreeVector::G4PhysicsFreeVector(const G4DataVector& theBinVector, 
                                         const G4DataVector& theDataVector)
{
  numberOfBin = theBinVector.entries();

  // Add extra one bin (hidden to user) to handle correctly when 
  // Energy=theEmax in getValue.
  dataVector.resize(numberOfBin+1);
  binVector.resize(numberOfBin+1);

  ptrNextTable = 0;

  for (int i=0; i<numberOfBin; i++) {
     binVector(i) = theBinVector(i);
     dataVector(i) = theDataVector(i);
  }

  // Put values to extra hidden bin. For 'binVector', the 'edgeMin' of the
  // extra hidden bin is assumed to have the following value. For binary
  // search, this value is completely arbitrary if it is greater than
  // the 'edgeMin' at 'numberOfBin-1'. 
  binVector(numberOfBin) = theBinVector(numberOfBin-1) + 1.0;


  // Put values to extra hidden bin. For 'dataVector', the 'value' of the
  // extra hidden bin is assumed to have the same as the one at 'numberBin-1'. 
  dataVector(numberOfBin) = theDataVector(numberOfBin-1);

  edgeMin = binVector(0);
  edgeMax = binVector(numberOfBin-1);

  lastBin = INT_MAX;
  lastEnergy = -DBL_MAX;
  lastValue = DBL_MAX;

}  


G4PhysicsFreeVector::~G4PhysicsFreeVector(){}


void G4PhysicsFreeVector::PutValue( size_t theBinNumber, G4double theBinValue, 
			            G4double theDataValue )
{
  binVector(theBinNumber)  = theBinValue;
  dataVector(theBinNumber) = theDataValue;


  if( theBinNumber == numberOfBin-1 ) {
     edgeMax = binVector(numberOfBin-1);

     // Put values to extra hidden bin. For 'binVector', the 'edgeMin' 
     // of the extra hidden bin is assumed to have the following value. 
     // For binary search, this value is completely arbitrary if it is 
     // greater than the 'edgeMin' at 'numberOfBin-1'. 
     binVector(numberOfBin) = theBinValue + 1.0;

     // Put values to extra hidden bin. For 'dataVector', the 'value' 
     // of the extra hidden bin is assumed to have the same as the one 
     // at 'numberBin-1'. 
     dataVector(numberOfBin) = theDataValue;
  }

  if( theBinNumber == 0 ) {
     edgeMin = binVector(0);
  }
}






