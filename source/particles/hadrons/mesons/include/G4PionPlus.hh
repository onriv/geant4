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
// $Id: G4PionPlus.hh,v 1.4.2.2 2001/06/28 20:19:04 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      History: first implementation, based on object model of
//      4-th April 1996, G.Cosmo
// ****************************************************************
//  Added particle definitions, H.Kurashige, 19 April 1996
//  Revised, G.Cosmo, 6 June 1996
//  Added not static GetEnergyCuts() and GetLengthCuts(), G.Cosmo, 11 July 1996
// ----------------------------------------------------------------

// Each class inheriting from G4VMeson
// corresponds to a particle type; one and only one
// instance for each class is guaranteed.

#ifndef G4PionPlus_h
#define G4PionPlus_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VMeson.hh"

// ######################################################################
// ###                         PIONPLUS                               ###
// ######################################################################

class G4PionPlus : public G4VMeson
{
 private:
   static G4PionPlus thePionPlus;
   static G4double  thePionPlusLengthCut;
   static G4double* thePionPlusKineticEnergyCuts;

 private:
   G4PionPlus(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable
   );

 public:
   virtual ~G4PionPlus(){}

   static G4PionPlus* PionPlusDefinition();
   static G4PionPlus* PionPlus() {return &thePionPlus;}
   static G4double GetCuts() {return thePionPlusLengthCut;}   
   static G4double* GetCutsInEnergy() {return thePionPlusKineticEnergyCuts;};

   void SetCuts(G4double aCut); 
   virtual void RestoreCuts(G4double cutInLength,
			    const G4double* cutInEnergy );
};

inline void G4PionPlus::SetCuts(G4double aCut)
{
  G4ParticleWithCuts::SetCuts(aCut);
  thePionPlusLengthCut = theCutInMaxInteractionLength;  
  thePionPlusKineticEnergyCuts = theKineticEnergyCuts;
}

inline void G4PionPlus::RestoreCuts(G4double cutInLength,
			    const G4double* cutInEnergy )
{
  G4ParticleWithCuts::RestoreCuts(cutInLength, cutInEnergy);
  thePionPlusLengthCut = theCutInMaxInteractionLength;  
  thePionPlusKineticEnergyCuts = theKineticEnergyCuts;
}


#endif
