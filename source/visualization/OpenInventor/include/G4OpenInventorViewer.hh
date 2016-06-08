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
// $Id: G4OpenInventorViewer.hh,v 1.7.2.1 2001/06/28 19:15:48 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
// Jeff Kallenbach 01 Aug 1996
// OpenInventor viewer - opens window, hard copy, etc.

#ifndef G4OPENINVENTORVIEWER_HH
#define G4OPENINVENTORVIEWER_HH

#ifdef G4VIS_BUILD_OI_DRIVER

#include <Inventor/Xt/SoXt.h>

#include "G4VViewer.hh"

class SoXtComponent;
class SoSelection;
class SoWindow;
class G4OpenInventorSceneHandler;
class G4VInteractorManager;

//
// Base class for various OpenInventorView classes.
//
class G4OpenInventorViewer: public G4VViewer {

public:
  G4OpenInventorViewer (G4OpenInventorSceneHandler& scene,
			const G4String& name = "");
  virtual ~G4OpenInventorViewer ();
  void DrawView ();
  void ShowView ();
private:
  void ClearView           ();
  void FinishView          ();
  void SetView             ();
  void KernelVisitDecision ();

  G4OpenInventorSceneHandler&	fSceneHandler; 	// Graphics Scene for this view.
  Widget fShell;
  SoWindow* fWindow;
  SoXtComponent* fViewer;	  // The Inventor Viewer
  SoSelection* fSelection;
  G4VInteractorManager* fInteractorManager;
};

#endif

#endif


