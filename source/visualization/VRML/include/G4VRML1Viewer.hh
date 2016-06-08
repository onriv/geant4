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
// $Id: G4VRML1Viewer.hh,v 1.4.4.1 2001/06/28 19:16:01 gunter Exp $
// GEANT4 tag $Name:  $
//
// G4VRML1Viewer.hh
// Satoshi Tanaka & Yasuhide Sawada

#ifdef  G4VIS_BUILD_VRML_DRIVER

#ifndef G4VRML1_VIEWER_HH
#define G4VRML1_VIEWER_HH

#include "G4VViewer.hh"
#include "globals.hh"

class G4VRML1SceneHandler;

class G4VRML1Viewer: public G4VViewer {
public:
	G4VRML1Viewer(G4VRML1SceneHandler& scene, const G4String& name = "");
	virtual ~G4VRML1Viewer();
	void ClearView();
	void DrawView();
	void ShowView();
	void FinishView();
private:
	void SetView();

private:
	G4VRML1SceneHandler& fSceneHandler; // Reference to Graphics Scene for this view.
};

#endif //G4VRML1_VIEW_HH
#endif //G4VIS_BUILD_VRML_DRIVER
