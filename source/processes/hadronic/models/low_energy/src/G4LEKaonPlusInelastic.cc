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
// $Id: G4LEKaonPlusInelastic.cc,v 1.3.2.1 2001/06/28 19:14:06 gunter Exp $
// GEANT4 tag $Name:  $
//
 // Hadronic Process: Low Energy KaonPlus Inelastic Process
 // J.L. Chuma, TRIUMF, 05-Feb-1997
 // Last modified: 27-Mar-1997
 // Modified by J.L.Chuma 30-Apr-97: added originalTarget for CalculateMomenta
 
#include "G4LEKaonPlusInelastic.hh"
#include "Randomize.hh"
 
 G4VParticleChange *
  G4LEKaonPlusInelastic::ApplyYourself( const G4Track &aTrack,
                                        G4Nucleus &targetNucleus )
  {
    theParticleChange.Initialize( aTrack );
    
    const G4DynamicParticle *originalIncident = aTrack.GetDynamicParticle();
    if (originalIncident->GetKineticEnergy()<= 0.1*MeV) return &theParticleChange;
    
    // create the target particle
    
    G4DynamicParticle *originalTarget = targetNucleus.ReturnTargetParticle();
    G4double targetMass = originalTarget->GetDefinition()->GetPDGMass();
    G4ReactionProduct targetParticle( originalTarget->GetDefinition() );
    
    if( verboseLevel > 1 )
    {
      G4Material *targetMaterial = aTrack.GetMaterial();
      G4cout << "G4LEKaonPlusInelastic::ApplyYourself called" << G4endl;
      G4cout << "kinetic energy = " << originalIncident->GetKineticEnergy() << "MeV, ";
      G4cout << "target material = " << targetMaterial->GetName() << ", ";
      G4cout << "target particle = " << originalTarget->GetDefinition()->GetParticleName()
           << G4endl;
    }    
    G4ReactionProduct currentParticle( originalIncident->GetDefinition() );
    currentParticle.SetMomentum( originalIncident->GetMomentum() );
    currentParticle.SetKineticEnergy( originalIncident->GetKineticEnergy() );
    
    // Fermi motion and evaporation
    // As of Geant3, the Fermi energy calculation had not been Done
    
    G4double ek = originalIncident->GetKineticEnergy();
    G4double amas = originalIncident->GetDefinition()->GetPDGMass();
    
    G4double tkin = targetNucleus.Cinema( ek );
    ek += tkin;
    currentParticle.SetKineticEnergy( ek );
    G4double et = ek + amas;
    G4double p = sqrt( abs((et-amas)*(et+amas)) );
    G4double pp = currentParticle.GetMomentum().mag();
    if( pp > 0.0 )
    {
      G4ThreeVector momentum = currentParticle.GetMomentum();
      currentParticle.SetMomentum( momentum * (p/pp) );
    }
    
    // calculate black track energies
    
    tkin = targetNucleus.EvaporationEffects( ek );
    ek -= tkin;
    currentParticle.SetKineticEnergy( ek );
    et = ek + amas;
    p = sqrt( abs((et-amas)*(et+amas)) );
    pp = currentParticle.GetMomentum().mag();
    if( pp > 0.0 )
    {
      G4ThreeVector momentum = currentParticle.GetMomentum();
      currentParticle.SetMomentum( momentum * (p/pp) );
    }
    
    G4ReactionProduct modifiedOriginal = currentParticle;
    
    currentParticle.SetSide( 1 ); // incident always goes in forward hemisphere
    targetParticle.SetSide( -1 );  // target always goes in backward hemisphere
    G4bool incidentHasChanged = false;
    G4bool targetHasChanged = false;
    G4bool quasiElastic = false;
    G4FastVector<G4ReactionProduct,128> vec;  // vec will contain the secondary particles
    G4int vecLen = 0;
    vec.Initialize( 0 );
        
    const G4double cutOff = 0.1*MeV;
    if( currentParticle.GetKineticEnergy() > cutOff )
      Cascade( vec, vecLen,
               originalIncident, currentParticle, targetParticle,
               incidentHasChanged, targetHasChanged, quasiElastic );
    
    CalculateMomenta( vec, vecLen,
                      originalIncident, originalTarget, modifiedOriginal,
                      targetNucleus, currentParticle, targetParticle,
                      incidentHasChanged, targetHasChanged, quasiElastic );
    
    SetUpChange( vec, vecLen,
                 currentParticle, targetParticle,
                 incidentHasChanged );
    
    delete originalTarget;
    
    return &theParticleChange;    
  }
 
 void
  G4LEKaonPlusInelastic::Cascade(
   G4FastVector<G4ReactionProduct,128> &vec,
   G4int &vecLen,
   const G4DynamicParticle *originalIncident,
   G4ReactionProduct &currentParticle,
   G4ReactionProduct &targetParticle,
   G4bool &incidentHasChanged,
   G4bool &targetHasChanged,
   G4bool &quasiElastic )
  {
    // derived from original FORTRAN code CASKP by H. Fesefeldt (13-Sep-1987)
    //
    // K+ undergoes interaction with nucleon within a nucleus.  Check if it is
    // energetically possible to produce pions/kaons.  In not, assume nuclear excitation
    // occurs and input particle is degraded in energy. No other particles are produced.
    // If reaction is possible, find the correct number of pions/protons/neutrons
    // produced using an interpolation to multiplicity data.  Replace some pions or
    // protons/neutrons by kaons or strange baryons according to the average
    // multiplicity per Inelastic reaction.
    //
    const G4double mOriginal = originalIncident->GetDefinition()->GetPDGMass();
    const G4double etOriginal = originalIncident->GetTotalEnergy();
    const G4double targetMass = targetParticle.GetMass();
    G4double centerofmassEnergy = sqrt( mOriginal*mOriginal +
                                        targetMass*targetMass +
                                        2.0*targetMass*etOriginal );
    G4double availableEnergy = centerofmassEnergy-(targetMass+mOriginal);
    if( availableEnergy < G4PionPlus::PionPlus()->GetPDGMass() )
    {
      quasiElastic = true;
      return;
    }
    static G4bool first = true;
    const G4int numMul = 1200;
    const G4int numSec = 60;
    static G4double protmul[numMul], protnorm[numSec]; // proton constants
    static G4double neutmul[numMul], neutnorm[numSec]; // neutron constants
    // np = number of pi+, nm = number of pi-, nz = number of pi0
    G4int nt=0, np=0, nm=0, nz=0;
    const G4double c = 1.25;    
    const G4double b[] = { 0.70, 0.70 };
    if( first )       // compute normalization constants, this will only be Done once
    {
      first = false;
      G4int i;
      for( i=0; i<numMul; ++i )protmul[i] = 0.0;
      for( i=0; i<numSec; ++i )protnorm[i] = 0.0;
      G4int counter = -1;
      for( np=0; np<(numSec/3); ++np )
      {
        for( nm=G4std::max(0,np-2); nm<=np; ++nm )
        {
          for( nz=0; nz<numSec/3; ++nz )
          {
            if( ++counter < numMul )
            {
              nt = np+nm+nz;
              if( nt > 0 )
              {
                protmul[counter] = Pmltpc(np,nm,nz,nt,b[0],c);
                protnorm[nt-1] += protmul[counter];
              }
            }
          }
        }
      }
      for( i=0; i<numMul; ++i )neutmul[i] = 0.0;
      for( i=0; i<numSec; ++i )neutnorm[i] = 0.0;
      counter = -1;
      for( np=0; np<numSec/3; ++np )
      {
        for( nm=G4std::max(0,np-1); nm<=(np+1); ++nm )
        {
          for( nz=0; nz<numSec/3; ++nz )
          {
            if( ++counter < numMul )
            {
              nt = np+nm+nz;
              if( (nt>0) && (nt<=numSec) )
              {
                neutmul[counter] = Pmltpc(np,nm,nz,nt,b[1],c);
                neutnorm[nt-1] += neutmul[counter];
              }
            }
          }
        }
      }
      for( i=0; i<numSec; ++i )
      {
        if( protnorm[i] > 0.0 )protnorm[i] = 1.0/protnorm[i];
        if( neutnorm[i] > 0.0 )neutnorm[i] = 1.0/neutnorm[i];
      }
    }   // end of initialization
        
    const G4double expxu = 82.;           // upper bound for arg. of exp
    const G4double expxl = -expxu;        // lower bound for arg. of exp
    G4ParticleDefinition *aKaonZS = G4KaonZeroShort::KaonZeroShort();
    G4ParticleDefinition *aKaonZL = G4KaonZeroLong::KaonZeroLong();
    G4ParticleDefinition *aNeutron = G4Neutron::Neutron();
    G4ParticleDefinition *aProton = G4Proton::Proton();
    G4int ieab = static_cast<G4int>(availableEnergy*5.0/GeV);
    const G4double supp[] = {0.,0.4,0.55,0.65,0.75,0.82,0.86,0.90,0.94,0.98};
    G4double test, w0, wp, wt, wm;
    if( (availableEnergy < 2.0*GeV) && (G4UniformRand() >= supp[ieab]) )
    {
      // suppress high multiplicity events at low momentum
      // only one pion will be produced
      
      nm = np = nz = 0;
      if( targetParticle.GetDefinition() == aProton )
      {
        test = exp( G4std::min( expxu, G4std::max( expxl, -sqr(1.0+b[0])/(2.0*c*c) ) ) );
        w0 = test;
        wp = test*2.0;        
        if( G4UniformRand() < w0/(w0+wp) )
          nz = 1;
        else
          np = 1;
      }
      else  // target is a neutron
      {
        test = exp( G4std::min( expxu, G4std::max( expxl, -sqr(1.0+b[1])/(2.0*c*c) ) ) );
        w0 = test;
        wp = test;
        test = exp( G4std::min( expxu, G4std::max( expxl, -sqr(-1.0+b[1])/(2.0*c*c) ) ) );
        wm = test;
        wt = w0+wp+wm;
        wp += w0;
        G4double ran = G4UniformRand();
        if( ran < w0/wt )
          nz = 1;
        else if( ran < wp/wt )
          np = 1;
        else
          nm = 1;
      }
    }
    else
    {
      G4double n, anpn;
      GetNormalizationConstant( availableEnergy, n, anpn );
      G4double ran = G4UniformRand();
      G4double dum, excs = 0.0;
      if( targetParticle.GetDefinition() == aProton )
      {
        G4int counter = -1;
        for( np=0; (np<numSec/3) && (ran>=excs); ++np )
        {
          for( nm=G4std::max(0,np-2); (nm<=np) && (ran>=excs); ++nm )
          {
            for( nz=0; (nz<numSec/3) && (ran>=excs); ++nz )
            {
              if( ++counter < numMul )
              {
                nt = np+nm+nz;
                if( nt > 0 )
                {
                  test = exp( G4std::min( expxu, G4std::max( expxl, -(pi/4.0)*(nt*nt)/(n*n) ) ) );
                  dum = (pi/anpn)*nt*protmul[counter]*protnorm[nt-1]/(2.0*n*n);
                  if( fabs(dum) < 1.0 )
                  {
                    if( test >= 1.0e-10 )excs += dum*test;
                  }
                  else
                    excs += dum*test;
                }
              }
            }
          }
        }
        if( ran >= excs )return;  // 3 previous loops continued to the end
        np--; nm--; nz--;
      }
      else  // target must be a neutron
      {
        G4int counter = -1;
        for( np=0; (np<numSec/3) && (ran>=excs); ++np )
        {
          for( nm=G4std::max(0,np-1); (nm<=(np+1)) && (ran>=excs); ++nm )
          {
            for( nz=0; (nz<numSec/3) && (ran>=excs); ++nz )
            {
              if( ++counter < numMul )
              {
                nt = np+nm+nz;
                if( (nt>=1) && (nt<=numSec) )
                {
                  test = exp( G4std::min( expxu, G4std::max( expxl, -(pi/4.0)*(nt*nt)/(n*n) ) ) );
                  dum = (pi/anpn)*nt*neutmul[counter]*neutnorm[nt-1]/(2.0*n*n);
                  if( fabs(dum) < 1.0 )
                  {
                    if( test >= 1.0e-10 )excs += dum*test;
                  }
                  else
                    excs += dum*test;
                }
              }
            }
          }
        }
        if( ran >= excs )return;  // 3 previous loops continued to the end
        np--; nm--; nz--;
      }
    }
    if( targetParticle.GetDefinition() == aProton )
    {
      switch( np-nm )
      {
       case 1:
         if( G4UniformRand() < 0.5 )
         {
           if( G4UniformRand() < 0.5 )
             currentParticle.SetDefinitionAndUpdateE( aKaonZS );
           else
             currentParticle.SetDefinitionAndUpdateE( aKaonZL );
           incidentHasChanged = true;
         }
         else
         {
           targetParticle.SetDefinitionAndUpdateE( aNeutron );
           targetHasChanged = true;
         }
         break;
       case 2:
         if( G4UniformRand() < 0.5 )
           currentParticle.SetDefinitionAndUpdateE( aKaonZS );
         else
           currentParticle.SetDefinitionAndUpdateE( aKaonZL );
         incidentHasChanged = true;
         targetParticle.SetDefinitionAndUpdateE( aNeutron );
         incidentHasChanged = true;
         targetHasChanged = true;
         break;
       default:
         break;
      }
    }
    else   // target is a neutron
    {
      switch( np-nm )
      {
       case 0:
         if( G4UniformRand() < 0.25 )
         {
           if( G4UniformRand() < 0.5 )
             currentParticle.SetDefinitionAndUpdateE( aKaonZS );
           else
             currentParticle.SetDefinitionAndUpdateE( aKaonZL );
           targetParticle.SetDefinitionAndUpdateE( aProton );
           incidentHasChanged = true;
           targetHasChanged = true;
         }
         break;
       case 1:
         if( G4UniformRand() < 0.5 )
           currentParticle.SetDefinitionAndUpdateE( aKaonZS );
         else
           currentParticle.SetDefinitionAndUpdateE( aKaonZL );
         incidentHasChanged = true;
         break;
       default: // assumes nm = np+1 so charge is conserved
         targetParticle.SetDefinitionAndUpdateE( aProton );
         targetHasChanged = true;
         break;
      }
    }
    SetUpPions( np, nm, nz, vec, vecLen );
    return;
  }

 /* end of file */
 
