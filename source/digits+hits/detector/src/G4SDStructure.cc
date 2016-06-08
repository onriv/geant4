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
// $Id: G4SDStructure.cc,v 1.4.2.1 2001/06/28 19:07:49 gunter Exp $
// GEANT4 tag $Name:  $
//

// G4SDStructure
#include "G4SDStructure.hh"
#include "G4ios.hh"

G4SDStructure::G4SDStructure(G4String aPath):verboseLevel(0)
{
  pathName = aPath;
  dirName = aPath;
  int i = dirName.length();
  if( i > 1 )
  {
    dirName.remove(i-1);
    int isl = dirName.last('/');
    dirName.remove(0,isl+1);
    dirName += "/";
  }
}

G4SDStructure::~G4SDStructure()
{
}

int G4SDStructure::operator==(const G4SDStructure &right) const
{
  return false;
}

void G4SDStructure::AddNewDetector(G4VSensitiveDetector*aSD, 
                                   G4String treeStructure)
{
  G4String remainingPath = treeStructure;
  remainingPath.remove(0,pathName.length());
  if( ! remainingPath.isNull() )
  {  // The detector should be kept in subdirectory.
     // First, check if the subdirectoy exists.
    G4String subD = ExtractDirName( remainingPath );
    G4SDStructure* tgtSDS = FindSubDirectory(subD);
    if( tgtSDS == NULL )
    { // Subdirectory not found. Create a new directory.
      subD.prepend(pathName);
      tgtSDS = new G4SDStructure(subD);
      structure.push_back( tgtSDS );
    }
    tgtSDS->AddNewDetector(aSD,treeStructure);
  }
  else
  { // The sensitive detector should be kept in this directory.
    G4VSensitiveDetector* tgtSD = GetSD( aSD->GetName() );
    if( tgtSD != NULL )
    {
      G4cout << aSD->GetName() << " had already stored in "
           << pathName << G4endl;
    }
    else
    {
      detector.push_back( aSD );
    }
  }
}

G4SDStructure* G4SDStructure::FindSubDirectory(G4String subD)
{
  for( int i=0; i<structure.size(); i++ )
  {
    if( subD == structure[i]->dirName ) return structure[i];
  } 
  return NULL;
}

G4VSensitiveDetector* G4SDStructure::GetSD(G4String aSDName)
{
  for( int i=0; i<detector.size(); i++ )
  {
    G4VSensitiveDetector* tgtSD = detector[i];
    if( aSDName == tgtSD->GetName() ) return tgtSD;
  }
  return NULL;
}

G4String G4SDStructure::ExtractDirName(G4String aName)
{
  G4String subD = aName;
  int i = aName.first('/');
  if( i != G4std::string::npos ) subD.remove(i+1);
  return subD;
}

void G4SDStructure::Activate(G4String aName, G4bool sensitiveFlag)
{
  G4String aPath = aName;
  aPath.remove(0,pathName.length());
  if( aPath.first('/') != G4std::string::npos )
  {  // Command is ordered for a subdirectory.
    G4String subD = ExtractDirName(aPath);
    G4SDStructure* tgtSDS = FindSubDirectory(subD);
    if( tgtSDS == NULL )
    {  // The subdirectory is not found
      G4cout << subD << " is not found in " << pathName << G4endl;
    }
    else
    { 
      tgtSDS->Activate(aName,sensitiveFlag);
    }
  }
  else if( aPath.isNull() )
  {  // Command is ordered for all detectors in this directory.
    for( int i=0; i<detector.size(); i++)
    { 
      detector[i]->Activate(sensitiveFlag);
    }
    for( int j=0;j<structure.size(); j++)
    {
      structure[j]->Activate(G4String("/"),sensitiveFlag);
    }
  }
  else
  {  // Command is ordered to a particular detector.
    G4VSensitiveDetector* tgtSD = GetSD(aPath);
    if( tgtSD == NULL )
    {  // The detector is not found.
      G4cout << aPath << " is not found in " << pathName << G4endl;
    }
    else
    {
      tgtSD->Activate(sensitiveFlag);
    }
  }
}

G4VSensitiveDetector* G4SDStructure::FindSensitiveDetector(G4String aName)
{
  G4String aPath = aName;
  aPath.remove(0,pathName.length());
  if( aPath.first('/') != G4std::string::npos )
  { // SD exists in sub-directory
    G4String subD = ExtractDirName(aPath);
    G4SDStructure* tgtSDS = FindSubDirectory(subD);
    if( tgtSDS == NULL )
    {  // The subdirectory is not found
      G4cout << subD << " is not found in " << pathName << G4endl;
      return NULL;
    }
    else
    {
      return tgtSDS->FindSensitiveDetector(aName);
    }
  }
  else
  { // SD must exist in this directory
    G4VSensitiveDetector* tgtSD = GetSD(aPath);
    if( tgtSD == NULL )
    {  // The detector is not found.
      G4cout << aPath << " is not found in " << pathName << G4endl;
    }
    return tgtSD;
  }
}

void G4SDStructure::Initialize(G4HCofThisEvent*HCE)
{
  int i;
  // Broadcast to subdirectories.
  for( i=0; i<structure.size(); i++ )
  {
    structure[i]->Initialize(HCE);
  }
  // Initialize all detectors in this directory.
  for( i=0; i<detector.size(); i++ )
  {
    if(detector[i]->isActive()) detector[i]->Initialize(HCE);
  }
}

void G4SDStructure::Terminate(G4HCofThisEvent*HCE)
{
  int i;
  // Broadcast to subdirectories.
  for( i=0; i<structure.size(); i++ )
  {
    structure[i]->Terminate(HCE);
  }
  // Initialize all detectors in this directory.
  for( i=0; i<detector.size(); i++ )
  {
    if(detector[i]->isActive()) detector[i]->EndOfEvent(HCE);
  }
}

void G4SDStructure::ListTree()
{
  G4cout << pathName << G4endl;
  for(int i=0; i<detector.size(); i++)
  {
    G4VSensitiveDetector* sd = detector[i];
    G4cout << pathName << sd->GetName();
    if( sd->isActive() )
    { G4cout << "   *** Active "; }
    else
    { G4cout << "   XXX Inactive "; }
    G4cout << G4endl;
  }
  for(int j=0; j<structure.size(); j++)
  { structure[j]->ListTree(); }
}
        

