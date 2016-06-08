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
// **********************************************************************
// *                                                                    *
// *                    GEANT 4 xray_telescope advanced example         *
// *                                                                    *
// * MODULE:            XrayTelSteppingAction.hh                        *
// * -------                                                            *
// *                                                                    *
// * Version:           0.4                                             *
// * Date:              06/11/00                                        *
// * Author:            R Nartallo                                      *
// * Organisation:      ESA/ESTEC, Noordwijk, THe Netherlands           *
// *                                                                    *
// **********************************************************************
//
// CHANGE HISTORY
// --------------
//
// 06.11.2000 R.Nartallo
// - First implementation of X-ray Telescope advanced example.
// - Based on Chandra and XMM models
//
//
// **********************************************************************

#ifndef XrayTelSteppingAction_h
#define XrayTelSteppingAction_h 1

class XrayTelAnalysisManager;

#include "G4UserSteppingAction.hh"
#include "G4ThreeVector.hh"
#include "g4std/vector"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class XrayTelSteppingAction : public G4UserSteppingAction
{
public:
  XrayTelSteppingAction(  
			G4std::vector<G4double*> *enEnergy, 
			G4std::vector<G4ThreeVector*> *enDirect,
			G4bool* dEvent,
			XrayTelAnalysisManager* = 0);
  virtual ~XrayTelSteppingAction();

  virtual void UserSteppingAction(const G4Step*);
  
private:
  G4bool* drawEvent;
  G4std::vector<G4double*>* enteringEnergy;
  G4std::vector<G4ThreeVector*>* enteringDirection;

  XrayTelAnalysisManager* fAnalysisManager;
};

#endif
