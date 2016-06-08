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
// $Id: G4GraphicsSystemList.cc,v 1.2.2.1 2001/06/28 19:16:13 gunter Exp $
// GEANT4 tag $Name:  $

#include "G4GraphicsSystemList.hh"

void G4GraphicsSystemList::remove(G4VGraphicsSystem* graphicsSystem) {
  G4GraphicsSystemListIterator iGS;
  for (iGS = begin(); iGS != end(); ++iGS) {
    if (*iGS == graphicsSystem) break;
  }
  if (iGS != end()) erase(iGS);
}
