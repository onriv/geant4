// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4HadronElasticDataSet.hh,v 2.0 1998/07/02 16:21:41 gunter Exp $
// GEANT4 tag $Name: geant4-00 $
//
//
// GEANT4 physics class: G4HadronElasticDataSet -- header file
// F.W. Jones, TRIUMF, 28-JAN-97
//

#ifndef G4HadronElasticDataSet_h
#define G4HadronElasticDataSet_h 1

#include "G4VCrossSectionDataSet.hh"
#include "G4HadronCrossSections.hh"
#include "G4DynamicParticle.hh"
#include "G4Element.hh"


class G4HadronElasticDataSet : public G4VCrossSectionDataSet
{
public:

   G4HadronElasticDataSet()
   {
      theHadronCrossSections = G4HadronCrossSections::Instance();
   }

   ~G4HadronElasticDataSet()
   {
   }

   G4bool IsApplicable(const G4DynamicParticle* aParticle,
                       const G4Element* anElement)
   {
      return theHadronCrossSections->IsApplicable(aParticle, anElement);
   }

   G4double GetCrossSection(const G4DynamicParticle* aParticle,
                            const G4Element* anElement)
   {
      return theHadronCrossSections->GetElasticCrossSection(aParticle,
                                                              anElement);
   }

   void BuildPhysicsTable(const G4ParticleDefinition&)
   {
   }

   void DumpPhysicsTable(const G4ParticleDefinition&)
   {
   }

private:

   G4HadronCrossSections* theHadronCrossSections;
};

#endif