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
// $Id: G4OpenGLImmediateWin32Viewer.hh,v 1.4.2.1 2001/06/28 19:15:37 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
// Class G4OpenGLImmediateWin32Viewer : a class derived from
//   G4OpenGLWin32Viewer and G4OpenGLImmediateViewer.

#ifdef G4VIS_BUILD_OPENGLWIN32_DRIVER

#ifndef G4OpenGLIMMEDIATEWIN32VIEWER_HH
#define G4OpenGLIMMEDIATEWIN32VIEWER_HH

#include "G4VViewer.hh"
#include "G4OpenGLImmediateViewer.hh"
#include "G4OpenGLWin32Viewer.hh"

#include "globals.hh"

class G4OpenGLImmediateSceneHandler;

class G4OpenGLImmediateWin32Viewer:
public G4OpenGLWin32Viewer, public G4OpenGLImmediateViewer{
  
public:
  G4OpenGLImmediateWin32Viewer (G4OpenGLImmediateSceneHandler& scene);
  void DrawView ();
};

#endif

#endif
