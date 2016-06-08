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
// $Id: G4VViewer.cc,v 1.13.2.1 2001/06/28 19:16:14 gunter Exp $
// GEANT4 tag $Name:  $
//
// 
// John Allison  27th March 1996
// Abstract interface class for graphics views.

#include "G4VViewer.hh"

#include "G4ios.hh"
#include "g4std/strstream"

#include "G4VisManager.hh"
#include "G4VGraphicsSystem.hh"
#include "G4VSceneHandler.hh"
#include "G4Scene.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Transform3D.hh"

G4VViewer::G4VViewer (G4VSceneHandler& sceneHandler,
		      G4int id, const G4String& name):
fSceneHandler (sceneHandler),
fViewId (id),
fModified (true),
fNeedKernelVisit (true)
{
  if (name == "") {
    char charname [50];
    G4std::ostrstream ost (charname, 50);
    ost << fSceneHandler.GetName () << '-' << fViewId << G4std::ends;
    fName = charname;
  }
  else {
    fName = name;
  }
  fShortName = fName (0, fName.find (' '));
  fShortName.strip ();

  G4VisManager* pVisMan = G4VisManager::GetInstance();
  G4double xHint = pVisMan->GetCurrentViewParameters().GetWindowSizeHintX();
  G4double yHint = pVisMan->GetCurrentViewParameters().GetWindowSizeHintY();
  fVP.SetWindowSizeHint(xHint,yHint);
  fDefaultVP.SetWindowSizeHint(xHint,yHint);
}

G4VViewer::~G4VViewer () {}

void G4VViewer::SetName (const G4String& name) {
  fName = name;
  fShortName = fName (0, fName.find (' '));
  fShortName.strip ();
}

const G4VisAttributes* G4VViewer::GetApplicableVisAttributes
(const G4VisAttributes* pVisAttribs) const {
  // If the pointer is null, pick up the default vis attributes from
  // the view parameters.
  if (!pVisAttribs)
    pVisAttribs = GetViewParameters ().GetDefaultVisAttributes ();
  return pVisAttribs;
}

void G4VViewer::NeedKernelVisit () {
  // Notify all views that a kernel visit is required.
  const G4ViewerList& viewerList = fSceneHandler.GetViewerList ();
  G4ViewerListConstIterator i;
  for (i = viewerList.begin(); i != viewerList.end(); i++) {
    (*i) -> SetNeedKernelVisit ();
  }
}

void G4VViewer::FinishView () {}

void G4VViewer::ShowView () {}

void G4VViewer::ProcessView () {

  // If view parameters have been modified, SetView () works out consequences. 
  if (fModified) {
    fModified = false;
    SetView ();
  }

  // If the scene data has changed (fNeedVisit is set to true in
  // G4VSceneHandler::SetSceneData), or if the concrete view has decided that it
  // necessary to visit the kernel (this should be Done in the concrete
  // object's DrawView ())...
  if (fNeedKernelVisit) {
    fSceneHandler.ProcessScene (*this);
    fNeedKernelVisit = false;
  }
}

void G4VViewer::SetViewParameters (const G4ViewParameters& vp) {
  fVP = vp;
  fModified = true;
}

G4std::ostream& operator << (G4std::ostream& os, const G4VViewer& v) {
  os << "View " << v.fName << ":\n";
  os << v.fVP;
  return os;
}
