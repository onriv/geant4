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
//    ********************************
//    *                              *
//    *     BrachyWaterBoxHit.cc     *
//    *                              *
//    ********************************

#include "BrachyWaterBoxHit.hh"
#include "G4ios.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

G4Allocator<BrachyWaterBoxHit> BrachyWaterBoxHitAllocator;

//....

BrachyWaterBoxHit::BrachyWaterBoxHit(G4LogicalVolume* logVol,G4int XID,G4int ZID)
:m_pLogV(logVol),m_XID(XID),m_ZID(ZID)
{
 m_Edep=0;
}

//....

BrachyWaterBoxHit::~BrachyWaterBoxHit()
{
}

//....

BrachyWaterBoxHit::BrachyWaterBoxHit(const BrachyWaterBoxHit &right)
{
 m_XID = right.m_XID;
 m_ZID = right.m_ZID;
 m_Edep = right.m_Edep;
 m_Pos = right.m_Pos;
 m_Rot = right.m_Rot;
 m_pLogV = right.m_pLogV;
}

//....

const BrachyWaterBoxHit& BrachyWaterBoxHit::operator=(const BrachyWaterBoxHit &right)
{
 m_XID = right.m_XID;
 m_ZID = right.m_ZID;
 m_Edep = right.m_Edep;
 m_Pos = right.m_Pos;
 m_Rot = right.m_Rot;
 m_pLogV = right.m_pLogV;
 return *this;
}

//....

int BrachyWaterBoxHit::operator==(const BrachyWaterBoxHit &right) const
{
 return((m_XID==right.m_XID)&&(m_ZID==right.m_ZID));
}

//....

void BrachyWaterBoxHit::Draw()
{
}

//....

void BrachyWaterBoxHit::Print()
{
}
