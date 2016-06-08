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
// $Id: G4SimpleIntegration.hh,v 1.2.8.1 2001/06/28 19:09:52 gunter Exp $
// GEANT4 tag $Name:  $
//
// Class description:
//
// Class for realisation of simple numerical methodes for integration of functions
// with signature: double f(double). The methods based mainly on algorithms given in
// the book : An introduction to NUMERICAL METHODS IN C++, B.H. Flowers, Claredon
// Press, Oxford, 1995
//
// --------------------------- Member data: -------------------------------------
//
//           fFunction       - pointer to the function to be integrated
//           fTolerance      - accuracy of integration in Adaptive Gauss method
//           fMaxDepth = 100 - constant maximum iteration depth for
//                             Adaptive Gauss method
//
// --------------------------- Methods: -----------------------------------------
//
//          Trapezoidal, MidPoint, Gauss,
//          and Simpson(double a,double b,int n) - integrate function pointed 
//          by fFunction from a to b by n iterations, i.e. with Step (b-a)/n 
//          according to the correspondent method
//
//  AdaptGausIntegration(double a, double b) - integrate function from a to be with
//                                             accuracy <= fTolerance 

// ----------------------------- History: ---------------------------------------- 
//
//  26.03.97   V.Grichine ( Vladimir.Grichine@cern.ch )

#ifndef G4SIMPLEINTEGRATION_HH
#define G4SIMPLEINTEGRATION_HH

#include "globals.hh"

typedef G4double (*function)(G4double) ;

class G4SimpleIntegration
{
public:
       G4SimpleIntegration( function pFunction ) ;
       
       G4SimpleIntegration( function pFunction,
                            G4double pTolerance ) ;
       
      ~G4SimpleIntegration() ;
       
       // Simple integration methods
       
       G4double Trapezoidal(G4double xInitial,
                            G4double xFinal,
			    G4int iterationNumber ) ;

       G4double    MidPoint(G4double xInitial,
                            G4double xFinal,
			    G4int iterationNumber ) ;

       G4double       Gauss(G4double xInitial,
                            G4double xFinal,
			    G4int iterationNumber ) ;

       G4double     Simpson(G4double xInitial,
                            G4double xFinal,
			    G4int iterationNumber ) ;

       // Adaptive Gauss integration with accuracy ~ fTolerance
       
       G4double       AdaptGaussIntegration( G4double xInitial,
                                             G4double xFinal   ) ;
       
 			    
protected:
       G4double       Gauss( G4double xInitial,
                             G4double xFinal   ) ;

       void      AdaptGauss( G4double xInitial,
                             G4double xFinal,
			     G4double& sum,
			     G4int& depth      ) ;

private:

        function fFunction ;
	G4double fTolerance ;
	static G4int fMaxDepth ;
} ;

#endif
