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
// $Id: G4OpenGLXmTextField.cc,v 1.5.2.1 2001/06/28 19:15:46 gunter Exp $
// GEANT4 tag $Name:  $
//
//Text field class. Inherits from G4OpenGLXmVWidgetComponent

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#include "G4OpenGLXmVWidgetComponent.hh"
#include "G4OpenGLXmVWidgetContainer.hh"
#include "G4OpenGLXmTextField.hh"
#include <X11/Intrinsic.h>
#include "globals.hh"

G4OpenGLXmTextField::G4OpenGLXmTextField (const char* n,
					  G4double* val)
{
  name = n;
  initial = new char[50];
  sprintf (initial, "%6.2f", *val);
  value = (void*)val;
  text=false;
}

G4OpenGLXmTextField::G4OpenGLXmTextField (const char* n,
					  const char* val)
{
  name = n;
  initial = new char[50];
  sprintf (initial, "%s", val);
  value = (void*)val;
  text=true;
  //  strcpy (initial, val);
}

G4OpenGLXmTextField::~G4OpenGLXmTextField ()
{
  delete[] initial;
}

void G4OpenGLXmTextField::SetName (const char* n) 
{
  name = n;
  XmString text_string = XmStringCreateLocalized ((char*)name);
  XtVaSetValues (text_label,
		 XmNlabelString, text_string,
		 NULL);
  XmStringFree (text_string);
}

const char* G4OpenGLXmTextField::GetName () 
{
  return name;
}

void G4OpenGLXmTextField::SetValue (G4double val)
{
  sprintf (initial, "%6.2f", val);
  
  XtVaSetValues (text_field,
		 XmNvalue, (String)initial,
		 NULL);
  
}

void G4OpenGLXmTextField::SetValue (const char* val)
{
  sprintf (initial, "%s", val);
  //  strcpy (initial, val);

  XtVaSetValues (text_field,
		 XmNvalue, (String)initial,
		 NULL);
  
}

const char* G4OpenGLXmTextField::GetValue ()
{
  return initial;
}

void G4OpenGLXmTextField::AddYourselfTo (G4OpenGLXmVWidgetContainer* container)
{

  pView = container->GetView ();
  ProcesspView ();
  parent = container->GetPointerToWidget ();

  char local_w_text[50];
  strcpy (local_w_text, name);

  char label_name[50];
  strcpy (label_name, name);
  strcat (label_name, "_label");
  
  char text_field_name[50];
  strcpy (text_field_name, name);
  strcat (text_field_name, "_text_field");
  
  XmString local_text = XmStringCreateLocalized (local_w_text);
  text_label = XtVaCreateManagedWidget (label_name, 
					xmLabelWidgetClass,
					*parent,

					XmNlabelString, local_text,
					
					XtNvisual, visual, 
					XtNdepth, depth, 
					XtNcolormap, cmap, 
					XtNborderColor, borcol,
					XtNbackground, bgnd,
					
					NULL);
  XmStringFree (local_text);

  text_field = XtVaCreateManagedWidget (text_field_name,
					xmTextFieldWidgetClass,
					*parent,

					XmNvalue, (String)initial, 
					
					XtNvisual, visual, 
					XtNdepth, depth, 
					XtNcolormap, cmap, 
					XtNborderColor, borcol,
					XtNbackground, bgnd,
					
					NULL);

  if (!text) {
    XtAddCallback (text_field, 
		   XmNvalueChangedCallback,
		   G4OpenGLXmViewer::get_double_value_callback,
		   value);
  } else {
    XtAddCallback (text_field, 
		   XmNvalueChangedCallback,
		   G4OpenGLXmViewer::get_text_callback,
		   value);
  }
}

Widget* G4OpenGLXmTextField::GetPointerToParent ()
{
  return parent;
}

Widget* G4OpenGLXmTextField::GetPointerToWidget () 
{
  return &text_field;
}

#endif
