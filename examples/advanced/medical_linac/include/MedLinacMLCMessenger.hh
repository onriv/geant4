//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: MedLinacMLCMessenger.hh,v 1.3 2006/06/29 16:03:47 gunter Exp $
//
//
// Code developed by: M. Piergentili

#ifndef MedLinacMLCMessenger_h
#define MedLinacMLCMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MedLinacMLCDecorator;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;

//****************************************************************************

class MedLinacMLCMessenger: public G4UImessenger
{
  public:
    MedLinacMLCMessenger(MedLinacMLCDecorator* );
   ~MedLinacMLCMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);

  private:
    MedLinacMLCDecorator* MedLinacMLCDeco;
    
    G4UIdirectory*             MedLinacMLCDir;
    G4UIcmdWithAString* leafNameCmd;
    G4UIcmdWithADoubleAndUnit* positionCmd;
 };

//****************************************************************************
#endif
