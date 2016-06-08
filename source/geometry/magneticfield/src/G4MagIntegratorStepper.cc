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
// $Id: G4MagIntegratorStepper.cc,v 1.5.2.1 2001/06/28 19:08:20 gunter Exp $
// GEANT4 tag $Name:  $
//
#include "G4MagIntegratorStepper.hh"

// Constructor for stepper abstract base class. 
// 

G4MagIntegratorStepper::G4MagIntegratorStepper(G4EquationOfMotion* Equation,
					       G4int       num_var)
  : fEquation_Rhs(Equation),
    fNumberOfVariables(num_var)
{
}

G4MagIntegratorStepper::~G4MagIntegratorStepper()
{
}

void G4MagIntegratorStepper::RightHandSide( const  double y[], double dydx[] )   
{
  fEquation_Rhs-> RightHandSide(y, dydx);
}
