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
// $Id: G4FissionBarrier.hh,v 1.3.8.1 2001/06/28 19:13:02 gunter Exp $
// GEANT4 tag $Name:  $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Oct 1998)

#ifndef G4FissionBarrier_h
#define G4FissionBarrier_h 1

#include "G4VFissionBarrier.hh"
#include "globals.hh"
#include "G4CameronShellPlusPairingCorrections.hh"

class G4FissionBarrier : public G4VFissionBarrier
{
public:
  G4FissionBarrier() {};
  ~G4FissionBarrier() {};

private:
  G4FissionBarrier(const G4FissionBarrier & right);

  const G4FissionBarrier & operator=(const G4FissionBarrier & right);
  G4bool operator==(const G4FissionBarrier & right) const;
  G4bool operator!=(const G4FissionBarrier & right) const;
  
public:
  G4double FissionBarrier(const G4int A, const G4int Z, const G4double U);


private:

  G4double BarashenkovFissionBarrier(const G4int A, const G4int Z);
  
  G4double SellPlusPairingCorrection(const G4int Z, const G4int N)
  { return G4CameronShellPlusPairingCorrections::GetShellPlusPairingZ(Z) +
  			  G4CameronShellPlusPairingCorrections::GetShellPlusPairingN(N); 
	}

};

#endif
