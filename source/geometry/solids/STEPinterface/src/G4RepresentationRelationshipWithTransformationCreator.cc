#include "G4RepresentationRelationshipWithTransformationCreator.hh"

G4RepresentationRelationshipWithTransformationCreator G4RepresentationRelationshipWithTransformationCreator::csc;

G4RepresentationRelationshipWithTransformationCreator::G4RepresentationRelationshipWithTransformationCreator(){G4GeometryTable::RegisterObject(this);}

G4RepresentationRelationshipWithTransformationCreator::~G4RepresentationRelationshipWithTransformationCreator(){}

void G4RepresentationRelationshipWithTransformationCreator::CreateG4Geometry(STEPentity& Ent)
{

}

void G4RepresentationRelationshipWithTransformationCreator::CreateSTEPGeometry(void * G4obj)
{

}