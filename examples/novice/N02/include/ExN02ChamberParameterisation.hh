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
// $Id: ExN02ChamberParameterisation.hh,v 1.3.4.1 2001/06/28 19:07:27 gunter Exp $
// GEANT4 tag $Name:  $
//
//
//  A parameterisation that describes a series of boxes along Z
//    The boxes have equal width, & their lengths are a linear equation.
//    They are spaced an equal distance apart, starting from given location.
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

#ifndef ExN02ChamberParameterisation_H
#define ExN02ChamberParameterisation_H 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Box;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

class ExN02ChamberParameterisation : public G4VPVParameterisation
{ 
  public:
  
    ExN02ChamberParameterisation(G4int    NoChambers, 
                                 G4double startZ, 
                                 G4double spacing,
                                 G4double widthChamber, 
                                 G4double lengthInitial,
                                 G4double lengthFinal );
				 
   ~ExN02ChamberParameterisation();
   
    void ComputeTransformation (const G4int copyNo,
                                G4VPhysicalVolume* physVol) const;
    
    void ComputeDimensions (G4Box & trackerLayer, const G4int copyNo,
                            const G4VPhysicalVolume* physVol) const;


  private:

    G4int    fNoChambers;   
    G4double fStartZ;
    G4double fHalfWidth;    //  The half-width of each tracker chamber
    G4double fSpacing;      //  The distance between the chambers' center
    G4double fHalfLengthFirst;  //  The first half-length 
    G4double fHalfLengthIncr;   //  The Increment for the half-length 
};

#endif


