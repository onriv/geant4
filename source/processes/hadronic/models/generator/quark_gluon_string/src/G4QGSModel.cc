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
#include "G4QGSModel.hh"
#include <stdlib.h>

//****************************************************************************************************************
G4QGSModel::G4QGSModel() 
    {
	G4VPartonStringModel::SetThisPointer(this);
    }
G4QGSModel::G4QGSModel(const G4QGSModel &right)
    {
	G4VPartonStringModel::SetThisPointer(this);
    }
G4QGSModel::~G4QGSModel()
    {
    }

void G4QGSModel::Init(const G4Nucleus & aNucleus, const G4DynamicParticle & aProjectile)
    {
     // clean-up and consistency with design, HPW Feb 1999
    theParticipants.Init(aNucleus.GetN(),aNucleus.GetZ());
    theCurrentVelocity.setX(0);    
    theCurrentVelocity.setY(0); 
     // HPW Feb 1999 
     // this is an approximation, neglecting the motion of nucleons in the nucleus & p,n mass differences. @@@
    G4double vz = aProjectile.Get4Momentum().pz()/
                  (aProjectile.Get4Momentum().e() + G4Proton::Proton()->GetPDGMass());
//--DEBUG--    cout << "IncomingMomentum "<<aProjectile.Get4Momentum()<<G4endl;
    theCurrentVelocity.setZ(vz);
    theParticipants.GetWoundedNucleus()->DoLorentzBoost(-theCurrentVelocity); 
    G4LorentzVector Mom = aProjectile.Get4Momentum();
    Mom.boost(-theCurrentVelocity);
    G4ReactionProduct theProjectile;   
    theProjectile.SetDefinition(aProjectile.GetDefinition());
    theProjectile.SetTotalEnergy(Mom.e());
    theProjectile.SetMomentum(Mom);
//--DEBUG--    cout << "PreInteractionMomentum "<<Mom<<G4endl;
    theParticipants.BuildInteractions(theProjectile);
    theParticipants.GetWoundedNucleus()->DoLorentzBoost(theCurrentVelocity);
    }

G4ExcitedStringVector * G4QGSModel::GetStrings()
{
  // clean-up and consistancy with design, HPW Feb 1999
  // also fixing a memory leak, removing unnecessary caching, and 
  // streamlining of logic
  G4PartonPair* aPair;
  G4ExcitedStringVector* theStrings = new G4ExcitedStringVector;
  G4ExcitedString * aString;
  while(aPair = theParticipants.GetNextPartonPair())
  {
    if (aPair->GetCollisionType() == G4PartonPair::DIFFRACTIVE)
    {
      aString = theDiffractiveStringBuilder.BuildString(aPair);
//      G4cout << "diffractive "<<aString->Get4Momentum()<<endl;
    }
    else
    {
      aString = theSoftStringBuilder.BuildString(aPair);
//      G4cout << "soft "<<aString->Get4Momentum()<<endl;
    }
    aString->Boost(theCurrentVelocity);  
    theStrings->insert(aString);
    delete aPair;
  }
//--DEBUG--  cout << G4endl;
  for(G4int i=0; i<theStrings->length(); i++)
  {
//   cout << "String = "<<theStrings->at(i)->Get4Momentum()<<G4endl;
  }
  return theStrings;
}

G4V3DNucleus* G4QGSModel::GetWoundedNucleus() const
{
  return theParticipants.GetWoundedNucleus();
}
 

//********************************************************************************************************************* 

