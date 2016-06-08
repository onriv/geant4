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
// $Id: G4VAnalysisSystem.hh,v 1.8.4.1 2001/06/28 19:07:47 gunter Exp $
// GEANT4 tag $Name:  $
//
// 

#ifndef G4VANALYSISSYSTEM_HH
#define G4VANALYSISSYSTEM_HH

#ifdef G4ANALYSIS_BUILD

#include "g4rw/cstring.h"

class IHistogram;
class IHistogramFactory;

#ifdef G4ANALYSIS_NON_AIDA
class ICloudFactory;
class ICloud;
class ITuple;
#endif

class G4VAnalysisSystem {
public:
  virtual ~G4VAnalysisSystem() {}
  virtual const G4String& GetName() const = 0;
  virtual IHistogramFactory* GetHistogramFactory() = 0;
  //
  virtual void Store(IHistogram* = 0,const G4String& = "") = 0;
  virtual void Plot(IHistogram*) = 0;
  //
#ifdef G4ANALYSIS_NON_AIDA
  virtual ICloudFactory* GetCloudFactory() = 0;
  virtual void Plot(ICloud*) = 0;
  virtual ITuple* CreateTuple(const G4String&,const G4String&) = 0;
#endif
};

#endif

#endif
