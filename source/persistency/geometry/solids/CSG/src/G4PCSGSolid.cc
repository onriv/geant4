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
// $Id: G4PCSGSolid.cc,v 1.2.8.1 2001/06/28 19:11:32 gunter Exp $
// GEANT4 tag $Name:  $
//
//
// History:
// 19.06.98 A.Kimura Converted G4CSGSolid.cc

#include "G4PCSGSolid.hh"

// Constructor
//  - Base class constructor 

G4PCSGSolid::G4PCSGSolid(const G4String& name) :
   G4PVSolid(name)
{;}

G4PCSGSolid::~G4PCSGSolid() 
{;}
