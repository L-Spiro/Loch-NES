#ifdef LSN_USE_WINDOWS

/**
 * First because of:
 *	1>C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\um\objidlbase.h(7882,79): error C2872: 'byte': ambiguous symbol
 *	1>C:\Program Files (x86)\Windows Kits\10\Include\10.0.19041.0\shared\rpcndr.h(191,23): message : could be 'unsigned char byte'
 *	1>T:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.31.31103\include\cstddef(28,12): message : or       'std::byte'
 **/
#include <LSWWin.h>
#include <shlwapi.h>

#include "../../Utilities/LSNUtilities.h"
#include "LSNMainWindow.h"
#include "LSNMainWindowLayout.h"
#include <Rebar/LSWRebar.h>
#include <StatusBar/LSWStatusBar.h>
#include <ToolBar/LSWToolBar.h>
#include <commdlg.h>

namespace lsn {

	CMainWindow::CMainWindow( const lsw::LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget, HMENU _hMenu, uint64_t _ui64Data ) :
		lsw::CMainWindow( _wlLayout, _pwParent, _bCreateWidget, _hMenu, _ui64Data ) {


		static const struct {
			LPCWSTR				lpwsImageName;
			DWORD				dwConst;
		} sImages[] = {
			{ L"1", LSN_I_OPENROM },

			{ L"73", LSN_I_OPTIONS },
		};
		m_iImages.Create( 24, 24, ILC_COLOR32, LSN_I_TOTAL, LSN_I_TOTAL );
		WCHAR szBuffer[MAX_PATH];
		::GetModuleFileNameW( NULL, szBuffer, MAX_PATH );
		PWSTR pwsEnd = std::wcsrchr( szBuffer, L'\\' ) + 1;
		(*pwsEnd) = L'\0';
		std::wstring wsRoot = szBuffer;
		for ( size_t I = 0; I < LSN_I_TOTAL; ++I ) {
			std::wstring wsTemp = wsRoot + L"Resources\\";
			wsTemp += sImages[I].lpwsImageName;
			wsTemp += L".bmp";

			m_bBitmaps[sImages[I].dwConst].LoadFromFile( wsTemp.c_str(), 0, 0, LR_CREATEDIBSECTION );
			m_iImageMap[sImages[I].dwConst] = m_iImages.Add( m_bBitmaps[sImages[I].dwConst].Handle() );
		}

	}
	CMainWindow::~CMainWindow() {
	}

	// == Functions.
	// WM_INITDIALOG.
	CWidget::LSW_HANDLED CMainWindow::InitDialog() {
		lsw::CToolBar * plvToolBar = static_cast<lsw::CToolBar *>(FindChild( CMainWindowLayout::LSN_MWI_TOOLBAR0 ));
		lsw::CRebar * plvRebar = static_cast<lsw::CRebar *>(FindChild( CMainWindowLayout::LSN_MWI_REBAR0 ));


		// ==== TOOL BAR ==== //
		if ( plvToolBar ) {
			plvToolBar->SetImageList( 0, m_iImages );
//#define LSN_TOOL_STR( TXT )					reinterpret_cast<INT_PTR>(TXT)
#define LSN_TOOL_STR( TXT )						0
			const TBBUTTON bButtons[] = {
				// iBitmap							idCommand									fsState				fsStyle			bReserved	dwData	iString
				{ m_iImageMap[LSN_I_OPENROM],		CMainWindowLayout::LSN_MWMI_OPENROM,	TBSTATE_ENABLED,	BTNS_AUTOSIZE,	{ 0 },		0,		LSN_TOOL_STR( L"Open Process" ) },
				{ -1,								0,											TBSTATE_ENABLED,	BTNS_SEP,		{ 0 },		0,		0 },
				{ m_iImageMap[LSN_I_OPTIONS],		CMainWindowLayout::LSN_MWMI_OPTIONS,		TBSTATE_ENABLED,	BTNS_AUTOSIZE,	{ 0 },		0,		LSN_TOOL_STR( L"Options" ) },
			};
#undef LSN_TOOL_STR

			plvToolBar->AddButtons( bButtons, LSN_ELEMENTS( bButtons ) );
		}

		LSW_RECT rRebarRect = ClientRect( this );
		LONG lRebarHeight = 0;
		if ( plvRebar ) {
			plvRebar->SetImageList( m_iImages );
			{
				LSW_REBARBANDINFO riRebarInfo;
				riRebarInfo.SetColors( ::GetSysColor( COLOR_BTNTEXT ), ::GetSysColor( COLOR_BTNFACE ) );
				riRebarInfo.SetStyle( RBBS_CHILDEDGE |
				  RBBS_FIXEDBMP );
				riRebarInfo.SetChild( plvToolBar->Wnd() );
				riRebarInfo.SetChildSize( plvToolBar->GetMinBoundingRect().Width(), plvToolBar->GetMinBoundingRect().Height() );
				riRebarInfo.SetId( CMainWindowLayout::LSN_MWI_TOOLBAR0 );
				plvRebar->InsertBand( -1, riRebarInfo );
			}

			lRebarHeight = plvRebar->WindowRect( this ).Height();
		   ::MoveWindow( plvRebar->Wnd(), 0, 0, rRebarRect.Width(), lRebarHeight, FALSE );

			plvRebar->UpdateRects();
		}

		

		// ==== STATUS BAR ==== //
		lsw::CStatusBar * psbStatus = StatusBar();
		LSW_RECT rStatusBar;
		rStatusBar.Zero();
		if ( psbStatus ) {
			const CStatusBar::LSW_STATUS_PART spParts[] = {
				// Last status message.
				//{ 450, TRUE },
				// Current process ID.
				//{ 450 + 48, TRUE },
				{ rRebarRect.Width() - psbStatus->ClientRect( this ).Height() - 48, TRUE },

				{ rRebarRect.Width() - psbStatus->ClientRect( this ).Height(), TRUE },
			};
			psbStatus->SetParts( spParts, LSN_ELEMENTS( spParts ) );
			rStatusBar = psbStatus->WindowRect();
		}
		

		ForceSizeUpdate();
		rRebarRect.SetWidth( LONG( rRebarRect.Height() / 3.0 * 4.0 ) );
		rRebarRect.bottom += lRebarHeight + rStatusBar.Height();
		::AdjustWindowRectEx( &rRebarRect, ::GetWindowLongW( Wnd(), GWL_STYLE ),
			TRUE, ::GetWindowLongW( Wnd(), GWL_EXSTYLE ) );
		LSW_RECT rScreen = rRebarRect.ClientToScreen( Wnd() );
		::MoveWindow( Wnd(), rScreen.left, rScreen.top, rScreen.Width(), rScreen.Height(), TRUE );

		return LSW_H_CONTINUE;
	}

