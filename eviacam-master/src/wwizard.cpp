/////////////////////////////////////////////////////////////////////////////
// Name:        wwizard.cpp
// Purpose:     
// Author:      Cesar Mauri Loba
// Modified by: 
// Created:     Mon 18 Oct 2010 09:57:22 CEST
// RCS-ID:      
// Copyright:   (C) 2008-14 Cesar Mauri from CREA Sistemes Informatics
// Licence:     
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "wwizard.h"
#include "viacamcontroller.h"
#include "configmanager.h"
#include <wx/timer.h>
#include "crvcamera.h"
#include "eviacamapp.h"
#include "cautostart.h"
#include "pointeraction.h"
#include "dwellclick.h"
#include "paths.h"

////@begin XPM images
////@end XPM images

#define SINGLE 1
#define SECONDARY 2
#define DOUBLE 3
#define DRAG 4
#define THIRD 5

/*!
 * WWizard type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WWizard, wxWizard )


/*!
 * WWizard event table definition
 */

BEGIN_EVENT_TABLE( WWizard, wxWizard )

////@begin WWizard event table entries
    EVT_WIZARD_CANCEL( ID_WWIZARD, WWizard::OnWwizardCancel )
    EVT_WIZARD_FINISHED( ID_WWIZARD, WWizard::OnWwizardFinished )
////@end WWizard event table entries

END_EVENT_TABLE()


/*!
 * WWizard constructors
 */

WWizard::WWizard()
{
    Init();
}

WWizard::WWizard( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
    Init();
    Create(parent, id, pos);
}

/*!
 * WWizard creator
 */

bool WWizard::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
////@begin WWizard creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizard::Create( parent, id, _("DAATN Vision configuration wizard"), wizardBitmap, pos, wxDEFAULT_DIALOG_STYLE|wxCAPTION|wxCLOSE_BOX );

    CreateControls();
////@end WWizard creation
    return true;
}


/*!
 * WWizard destructor
 */

WWizard::~WWizard()
{
////@begin WWizard destruction
////@end WWizard destruction
}


/*!
 * Member initialisation
 */

void WWizard::Init()
{
////@begin WWizard member initialisation
////@end WWizard member initialisation
	m_performCalibration = true;
}


/*!
 * Control creation for WWizard
 */

void WWizard::CreateControls()
{    
////@begin WWizard content construction
    WWizard* itemWizard1 = this;

    WizardPage* itemWizardPageSimple2 = new WizardPage( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple2);

    WizardPage5* itemWizardPageSimple9 = new WizardPage5( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple9);

    WizardPage8* itemWizardPageSimple23 = new WizardPage8( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple23);

    WizardPage1* itemWizardPageSimple33 = new WizardPage1( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple33);

    WizardPage2* itemWizardPageSimple42 = new WizardPage2( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple42);

    WizardPage6* itemWizardPageSimple46 = new WizardPage6( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple46);

    WizardPage3* itemWizardPageSimple61 = new WizardPage3( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple61);

    WizardPage4* itemWizardPageSimple75 = new WizardPage4( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple75);

    wxWizardPageSimple* lastPage = NULL;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple2);
    lastPage = itemWizardPageSimple2;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple9);
    lastPage = itemWizardPageSimple9;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple23);
    lastPage = itemWizardPageSimple23;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple33);
    lastPage = itemWizardPageSimple33;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple42);
    lastPage = itemWizardPageSimple42;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple46);
    lastPage = itemWizardPageSimple46;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple61);
    lastPage = itemWizardPageSimple61;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple75);
    lastPage = itemWizardPageSimple75;
////@end WWizard content construction
}


/*!
 * Runs the wizard.
 */

bool WWizard::Run()
{
    wxWindowList::compatibility_iterator node = GetChildren().GetFirst();

    while (node)
    {
        wxWizardPage* startPage = wxDynamicCast(node->GetData(), wxWizardPage);
    
		if (startPage)
		{
			FinishLayout();
			ShowPage(startPage);
			Show(true);
			return true;
		}
		node = node->GetNext();
    }
	
    return false;
}


/*!
 * Should we show tooltips?
 */

bool WWizard::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WWizard::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WWizard bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WWizard bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WWizard::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WWizard icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WWizard icon retrieval
}

void WWizard::UpdateToggleButtonStatus (wxToggleButton& toggle)
{
	if (wxGetApp().GetController().GetEnabled()) {
		toggle.SetValue(true);
		toggle.SetLabel(_("Disable pointer control"));
	}
	else {
		toggle.SetValue(false);
		toggle.SetLabel(_("Enable pointer control"));
	}
}

void WWizard::OnToggleHeadTrackingClick (wxCommandEvent& event, wxToggleButton& toggle)
{
	bool isEnabled= wxGetApp().GetController().GetEnabled();
	wxGetApp().GetController().SetEnabled(!isEnabled, !isEnabled, this);
	UpdateToggleButtonStatus (toggle);
	event.Skip(false);
}

void WWizard::OnToggleHeadTrackingUpdate(wxUpdateUIEvent& event, wxToggleButton& toggle)
{
	if (wxGetApp().GetController().GetEnabled()!= toggle.GetValue()) {	
		UpdateToggleButtonStatus (toggle);
	}
	event.Skip(false);
}

/*!
 * WizardPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage, wxWizardPageSimple )


/*!
 * WizardPage event table definition
 */

