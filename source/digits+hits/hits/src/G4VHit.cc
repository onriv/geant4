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
// $Id: G4VHit.cc,v 1.2.2.1 2001/06/28 19:07:52 gunter Exp $
// GEANT4 tag $Name:  $
//

// G4VHit
#include "G4VHit.hh"
#include "globals.hh"

G4VHit::G4VHit()
{;}

G4VHit::~G4VHit()
{;}

int G4VHit::operator==(const G4VHit &right) const
{ return false; }

void G4VHit::Draw()
{;}

void G4VHit::Print()
{;}