	// WM_COMMAND from control.
	CWidget::LSW_HANDLED CMainWindow::Command( WORD /*_wCtrlCode*/, WORD _Id, CWidget * /*_pwSrc*/ ) {
		switch ( _Id ) {
			case CMainWindowLayout::LSN_MWMI_OPENROM : {
				OPENFILENAMEW ofnOpenFile = { sizeof( ofnOpenFile ) };
				std::wstring szFileName;
				szFileName.resize( 0xFFFF + 2 );
#define LSN_FILE_OPEN_FORMAT				L"ROM Files (*.nes, *.zip)\0*.nes;*.zip\0All Files (*.*)\0*.*\0\0"
				std::wstring wsFilter = std::wstring( LSN_FILE_OPEN_FORMAT, LSN_ELEMENTS( LSN_FILE_OPEN_FORMAT ) - 1 );
				ofnOpenFile.hwndOwner = Wnd();
				ofnOpenFile.lpstrFilter = wsFilter.c_str();
				ofnOpenFile.lpstrFile = &szFileName[0];
				ofnOpenFile.nMaxFile = DWORD( szFileName.size() );
				ofnOpenFile.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
				//ofnOpenFile.lpstrDefExt = L"";

				if ( ::GetOpenFileNameW( &ofnOpenFile ) ) {
					const LPWSTR lpstrExt = &ofnOpenFile.lpstrFile[ofnOpenFile.nFileExtension];
					if ( lpstrExt ) {
						if ( ::StrCmpIW( lpstrExt, L"zip" ) == 0 ) {

							return LSW_H_CONTINUE;
						}
					}
					/*if ( !LoadFile( ofnOpenFile.lpstrFile ) ) {
					}*/
				}
				break;
			}
		}
		return LSW_H_CONTINUE;
	}

	// WM_NCDESTROY.
	CWidget::LSW_HANDLED CMainWindow::NcDestroy() {
		::PostQuitMessage( 0 );
		return LSW_H_CONTINUE;
	}

	// Virtual client rectangle.  Can be used for things that need to be adjusted based on whether or not status bars, toolbars, etc. are present.
	const lsw::LSW_RECT CMainWindow::VirtualClientRect( const CWidget * /*_pwChild*/ ) const {
		LSW_RECT rTemp = ClientRect( this );
		const CRebar * plvRebar = static_cast<const CRebar *>(FindChild( CMainWindowLayout::LSN_MWI_REBAR0 ));
		if ( plvRebar ) {
			LSW_RECT rRebar = plvRebar->ClientRect( this );
			rTemp.top += rRebar.Height();
		}

		const CStatusBar * psbStatus = StatusBar();
		if ( psbStatus ) {
			LSW_RECT rStatus = psbStatus->ClientRect( this );
			rTemp.bottom -= rStatus.Height();
		}
		return rTemp;
	}

	/**
	 * Gets the status bar.
	 *
	 * \return the status bar.
	 */
	lsw::CStatusBar * CMainWindow::StatusBar() {
		return static_cast<lsw::CStatusBar *>(FindChild( CMainWindowLayout::LSN_MWI_STATUSBAR ));
	}

	/**
	 * Gets the status bar.
	 *
	 * \return the status bar.
	 */
	const lsw::CStatusBar * CMainWindow::StatusBar() const {
		return static_cast<const lsw::CStatusBar *>(FindChild( CMainWindowLayout::LSN_MWI_STATUSBAR ));
	}

}	// namespace lsn

#endif	// #ifdef LSN_USE_WINDOWS