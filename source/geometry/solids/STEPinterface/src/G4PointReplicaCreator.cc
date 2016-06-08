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
// $Id: G4PointReplicaCreator.cc,v 1.2.4.1 2001/06/28 19:09:19 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
// ----------------------------------------------------------------------
// Class G4PointReplicaCreator
//
// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------

#include "G4PointReplicaCreator.hh"
#include "G4GeometryTable.hh"

G4PointReplicaCreator G4PointReplicaCreator::csc;

G4PointReplicaCreator::G4PointReplicaCreator()
{
  G4GeometryTable::RegisterObject(this);
}

G4PointReplicaCreator::~G4PointReplicaCreator() {}

void G4PointReplicaCreator::CreateG4Geometry(STEPentity& Ent) {}

void G4PointReplicaCreator::CreateSTEPGeometry(void* G4obj) {}