BEGIN_EVENT_TABLE( WizardPage, wxWizardPageSimple )

////@begin WizardPage event table entries
////@end WizardPage event table entries

END_EVENT_TABLE()


/*!
 * WizardPage constructors
 */

WizardPage::WizardPage()
{
    Init();
}

WizardPage::WizardPage( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage creator
 */

bool WizardPage::Create( wxWizard* parent )
{
////@begin WizardPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage creation
    return true;
}


/*!
 * WizardPage destructor
 */

WizardPage::~WizardPage()
{
////@begin WizardPage destruction
////@end WizardPage destruction
}


/*!
 * Member initialisation
 */

void WizardPage::Init()
{
////@begin WizardPage member initialisation
    m_eviacamLogo = NULL;
////@end WizardPage member initialisation
}


/*!
 * Control creation for WizardPage
 */

void WizardPage::CreateControls()
{    
////@begin WizardPage content construction
    WizardPage* itemWizardPageSimple2 = this;

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    itemWizardPageSimple2->SetSizer(itemFlexGridSizer3);

    wxStaticText* itemStaticText4 = new wxStaticText( itemWizardPageSimple2, wxID_STATIC, _("Welcome to the DAATN Vision configuration wizard"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine5 = new wxStaticLine( itemWizardPageSimple2, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemFlexGridSizer3->Add(itemStaticLine5, 0, wxGROW|wxALIGN_TOP|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer3->Add(itemBoxSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_eviacamLogo = new wxStaticBitmap( itemWizardPageSimple2, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxSize(303, 100), 0 );
    itemBoxSizer6->Add(m_eviacamLogo, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemWizardPageSimple2, wxID_STATIC, _("Click Next to continue."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer3->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer3->AddGrowableRow(2);
    itemFlexGridSizer3->AddGrowableCol(0);

////@end WizardPage content construction

	wxString logoPath= eviacam::GetDataDir();
	logoPath+= _T("/eviacam_logo.png");
	m_eviacamLogo->SetBitmap(wxBitmap(logoPath, wxBITMAP_TYPE_PNG));    
	//m_eviacamLogo = new wxStaticBitmap( itemWizardPageSimple2, wxID_STATIC, itemWizardPageSimple2->GetBitmapResource(wxT("../doc/eviacam_logo.png")), wxDefaultPosition, wxSize(303, 100), 0 );
}




/*!
 * Should we show tooltips?
 */

bool WizardPage::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage icon retrieval
}


/*!
 * WizardPage1 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage1, wxWizardPageSimple )


/*!
 * WizardPage1 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage1, wxWizardPageSimple )

////@begin WizardPage1 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage1::OnWizardpage1Changed )
    EVT_CHECKBOX( ID_CHECKBOX_PERFORM_CALIBRATION, WizardPage1::OnCheckboxPerformCalibrationClick )
////@end WizardPage1 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage1 constructors
 */

WizardPage1::WizardPage1()
{
    Init();
}

WizardPage1::WizardPage1( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
	Create( parent );
}


/*!
 * WizardPage1 creator
 */

bool WizardPage1::Create( wxWizard* parent )
{
////@begin WizardPage1 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage1 creation
    return true;
}


/*!
 * WizardPage1 destructor
 */

WizardPage1::~WizardPage1()
{
////@begin WizardPage1 destruction
////@end WizardPage1 destruction
}


/*!
 * Member initialisation
 */

void WizardPage1::Init()
{
////@begin WizardPage1 member initialisation
    m_chkPerformCalibration = NULL;
////@end WizardPage1 member initialisation
}


/*!
 * Control creation for WizardPage1
 */

void WizardPage1::CreateControls()
{    
////@begin WizardPage1 content construction
    WizardPage1* itemWizardPageSimple33 = this;

    wxBoxSizer* itemBoxSizer34 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple33->SetSizer(itemBoxSizer34);

    wxStaticText* itemStaticText35 = new wxStaticText( itemWizardPageSimple33, wxID_STATIC, _("Pointer calibration"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText35->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer34->Add(itemStaticText35, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine36 = new wxStaticLine( itemWizardPageSimple33, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer34->Add(itemStaticLine36, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer37 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer34->Add(itemBoxSizer37, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText38 = new wxStaticText( itemWizardPageSimple33, wxID_STATIC, _("The assisted calibration procedure will ask you to move your head in order to automatically configure the appropriate motion parameters.\n\nAfter this calibration stage, you can manually adjust the motion parameters.\n\nNOTE: the calibration assistant will enable the pointer control so that you can test your configuration."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText38->Wrap(450);
    itemBoxSizer37->Add(itemStaticText38, 0, wxGROW|wxALL, 5);

    itemBoxSizer37->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer37->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_chkPerformCalibration = new wxCheckBox( itemWizardPageSimple33, ID_CHECKBOX_PERFORM_CALIBRATION, _("Perform assisted calibration"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkPerformCalibration->SetValue(false);
    if (WizardPage1::ShowToolTips())
        m_chkPerformCalibration->SetToolTip(_("If checked the next window will allow\nyou to calibrate the speed of the pointer."));
    itemBoxSizer37->Add(m_chkPerformCalibration, 0, wxALIGN_LEFT|wxALL, 5);

////@end WizardPage1 content construction
}


/*!
 * Should we show tooltips?
 */

bool WizardPage1::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage1::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage1 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage1 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage1::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage1 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage1 icon retrieval
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX_PERFORM_CALIBRATION
 */

void WizardPage1::OnCheckboxPerformCalibrationClick( wxCommandEvent& event )
{
	m_wizardParent->SetPerformCalibration(m_chkPerformCalibration->GetValue());
	event.Skip(false);	
}


/*!
 * WizardPage2 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage2, wxWizardPageSimple )


/*!
 * WizardPage2 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage2, wxWizardPageSimple )

////@begin WizardPage2 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage2::OnWizardpage2Changed )
////@end WizardPage2 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage2 constructors
 */

WizardPage2::WizardPage2()
{
    Init();
}

WizardPage2::WizardPage2( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage2 creator
 */

bool WizardPage2::Create( wxWizard* parent )
{
////@begin WizardPage2 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage2 creation
    return true;
}


/*!
 * WizardPage2 destructor
 */

WizardPage2::~WizardPage2()
{
////@begin WizardPage2 destruction
////@end WizardPage2 destruction
}


/*!
 * Member initialisation
 */

void WizardPage2::Init()
{
////@begin WizardPage2 member initialisation
////@end WizardPage2 member initialisation
}


/*!
 * Control creation for WizardPage2
 */

void WizardPage2::CreateControls()
{    
////@begin WizardPage2 content construction
    WizardPage2* itemWizardPageSimple42 = this;

    wxBoxSizer* itemBoxSizer43 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple42->SetSizer(itemBoxSizer43);

    wxStaticText* itemStaticText44 = new wxStaticText( itemWizardPageSimple42, wxID_STATIC, _("Pointer calibration "), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText44->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer43->Add(itemStaticText44, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine45 = new wxStaticLine( itemWizardPageSimple42, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer43->Add(itemStaticLine45, 0, wxGROW|wxALL, 5);

////@end WizardPage2 content construction
}


/*!
 * Should we show tooltips?
 */

bool WizardPage2::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage2::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage2 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage2 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage2::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage2 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage2 icon retrieval
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE2
 */

void WizardPage2::OnWizardpage2Changed( wxWizardEvent& event )
{
	if (m_wizardParent->GetPerformCalibration() && event.GetDirection())
	{
		bool isEnabled= wxGetApp().GetController().GetEnabled();
		wxGetApp().GetController().StartMotionCalibration();
		wxGetApp().GetController().SetEnabled(isEnabled);
	}

	if (event.GetDirection())
		m_wizardParent->ShowPage(GetNext());
	else
		m_wizardParent->ShowPage(GetPrev());
	
	event.Skip(false);
}



/*!
 * WizardPage3 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage3, wxWizardPageSimple )


/*!
 * WizardPage3 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage3, wxWizardPageSimple )

////@begin WizardPage3 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage3::OnWizardpage3Changed )
    EVT_RADIOBUTTON( ID_RADIOBUTTON_DWELL_CLICK, WizardPage3::OnRadiobuttonDwellClickSelected )
#if defined(__WXGTK__)
    EVT_RADIOBUTTON( ID_RADIOBUTTON_GESTURE_CLICK, WizardPage3::OnRadiobuttonGestureClickSelected )
#endif

    EVT_RADIOBUTTON( ID_RADIOBUTTON_NONE_CLICK, WizardPage3::OnRadiobuttonNoneClickSelected )
    EVT_TOGGLEBUTTON( ID_TOGGLE_HEAD_TRACKING_PAGE3, WizardPage3::OnToggleHeadTrackingPage3Click )
    EVT_UPDATE_UI( ID_TOGGLE_HEAD_TRACKING_PAGE3, WizardPage3::OnToggleHeadTrackingPage3Update )
////@end WizardPage3 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage3 constructors
 */

WizardPage3::WizardPage3()
{
    Init();
}

WizardPage3::WizardPage3( wxWizard* parent )
{
	Init();
	m_wizardParent = (WWizard*) parent;
	Create( parent );
}


/*!
 * WizardPage3 creator
 */

bool WizardPage3::Create( wxWizard* parent )
{
////@begin WizardPage3 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage3 creation
    return true;
}


/*!
 * WizardPage3 destructor
 */

WizardPage3::~WizardPage3()
{
////@begin WizardPage3 destruction
////@end WizardPage3 destruction
}


/*!
 * Member initialisation
 */

void WizardPage3::Init()
{
////@begin WizardPage3 member initialisation
    m_toggleTest = NULL;
    m_rbDwellClick = NULL;
#if defined(__WXGTK__)
    m_rbGestureClick = NULL;
#endif
    m_rbNoneClick = NULL;
    m_toggleHeadTrackingPage3 = NULL;
////@end WizardPage3 member initialisation

	m_isLeftDown= false;
	m_isDoubleClick= false;
}


/*!
 * Control creation for WizardPage3
 */

void WizardPage3::CreateControls()
{    
////@begin WizardPage3 content construction
    WizardPage3* itemWizardPageSimple61 = this;

    wxBoxSizer* itemBoxSizer62 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple61->SetSizer(itemBoxSizer62);

    wxStaticText* itemStaticText63 = new wxStaticText( itemWizardPageSimple61, wxID_STATIC, _("Click mode"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText63->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer62->Add(itemStaticText63, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine64 = new wxStaticLine( itemWizardPageSimple61, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer62->Add(itemStaticLine64, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer65 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer62->Add(itemBoxSizer65, 0, wxGROW|wxALL, 5);

    m_toggleTest = new wxToggleButton( itemWizardPageSimple61, ID_TOGGLE_TEST, _("Click here to test"), wxDefaultPosition, wxSize(-1, 50), 0 );
    m_toggleTest->SetValue(false);
    itemBoxSizer65->Add(m_toggleTest, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer65->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_rbDwellClick = new wxRadioButton( itemWizardPageSimple61, ID_RADIOBUTTON_DWELL_CLICK, _("Dwell Click (default)"), wxDefaultPosition, wxDefaultSize, 0 );
    m_rbDwellClick->SetValue(true);
    itemBoxSizer65->Add(m_rbDwellClick, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText69 = new wxStaticText( itemWizardPageSimple61, wxID_STATIC, _("The click is generated automatically when you hover the mouse pointer momentarily. The Click the Window lets you choose between different actions."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText69->Wrap(450);
    itemBoxSizer65->Add(itemStaticText69, 0, wxGROW|wxALL, 5);

#if defined(__WXGTK__)
    m_rbGestureClick = new wxRadioButton( itemWizardPageSimple61, ID_RADIOBUTTON_GESTURE_CLICK, _("Gesture click"), wxDefaultPosition, wxDefaultSize, 0 );
    m_rbGestureClick->SetValue(false);
    itemBoxSizer65->Add(m_rbGestureClick, 0, wxALIGN_LEFT|wxALL, 5);

#endif

#if defined(__WXGTK__)
    wxStaticText* itemStaticText71 = new wxStaticText( itemWizardPageSimple61, wxID_STATIC, _("The click is automatically generated by stopping the pointer for a moment and then moving the pointer to one of the 4 directions to choose the action."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText71->Wrap(450);
    itemBoxSizer65->Add(itemStaticText71, 0, wxGROW|wxALL, 5);

#endif

    m_rbNoneClick = new wxRadioButton( itemWizardPageSimple61, ID_RADIOBUTTON_NONE_CLICK, _("No click. Click function disabled."), wxDefaultPosition, wxDefaultSize, 0 );
    m_rbNoneClick->SetValue(false);
    itemBoxSizer65->Add(m_rbNoneClick, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer65->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_toggleHeadTrackingPage3 = new wxToggleButton( itemWizardPageSimple61, ID_TOGGLE_HEAD_TRACKING_PAGE3, _("Enable head tracking"), wxDefaultPosition, wxDefaultSize, 0 );
    m_toggleHeadTrackingPage3->SetValue(false);
    itemBoxSizer65->Add(m_toggleHeadTrackingPage3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    // Connect events and objects
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_LEFT_DOWN, wxMouseEventHandler(WizardPage3::OnLeftDownTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_LEFT_UP, wxMouseEventHandler(WizardPage3::OnLeftUpTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_LEFT_DCLICK, wxMouseEventHandler(WizardPage3::OnLeftDClickTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_MIDDLE_UP, wxMouseEventHandler(WizardPage3::OnMiddleUpTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_RIGHT_UP, wxMouseEventHandler(WizardPage3::OnRightUpTest), NULL, this);
////@end WizardPage3 content construction

}


/*!
 * Should we show tooltips?
 */

bool WizardPage3::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage3::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage3 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage3 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage3::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage3 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage3 icon retrieval
}

void WizardPage3::UpdateRadioButtons()
{
	// Set radio buttons according to the current configuration
	m_rbDwellClick->SetValue(false);
#if defined(__WXGTK__)
	m_rbGestureClick->SetValue(false);
	m_rbNoneClick->SetValue(false);
#endif
	switch (wxGetApp().GetController().GetPointerAction().GetClickMode()) {
	case CPointerAction::DWELL:
		m_rbDwellClick->SetValue(true);
		// Force open click window
		wxGetApp().GetController().GetPointerAction().GetDwellClick().SetUseClickWindow(true);
		break;
#if defined(__WXGTK__)
	case CPointerAction::GESTURE:
		m_rbGestureClick->SetValue(true);
		break;
#endif
	case CPointerAction::NONE:
		m_rbNoneClick->SetValue(true);
		break;
	default:
		assert (false);
	}
}

/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON_NONE_CLICK
 */

void WizardPage3::OnRadiobuttonNoneClickSelected( wxCommandEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetClickMode(CPointerAction::NONE, false);
	UpdateRadioButtons();
	event.Skip(false);
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE3
 */

void WizardPage3::OnWizardpage3Changed( wxWizardEvent& event )
{
	UpdateRadioButtons();
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON_DWELL_CLICK
 */

void WizardPage3::OnRadiobuttonDwellClickSelected( wxCommandEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetClickMode(CPointerAction::DWELL, false);
	UpdateRadioButtons();
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON_GESTURE_CLICK
 */
#if defined(__WXGTK__)
void WizardPage3::OnRadiobuttonGestureClickSelected( wxCommandEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetClickMode(CPointerAction::GESTURE, false);
	UpdateRadioButtons();
	event.Skip(false);
}
#endif


/*!
 * wxEVT_LEFT_DOWN event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnLeftDownTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Drag"));
	
	m_lastLeftDown= wxGetLocalTimeMillis();
	m_isLeftDown= true;
	
	event.Skip(false);
}


/*!
 * wxEVT_LEFT_UP event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnLeftUpTest( wxMouseEvent& event )
{
	if (m_isDoubleClick) m_isDoubleClick= false;
	else {
		if (wxGetLocalTimeMillis() - m_lastLeftDown > 200)
			m_toggleTest->SetLabel(_("Drop"));
		else
			m_toggleTest->SetLabel(_("Left click"));
	}
	m_isLeftDown= false;
	event.Skip(false);
}

/*!
 * wxEVT_RIGHT_UP event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnRightUpTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Right click"));
	event.Skip(false);
}

/*!
 * wxEVT_LEFT_DCLICK event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnLeftDClickTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Double click"));
	m_isDoubleClick= true;
	event.Skip(false);
}

/*!
 * wxEVT_MIDDLE_UP event handler for ID_TOGGLE_TEST
 */

void WizardPage3::OnMiddleUpTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Middle click"));
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_TOGGLE_HEAD_TRACKING_PAGE3
 */

void WizardPage3::OnToggleHeadTrackingPage3Click( wxCommandEvent& event )
{
	m_wizardParent->OnToggleHeadTrackingClick (event, *m_toggleHeadTrackingPage3);
}


/*!
 * wxEVT_UPDATE_UI event handler for ID_TOGGLE_HEAD_TRACKING_PAGE3
 */

void WizardPage3::OnToggleHeadTrackingPage3Update( wxUpdateUIEvent& event )
{
	m_wizardParent->OnToggleHeadTrackingUpdate(event, *m_toggleHeadTrackingPage3);
}



/*!
 * WizardPage4 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage4, wxWizardPageSimple )


/*!
 * WizardPage4 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage4, wxWizardPageSimple )

////@begin WizardPage4 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage4::OnWizardpageFinalPageChanged )
    EVT_CHECKBOX( ID_CHECKBOX1, WizardPage4::OnCheckboxRunWizardAtStartupClick )
#if defined(__WXGTK__)
    EVT_CHECKBOX( ID_CHECKBOX3, WizardPage4::OnCheckboxStartupClick )
#endif

    EVT_CHECKBOX( ID_CHECKBOX4, WizardPage4::OnCheckboxEnabledAtStartupClick )
////@end WizardPage4 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage4 constructors
 */

WizardPage4::WizardPage4()
{
    Init();
}

WizardPage4::WizardPage4( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage4 creator
 */

bool WizardPage4::Create( wxWizard* parent )
{
////@begin WizardPage4 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage4 creation
    return true;
}


/*!
 * WizardPage4 destructor
 */

WizardPage4::~WizardPage4()
{
////@begin WizardPage4 destruction
////@end WizardPage4 destruction
}


/*!
 * Member initialisation
 */

void WizardPage4::Init()
{
////@begin WizardPage4 member initialisation
    m_chkRunWizardAtStartup = NULL;
#if defined(__WXGTK__)
    m_chkStartup = NULL;
#endif
    m_chkEnabledAtStartup = NULL;
////@end WizardPage4 member initialisation
}


/*!
 * Control creation for WizardPage4
 */

void WizardPage4::CreateControls()
{    
////@begin WizardPage4 content construction
    WizardPage4* itemWizardPageSimple75 = this;

    wxFlexGridSizer* itemFlexGridSizer76 = new wxFlexGridSizer(0, 1, 0, 0);
    itemWizardPageSimple75->SetSizer(itemFlexGridSizer76);

    wxStaticText* itemStaticText77 = new wxStaticText( itemWizardPageSimple75, wxID_STATIC, _("Wizard completed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText77->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemFlexGridSizer76->Add(itemStaticText77, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine78 = new wxStaticLine( itemWizardPageSimple75, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemFlexGridSizer76->Add(itemStaticLine78, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer79 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer76->Add(itemFlexGridSizer79, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_chkRunWizardAtStartup = new wxCheckBox( itemWizardPageSimple75, ID_CHECKBOX1, _("Run this wizard at startup"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkRunWizardAtStartup->SetValue(false);
    if (WizardPage4::ShowToolTips())
        m_chkRunWizardAtStartup->SetToolTip(_("If checked the wizard automatically appears at startup."));
    itemFlexGridSizer79->Add(m_chkRunWizardAtStartup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

#if defined(__WXGTK__)
    m_chkStartup = new wxCheckBox( itemWizardPageSimple75, ID_CHECKBOX3, _("Start DAATN Vision at user logon"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkStartup->SetValue(false);
    itemFlexGridSizer79->Add(m_chkStartup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

    m_chkEnabledAtStartup = new wxCheckBox( itemWizardPageSimple75, ID_CHECKBOX4, _("Enable DAATN Vision at startup"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkEnabledAtStartup->SetValue(false);
    if (WizardPage4::ShowToolTips())
        m_chkEnabledAtStartup->SetToolTip(_("If checked the program automatically \nenables cursor control at startup."));
    itemFlexGridSizer79->Add(m_chkEnabledAtStartup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer79->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText84 = new wxStaticText( itemWizardPageSimple75, wxID_STATIC, _("You may change the settings through Configuration -> Options"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText84->Wrap(450);
    itemFlexGridSizer79->Add(itemStaticText84, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5);

    itemFlexGridSizer76->AddGrowableCol(0);

////@end WizardPage4 content construction
	m_chkEnabledAtStartup->SetValue(wxGetApp().GetController().GetEnabledAtStartup());
#if defined(__WXGTK__)
	m_chkStartup->SetValue(wxGetApp().GetController().GetAutostart().IsEnabled());
#endif
}


/*!
 * Should we show tooltips?
 */

bool WizardPage4::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage4::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage4 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage4 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage4::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage4 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage4 icon retrieval
}


/*!
 * wxEVT_WIZARD_FINISHED event handler for ID_WWIZARD
 */

void WWizard::OnWwizardFinished( wxWizardEvent& event )
{
	wxGetApp().GetController().GetConfigManager().WriteAll();
	event.Skip(false);
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE1
 */

void WizardPage1::OnWizardpage1Changed( wxWizardEvent& event )
{
    m_wizardParent->SetPerformCalibration(false);
	m_chkPerformCalibration->SetValue(false);
	event.Skip(false);
}



/*!
 * WizardPage5 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage5, wxWizardPageSimple )


/*!
 * WizardPage5 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage5, wxWizardPageSimple )

////@begin WizardPage5 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage5::OnWizardpageCameraPageChanged )
    EVT_BUTTON( ID_BUTTON5, WizardPage5::OnButtonCameraSettingsClick )
////@end WizardPage5 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage5 constructors
 */

WizardPage5::WizardPage5()
{
    Init();
}

WizardPage5::WizardPage5( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
	
}


/*!
 * WizardPage5 creator
 */

bool WizardPage5::Create( wxWizard* parent )
{
////@begin WizardPage5 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage5 creation
    return true;
}


/*!
 * WizardPage5 destructor
 */

WizardPage5::~WizardPage5()
{
////@begin WizardPage5 destruction
////@end WizardPage5 destruction
}


/*!
 * Member initialisation
 */

void WizardPage5::Init()
{
////@begin WizardPage5 member initialisation
    m_staticCameraName = NULL;
    m_staticFramerate = NULL;
    m_staticCameraInstructions = NULL;
    m_btnCameraSettings = NULL;
////@end WizardPage5 member initialisation
}


/*!
 * Control creation for WizardPage5
 */

void WizardPage5::CreateControls()
{    
////@begin WizardPage5 content construction
    WizardPage5* itemWizardPageSimple9 = this;

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple9->SetSizer(itemBoxSizer10);

    wxStaticText* itemStaticText11 = new wxStaticText( itemWizardPageSimple9, wxID_STATIC, _("Camera setup"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText11->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer10->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine12 = new wxStaticLine( itemWizardPageSimple9, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer10->Add(itemStaticLine12, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer10->Add(itemBoxSizer13, 0, wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer14 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer13->Add(itemFlexGridSizer14, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemWizardPageSimple9, wxID_STATIC, _("Detected camera:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer14->Add(itemStaticText15, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_staticCameraName = new wxStaticText( itemWizardPageSimple9, wxID_STATIC, _("camera_name"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticCameraName->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxT("")));
    itemFlexGridSizer14->Add(m_staticCameraName, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText17 = new wxStaticText( itemWizardPageSimple9, wxID_STATIC, _("Framerate:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer14->Add(itemStaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_staticFramerate = new wxStaticText( itemWizardPageSimple9, wxID_STATIC, _("framerate"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticFramerate->SetFont(wxFont(wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxT("")));
    itemFlexGridSizer14->Add(m_staticFramerate, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer13->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_staticCameraInstructions = new wxStaticText( itemWizardPageSimple9, wxID_STATIC, _("For best performance possible, the frame rate should be equal to or greater than 25 fps. DAATN Vision tries to automatically configure your camera, but If this value is below this threshold you may need to manually adjust the camera settings."), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticCameraInstructions->Wrap(450);
    itemBoxSizer13->Add(m_staticCameraInstructions, 0, wxGROW|wxALL, 5);

    itemBoxSizer13->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_btnCameraSettings = new wxButton( itemWizardPageSimple9, ID_BUTTON5, _("Camera settings..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add(m_btnCameraSettings, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end WizardPage5 content construction
	m_staticCameraName->SetLabel(wxGetApp().GetController().GetCameraName());	
	m_staticFramerate->SetLabel(wxString::Format(wxT("%.1f"), wxGetApp().GetController().GetCamera().GetRealFrameRate()));

}


/*!
 * Should we show tooltips?
 */

bool WizardPage5::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage5::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage5 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage5 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage5::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage5 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage5 icon retrieval
}


/*!
 * WizardPage6 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage6, wxWizardPageSimple )


/*!
 * WizardPage6 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage6, wxWizardPageSimple )

////@begin WizardPage6 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage6::OnWizardpageCalib3PageChanged )
    EVT_SPINCTRL( ID_SPINCTRL, WizardPage6::OnSpinctrlXSpeedUpdated )
    EVT_SPINCTRL( ID_SPINCTRL1, WizardPage6::OnSpinctrlYSpeedUpdated )
    EVT_TOGGLEBUTTON( ID_TOGGLE_HEAD_TRACKING_PAGE6, WizardPage6::OnToggleHeadTrackingPage6Click )
    EVT_UPDATE_UI( ID_TOGGLE_HEAD_TRACKING_PAGE6, WizardPage6::OnToggleHeadTrackingPage6Update )
////@end WizardPage6 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage6 constructors
 */

WizardPage6::WizardPage6()
{
    Init();
}

WizardPage6::WizardPage6( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage6 creator
 */

bool WizardPage6::Create( wxWizard* parent )
{
////@begin WizardPage6 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage6 creation
    return true;
}


/*!
 * WizardPage6 destructor
 */

WizardPage6::~WizardPage6()
{
////@begin WizardPage6 destruction
////@end WizardPage6 destruction
}


/*!
 * Member initialisation
 */

void WizardPage6::Init()
{
////@begin WizardPage6 member initialisation
    m_spinXSpeed = NULL;
    m_spinYSpeed = NULL;
    m_toggleHeadTrackingPage6 = NULL;
////@end WizardPage6 member initialisation
}


/*!
 * Control creation for WizardPage6
 */

void WizardPage6::CreateControls()
{    
////@begin WizardPage6 content construction
    WizardPage6* itemWizardPageSimple46 = this;

    wxBoxSizer* itemBoxSizer47 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple46->SetSizer(itemBoxSizer47);

    wxStaticText* itemStaticText48 = new wxStaticText( itemWizardPageSimple46, wxID_STATIC, _("Pointer calibration"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText48->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer47->Add(itemStaticText48, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine49 = new wxStaticLine( itemWizardPageSimple46, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer47->Add(itemStaticLine49, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer50 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer47->Add(itemBoxSizer50, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText51 = new wxStaticText( itemWizardPageSimple46, wxID_STATIC, _("You can adjust motion speed manually and enable head tracking to test how it works."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText51->Wrap(450);
    itemBoxSizer50->Add(itemStaticText51, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer52 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer50->Add(itemBoxSizer52, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText53 = new wxStaticText( itemWizardPageSimple46, wxID_STATIC, _("X axis speed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer52->Add(itemStaticText53, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_spinXSpeed = new wxSpinCtrl( itemWizardPageSimple46, ID_SPINCTRL, wxT("0"), wxDefaultPosition, wxSize(75, -1), wxSP_ARROW_KEYS, 0, 30, 0 );
    itemBoxSizer52->Add(m_spinXSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer55 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer50->Add(itemBoxSizer55, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText56 = new wxStaticText( itemWizardPageSimple46, wxID_STATIC, _("Y axis speed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer55->Add(itemStaticText56, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_spinYSpeed = new wxSpinCtrl( itemWizardPageSimple46, ID_SPINCTRL1, wxT("0"), wxDefaultPosition, wxSize(75, -1), wxSP_ARROW_KEYS, 0, 30, 0 );
    itemBoxSizer55->Add(m_spinYSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer50->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer50->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_toggleHeadTrackingPage6 = new wxToggleButton( itemWizardPageSimple46, ID_TOGGLE_HEAD_TRACKING_PAGE6, _("Enable pointer control"), wxDefaultPosition, wxDefaultSize, 0 );
    m_toggleHeadTrackingPage6->SetValue(false);
    itemBoxSizer50->Add(m_toggleHeadTrackingPage6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end WizardPage6 content construction

}


/*!
 * Should we show tooltips?
 */

bool WizardPage6::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage6::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage6 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage6 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage6::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage6 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage6 icon retrieval
}


/*!
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL
 */

void WizardPage6::OnSpinctrlXSpeedUpdated( wxSpinEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetXSpeed(event.GetInt());
    event.Skip(false);
}


/*!
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL1
 */

void WizardPage6::OnSpinctrlYSpeedUpdated( wxSpinEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetYSpeed(event.GetInt());
    event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_TOGGLE_HEAD_TRACKING_PAGE6
 */

void WizardPage6::OnToggleHeadTrackingPage6Click( wxCommandEvent& event )
{
	m_wizardParent->OnToggleHeadTrackingClick (event, *m_toggleHeadTrackingPage6);
}

/*!
 * wxEVT_UPDATE_UI event handler for ID_TOGGLE_HEAD_TRACKING_PAGE6
 */

void WizardPage6::OnToggleHeadTrackingPage6Update( wxUpdateUIEvent& event )
{
	m_wizardParent->OnToggleHeadTrackingUpdate(event, *m_toggleHeadTrackingPage6);
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE6
 */

void WizardPage6::OnWizardpageCalib3PageChanged( wxWizardEvent& event )
{
	m_spinXSpeed->SetValue(wxGetApp().GetController().GetPointerAction().GetXSpeed());
	m_spinYSpeed->SetValue(wxGetApp().GetController().GetPointerAction().GetYSpeed());
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX1
 */

void WizardPage4::OnCheckboxRunWizardAtStartupClick( wxCommandEvent& event )
{
	wxGetApp().GetController().SetRunWizardAtStartup(event.IsChecked());
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX3
 */
#if defined(__WXGTK__)
void WizardPage4::OnCheckboxStartupClick( wxCommandEvent& event )
{
#if defined(__WXGTK__)
	wxGetApp().GetController().GetAutostart().Enable(event.IsChecked());
#endif
    event.Skip(false);
}
#endif

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE4
 */

void WizardPage4::OnWizardpageFinalPageChanged( wxWizardEvent& event )
{
	m_chkEnabledAtStartup->SetValue(false);
	wxGetApp().GetController().SetRunWizardAtStartup (false);
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX4
 */

void WizardPage4::OnCheckboxEnabledAtStartupClick( wxCommandEvent& event )
{
	wxGetApp().GetController().SetEnabledAtStartup (m_chkEnabledAtStartup->GetValue());
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON5
 */

void WizardPage5::OnButtonCameraSettingsClick( wxCommandEvent& event )
{
	wxGetApp().GetController().ShowCameraSettingsDialog();
	event.Skip(false);
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE_CAMERA
 */

void WizardPage5::OnWizardpageCameraPageChanged( wxWizardEvent& event )
{
	float fr= wxGetApp().GetController().GetCamera().GetRealFrameRate();
	m_staticFramerate->SetLabel(wxString::Format(wxT("%.1f"), fr));
	if (fr>= 25.0f) {
		m_staticCameraInstructions->SetLabel(_("The frame rate is appropriate."));
		m_btnCameraSettings->Hide();
	}
	event.Skip(false);
}


/*!
 * WizardPage8 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage8, wxWizardPageSimple )


/*!
 * WizardPage8 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage8, wxWizardPageSimple )

////@begin WizardPage8 event table entries
    EVT_CHECKBOX( ID_CHECKBOX_LOCATE_FACE, WizardPage8::OnCheckboxLocateFaceClick )
    EVT_CHECKBOX( ID_CHECKBOX_ENABLE_WHEN_FACE_DETECTED, WizardPage8::OnCheckboxEnableWhenFaceDetectedClick )
////@end WizardPage8 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage8 constructors
 */

WizardPage8::WizardPage8()
{
    Init();
}

WizardPage8::WizardPage8( wxWizard* parent )
{
    Init();
    Create( parent );
}


/*!
 * WizardPage8 creator
 */

bool WizardPage8::Create( wxWizard* parent )
{
////@begin WizardPage8 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage8 creation
    return true;
}


/*!
 * WizardPage8 destructor
 */

WizardPage8::~WizardPage8()
{
////@begin WizardPage8 destruction
////@end WizardPage8 destruction
}


/*!
 * Member initialisation
 */

void WizardPage8::Init()
{
////@begin WizardPage8 member initialisation
    m_chkLocateFace = NULL;
    m_chkEnableWhenFaceDetected = NULL;
////@end WizardPage8 member initialisation
}


/*!
 * Control creation for WizardPage8
 */

void WizardPage8::CreateControls()
{    
////@begin WizardPage8 content construction
    WizardPage8* itemWizardPageSimple23 = this;

    wxBoxSizer* itemBoxSizer24 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple23->SetSizer(itemBoxSizer24);

    wxStaticText* itemStaticText25 = new wxStaticText( itemWizardPageSimple23, wxID_STATIC, _("Face detection setup"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText25->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Sans")));
    itemBoxSizer24->Add(itemStaticText25, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine26 = new wxStaticLine( itemWizardPageSimple23, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer24->Add(itemStaticLine26, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer27 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer24->Add(itemBoxSizer27, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText28 = new wxStaticText( itemWizardPageSimple23, wxID_STATIC, _("DAATN Vision will try to detect your face automatically. But, if necessary, you can disable this feature and manually adjust the tracking area (blue rectangle) around your face.\n"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText28->Wrap(450);
    itemBoxSizer27->Add(itemStaticText28, 0, wxGROW|wxALL, 5);

    itemBoxSizer27->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_chkLocateFace = new wxCheckBox( itemWizardPageSimple23, ID_CHECKBOX_LOCATE_FACE, _("Locate face automatically (recommended)"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkLocateFace->SetValue(false);
    itemBoxSizer27->Add(m_chkLocateFace, 0, wxALIGN_LEFT|wxALL, 5);

    itemBoxSizer27->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_chkEnableWhenFaceDetected = new wxCheckBox( itemWizardPageSimple23, ID_CHECKBOX_ENABLE_WHEN_FACE_DETECTED, _("Disable DAATN Vision if no face is found"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkEnableWhenFaceDetected->SetValue(false);
    itemBoxSizer27->Add(m_chkEnableWhenFaceDetected, 0, wxALIGN_LEFT|wxALL, 5);

////@end WizardPage8 content construction

	m_chkLocateFace->SetValue(wxGetApp().GetController().GetVisionPipeline().GetTrackFace());
	m_chkEnableWhenFaceDetected->Enable (m_chkLocateFace->GetValue());
	m_chkEnableWhenFaceDetected->SetValue(wxGetApp().GetController().GetVisionPipeline().GetEnableWhenFaceDetected());
}


/*!
 * Should we show tooltips?
 */

bool WizardPage8::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage8::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage8 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage8 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage8::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage8 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage8 icon retrieval
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX_LOCATE_FACE
 */

void WizardPage8::OnCheckboxLocateFaceClick( wxCommandEvent& event )
{
	wxGetApp().GetController().GetVisionPipeline().SetTrackFace (m_chkLocateFace->GetValue());
	wxGetApp().GetController().GetVisionPipeline().SetDegradation(0);
	m_chkEnableWhenFaceDetected->Enable (m_chkLocateFace->GetValue());
	event.Skip();
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX_ENABLE_WHEN_FACE_DETECTED
 */

void WizardPage8::OnCheckboxEnableWhenFaceDetectedClick( wxCommandEvent& event )
{
	wxGetApp().GetController().GetVisionPipeline().SetEnableWhenFaceDetected (m_chkEnableWhenFaceDetected->GetValue());
    event.Skip();
}


/*!
 * wxEVT_WIZARD_CANCEL event handler for ID_WWIZARD
 */

void WWizard::OnWwizardCancel( wxWizardEvent& event )
{
	wxGetApp().GetController().SetRunWizardAtStartup(false);
	wxGetApp().GetController().GetConfigManager().WriteAll();
    event.Skip();
}

