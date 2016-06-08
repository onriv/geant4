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
// $Id: G4StackManager.hh,v 1.5.4.1 2001/06/28 19:07:54 gunter Exp $
// GEANT4 tag $Name:  $
//
//


#ifndef G4StackManager_h
#define G4StackManager_h 1

#include "G4UserStackingAction.hh"
#include "G4StackedTrack.hh"
#include "G4TrackStack.hh"
#include "G4ClassificationOfNewTrack.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "globals.hh"
class G4StackingMessenger;
class G4VTrajectory;

// class description:
//
//  This is the manager class of handling stacks of G4Track objects.
// This class must be a singleton and be constructed by G4EventManager.
// Almost all methods must be invoked exclusively by G4EventManager.
// Especially, some Clear() methods MUST NOT be invoked by the user.
// Event abortion is handled by G4EventManager.
//
//  This G4StackingManager has three stacks, the urgent stack, the
// waiting stack, and the postpone to next event stack. The meanings
// of each stack is descrived in the Geant4 user's manual.
//
//  The only method the user can invoke is ReClassify(), which can
// be used from the user's concrete class of G4UserStackingAction.
//


class G4StackManager 
{
  public:
      G4StackManager();
      ~G4StackManager();

  private:
      const G4StackManager & operator=
                          (const G4StackManager &right);
      int operator==(const G4StackManager &right) const;
      int operator!=(const G4StackManager &right) const;

  public:
      G4int PushOneTrack(G4Track *newTrack, G4VTrajectory *newTrajectory = NULL);
      G4Track * PopNextTrack(G4VTrajectory**newTrajectory);
      G4int PrepareNewEvent();

  public: // with description
      void ReClassify();
      //  Send all tracks stored in the Urgent stack one by one to 
      // the user's concrete ClassifyNewTrack() method. This method
      // can be invoked from the user's G4UserStackingAction concrete
      // class, especially fron its NewStage() method. Be aware that
      // when the urgent stack becomes empty, all tracks in the waiting
      // stack are send to the urgent stack and then the user's NewStage()
      // method is invoked.

  private:
      G4UserStackingAction * userStackingAction;
      int verboseLevel;
      G4TrackStack * urgentStack;
      G4TrackStack * waitingStack;
      G4TrackStack * postponeStack;
      G4StackingMessenger* theMessenger;

  public:
      inline void clear()
      { 
        ClearUrgentStack();
        ClearWaitingStack();
      }
      inline void ClearUrgentStack()
      { urgentStack->clear(); }
      inline void ClearWaitingStack()
      { waitingStack->clear(); }
      inline void ClearPostponeStack()
      { postponeStack->clear(); }
      inline G4int GetNTotalTrack() const
      { return urgentStack->GetNTrack()
             + waitingStack->GetNTrack()
             + postponeStack->GetNTrack(); }
      inline G4int GetNUrgentTrack() const
      { return urgentStack->GetNTrack(); }
      inline G4int GetNWaitingTrack() const
      { return waitingStack->GetNTrack(); }
      inline G4int GetNPostponedTrack() const
      { return postponeStack->GetNTrack(); }
      inline void SetVerboseLevel( int const value )
      { verboseLevel = value; }
      inline void SetUserStackingAction(G4UserStackingAction* value)
      { 
	userStackingAction = value;
        if(userStackingAction) userStackingAction->SetStackManager(this);
      }

  private:
      inline G4ClassificationOfNewTrack 
      DefaultClassification(G4Track *aTrack)
      { 
        G4ClassificationOfNewTrack classification = fUrgent;
        if( aTrack->GetTrackStatus() == fPostponeToNextEvent )
        { classification = fPostpone; }
        return classification;
      }
};

#endif

