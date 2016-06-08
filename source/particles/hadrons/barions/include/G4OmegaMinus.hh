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
// $Id: G4OmegaMinus.hh,v 1.4.4.2 2001/06/28 20:18:57 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      History: first implementation, based on object model of
//      4-th April 1996, G.Cosmo
// ****************************************************************
//  Added particle definitions, H.Kurashige, 14 Feb 19
// ----------------------------------------------------------------

// Each class inheriting from G4VBaryon
// corresponds to a particle type; one and only one
// instance for each class is guaranteed.

#ifndef G4OmegaMinus_h
#define G4OmegaMinus_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VBaryon.hh"

// ######################################################################
// ###                          OmegaMinus                            ###
// ######################################################################

class G4OmegaMinus : public G4VBaryon
{
 private:
   static G4OmegaMinus theOmegaMinus;
   static G4double  theOmegaMinusLengthCut;
   static G4double* theOmegaMinusKineticEnergyCuts;

 private:
   G4OmegaMinus(
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
   virtual  ~G4OmegaMinus(){}
 
   static G4OmegaMinus* OmegaMinusDefinition();
   static G4OmegaMinus* OmegaMinus() {return &theOmegaMinus;}
   static G4double GetCuts() {return theOmegaMinusLengthCut;}   
   static G4double* GetCutsInEnergy() {return theOmegaMinusKineticEnergyCuts;};

   virtual void SetCuts(G4double aCut); 
};

inline void G4OmegaMinus::SetCuts(G4double aCut)
{
  CalcEnergyCuts(aCut);
  theOmegaMinusLengthCut = theCutInMaxInteractionLength;  
  theOmegaMinusKineticEnergyCuts = theKineticEnergyCuts;
  
}


#endif
