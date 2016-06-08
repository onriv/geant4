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
// $Id: G4UIbatch.cc,v 1.3.2.1 2001/06/28 19:10:17 gunter Exp $
// GEANT4 tag $Name:  $
//

#include "G4UIbatch.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"

G4UIbatch::G4UIbatch(G4String fileName,G4UIsession* prevSession) 
 : previousSession(prevSession), macroFileName(fileName),
   openFailed(false)
{
  const char* theFileName = fileName;
  UImanager = G4UImanager::GetUIpointer();
  UImanager->SetSession(this);
  macroFile.open((char*)theFileName);
  if(macroFile.fail())
  {
    G4cerr << "macro file <" << fileName << "> could not open."
         << G4endl;
    openFailed = true;
  }
}

G4UIbatch::~G4UIbatch() 
{
  if(!openFailed) macroFile.close();
}

G4UIsession * G4UIbatch::SessionStart() 
{
  if(!openFailed)
  {
    char commandLine[256];
    int lineLength = 255;

    while(1)
    {
      macroFile.getline( commandLine, lineLength );
      if( macroFile.bad() )
      {
        G4cout << "Cannot read " << macroFileName << "." << G4endl;
        break;
      }
      if( macroFile.eof() ) break;
      commandLine[lineLength] = '\0';
      if( commandLine[0] != '#' )
      { UImanager->ApplyCommand(commandLine); }
      else
      { G4cout << commandLine << G4endl; }
    }
  }
  return previousSession;
}

void G4UIbatch::PauseSessionStart(G4String Prompt) 
{
  G4cout << "Pause session <" << Prompt << "> start." << G4endl;
  SessionStart();
  G4cout << "Pause session <" << Prompt << "> Terminate." << G4endl;
}


