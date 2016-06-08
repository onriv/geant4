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
// $Id: PersEx02TrackerHitsCollection.cc,v 1.3.8.1 2001/06/28 19:07:26 gunter Exp $
// GEANT4 tag $Name:  $
//

#include "PersEx02TrackerHitsCollection.hh"


PersEx02TrackerHitsCollection::PersEx02TrackerHitsCollection
                                    (G4String dName, G4String aName)
 : G4PVHitsCollection(dName, aName), elems(0)
{;}

PersEx02TrackerHitsCollection::~PersEx02TrackerHitsCollection()
{;}

void PersEx02TrackerHitsCollection::DrawAllHits()
{;}

void PersEx02TrackerHitsCollection::PrintAllHits()
{;}

