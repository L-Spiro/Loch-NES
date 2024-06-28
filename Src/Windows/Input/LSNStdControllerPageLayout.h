#ifdef LSN_USE_WINDOWS

/**
 * Copyright L. Spiro 2023
 *
 * Written by: Shawn (L. Spiro) Wilcoxen
 *
 * Description: A dialog shaped like a standard controller.
 */

#pragma once

#include "../../LSNLSpiroNes.h"
#include "../../Options/LSNOptions.h"
#include <Layout/LSWMenuLayout.h>
#include <Layout/LSWWidgetLayout.h>
#include <Widget/LSWWidget.h>

using namespace lsw;

namespace lsn {

#define LSN_STD_CONT_BUTTON_FULL_H						((LSN_DEF_BUTTON_HEIGHT * 2) + LSN_DEF_COMBO_HEIGHT + LSN_DEF_TRACKBAR_HEIGHT + 3)
#define LSN_STD_CONT_BUTTON_LABEL_W						(25)
#define LSN_STD_CONT_BUTTON_BUTTON_W					(100 - (LSN_STD_CONT_BUTTON_LABEL_W))
#define LSN_STD_CONT_BUTTON_FULL_W						(LSN_STD_CONT_BUTTON_LABEL_W + LSN_STD_CONT_BUTTON_BUTTON_W)
#define LSN_STD_CONT_BUTTON_GROUP_W						(LSN_STD_CONT_BUTTON_FULL_W + LSN_GROUP_LEFT + LSN_GROUP_RIGHT)
#define LSN_STD_CONT_BUTTON_GROUP_H						(LSN_STD_CONT_BUTTON_FULL_H + LSN_GROUP_TOP + LSN_GROUP_BOTTOM)
#define LSN_STD_CONT_DPAD_LEFT							LSN_LEFT_JUST
#define LSN_STD_CONT_DPAD_TOP							LSN_TOP_JUST
#define LSN_STD_CONT_DPAD_W								(LSN_STD_CONT_BUTTON_GROUP_W * 2 + LSN_LEFT_JUST * 20)
#define LSN_STD_CONT_DPAD_H								(LSN_STD_CONT_BUTTON_GROUP_H * 3 + LSN_TOP_JUST * 4)
#define LSN_STD_CONT_DPAD_H_MIDDLE						(LSN_STD_CONT_DPAD_W / 2)
#define LSN_STD_CONT_DPAD_V_MIDDLE						(LSN_STD_CONT_DPAD_H / 2)
#define LSN_STD_CONT_DPAD_GROUP_W						(LSN_STD_CONT_DPAD_W + LSN_GROUP_LEFT + LSN_GROUP_RIGHT)
#define LSN_STD_CONT_DPAD_GROUP_H						(LSN_STD_CONT_DPAD_H + LSN_GROUP_TOP + LSN_GROUP_BOTTOM)
#define LSN_STD_CONT_SS_LEFT							(LSN_STD_CONT_DPAD_LEFT + LSN_STD_CONT_DPAD_GROUP_W + LSN_LEFT_JUST * 2)
#define LSN_STD_CONT_SS_TOP								(LSN_STD_CONT_DPAD_TOP + LSN_STD_CONT_DPAD_GROUP_H - LSN_GROUP_TOP - LSN_GROUP_BOTTOM - LSN_STD_CONT_BUTTON_GROUP_H)
#define LSN_STD_CONT_SS_START_LEFT						(LSN_STD_CONT_BUTTON_GROUP_W + LSN_LEFT_JUST * 4)
#define LSN_STD_CONT_SS_GROUP_W							(LSN_STD_CONT_SS_START_LEFT + LSN_STD_CONT_BUTTON_GROUP_W + LSN_GROUP_LEFT + LSN_GROUP_RIGHT)
#define LSN_STD_CONT_SS_GROUP_H							(LSN_STD_CONT_BUTTON_GROUP_H + LSN_GROUP_TOP + LSN_GROUP_BOTTOM)
#define LSN_STD_CONT_BUT_GROUP_W						LSN_STD_CONT_SS_GROUP_W
#define LSN_STD_CONT_BUT_GROUP_H						LSN_STD_CONT_SS_GROUP_H
#define LSN_STD_CONT_BUT_LEFT							(LSN_STD_CONT_SS_LEFT + LSN_STD_CONT_SS_GROUP_W + LSN_LEFT_JUST * 2)
#define LSN_STD_CONT_BUT_TOP							(LSN_STD_CONT_DPAD_TOP + (LSN_STD_CONT_DPAD_GROUP_H / 2) - (LSN_STD_CONT_BUT_GROUP_H / 2))
#define LSN_STD_CONT_BUT_A_LEFT							LSN_STD_CONT_SS_START_LEFT

#define LSN_STD_CONT_W									(LSN_LEFT_JUST + LSN_LEFT_JUST + LSN_STD_CONT_BUT_LEFT + LSN_STD_CONT_BUT_GROUP_W + LSN_LEFT_JUST + LSN_LEFT_JUST)
#define LSN_STD_CONT_H									(LSN_STD_CONT_DPAD_GROUP_H + 20)

	class												CMainWindow;
	
	/**
	 * Class CStdControllerPageLayout
	 * \brief A dialog shaped like a standard controller.
	 *
	 * Description: A dialog shaped like a standard controller.
	 */
	class CStdControllerPageLayout {
	public :
		// == Enumerations.
		// Control ID's.
		enum LSN_STD_CONTROLLER_PAGE_IDS : WORD {
			LSN_SCPI_NONE,

			LSN_SCPI_GROUP								= 0,
			LSN_SCPI_LABEL								= 1,
			LSN_SCPI_BUTTON								= 2,
			LSN_SCPI_TURBO_LABEL						= 3,
			LSN_SCPI_TURBO_BUTTON						= 4,
			LSN_SCPI_TURBO_COMBO						= 5,
			LSN_SCPI_TURBO_DEADZONE_LABEL				= 6,
			LSN_SCPI_TURBO_DEADZONE_TRACKBAR			= 7,
			LSN_SCPI_MAINWINDOW							= 0x4690,

			LSN_SCPI_DPAD_GROUP,

			LSN_SCPI_BUTTON_UP_START,
			LSN_SCPI_BUTTON_UP_GROUP					= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_UP_LABEL					= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_UP_BUTTON					= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_UP_TURBO_LABEL				= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_UP_TURBO_BUTTON				= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_UP_TURBO_COMBO				= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_UP_DEADZONE_LABEL			= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_UP_DEADZONE_TRACKBAR		= LSN_SCPI_BUTTON_UP_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_BUTTON_LEFT_START,
			LSN_SCPI_BUTTON_LEFT_GROUP					= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_LEFT_LABEL					= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_LEFT_BUTTON					= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_LEFT_TURBO_LABEL			= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_LEFT_TURBO_BUTTON			= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_LEFT_TURBO_COMBO			= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_LEFT_DEADZONE_LABEL			= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_LEFT_DEADZONE_TRACKBAR		= LSN_SCPI_BUTTON_LEFT_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_BUTTON_RIGHT_START,
			LSN_SCPI_BUTTON_RIGHT_GROUP					= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_RIGHT_LABEL					= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_RIGHT_BUTTON				= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_RIGHT_TURBO_LABEL			= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_RIGHT_TURBO_BUTTON			= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_RIGHT_TURBO_COMBO			= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_RIGHT_DEADZONE_LABEL		= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_RIGHT_DEADZONE_TRACKBAR		= LSN_SCPI_BUTTON_RIGHT_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_BUTTON_DOWN_START,
			LSN_SCPI_BUTTON_DOWN_GROUP					= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_DOWN_LABEL					= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_DOWN_BUTTON					= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_DOWN_TURBO_LABEL			= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_DOWN_TURBO_BUTTON			= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_DOWN_TURBO_COMBO			= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_DOWN_DEADZONE_LABEL			= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_DOWN_DEADZONE_TRACKBAR		= LSN_SCPI_BUTTON_DOWN_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_SS_GROUP,

			LSN_SCPI_BUTTON_SELECT_START,
			LSN_SCPI_BUTTON_SELECT_GROUP				= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_SELECT_LABEL				= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_SELECT_BUTTON				= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_SELECT_TURBO_LABEL			= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_SELECT_TURBO_BUTTON			= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_SELECT_TURBO_COMBO			= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_SELECT_DEADZONE_LABEL		= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_SELECT_DEADZONE_TRACKBAR	= LSN_SCPI_BUTTON_SELECT_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_BUTTON_START_START,
			LSN_SCPI_BUTTON_START_GROUP					= LSN_SCPI_BUTTON_START_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_START_LABEL					= LSN_SCPI_BUTTON_START_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_START_BUTTON				= LSN_SCPI_BUTTON_START_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_START_TURBO_LABEL			= LSN_SCPI_BUTTON_START_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_START_TURBO_BUTTON			= LSN_SCPI_BUTTON_START_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_START_TURBO_COMBO			= LSN_SCPI_BUTTON_START_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_START_DEADZONE_LABEL		= LSN_SCPI_BUTTON_START_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_START_DEADZONE_TRACKBAR		= LSN_SCPI_BUTTON_START_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_BUTTON_GROUP,

			LSN_SCPI_BUTTON_A_START,
			LSN_SCPI_BUTTON_A_GROUP						= LSN_SCPI_BUTTON_A_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_A_LABEL						= LSN_SCPI_BUTTON_A_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_A_BUTTON					= LSN_SCPI_BUTTON_A_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_A_TURBO_LABEL				= LSN_SCPI_BUTTON_A_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_A_TURBO_BUTTON				= LSN_SCPI_BUTTON_A_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_A_TURBO_COMBO				= LSN_SCPI_BUTTON_A_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_A_DEADZONE_LABEL			= LSN_SCPI_BUTTON_A_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_A_DEADZONE_TRACKBAR			= LSN_SCPI_BUTTON_A_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,

			LSN_SCPI_BUTTON_B_START,
			LSN_SCPI_BUTTON_B_GROUP						= LSN_SCPI_BUTTON_B_START + LSN_SCPI_GROUP,
			LSN_SCPI_BUTTON_B_LABEL						= LSN_SCPI_BUTTON_B_START + LSN_SCPI_LABEL,
			LSN_SCPI_BUTTON_B_BUTTON					= LSN_SCPI_BUTTON_B_START + LSN_SCPI_BUTTON,
			LSN_SCPI_BUTTON_B_TURBO_LABEL				= LSN_SCPI_BUTTON_B_START + LSN_SCPI_TURBO_LABEL,
			LSN_SCPI_BUTTON_B_TURBO_BUTTON				= LSN_SCPI_BUTTON_B_START + LSN_SCPI_TURBO_BUTTON,
			LSN_SCPI_BUTTON_B_TURBO_COMBO				= LSN_SCPI_BUTTON_B_START + LSN_SCPI_TURBO_COMBO,
			LSN_SCPI_BUTTON_B_DEADZONE_LABEL			= LSN_SCPI_BUTTON_B_START + LSN_SCPI_TURBO_DEADZONE_LABEL,
			LSN_SCPI_BUTTON_B_DEADZONE_TRACKBAR			= LSN_SCPI_BUTTON_B_START + LSN_SCPI_TURBO_DEADZONE_TRACKBAR,



			LSN_SCPI_INPUT_DEVICES_GROUP,
			LSN_SCPI_INPUT_DEVICES_LISTVIEW,

			LSN_SCPI_OK,
			LSN_SCPI_CANCEL,
		};


		// == Functions.
		/**
		 * Creates the page.
		 *
		 * \param _pwParent The parent of the page.
		 * \param _ioOptions The input options to potentially modify.
		 * \param _pmwMainWindow A pointer to the main window for USB controller access.
		 * \param _stIdx The page's configuration index.
		 * \return Returns the created widget.
		 */
		static CWidget *								CreatePage( CWidget * _pwParent, LSN_INPUT_OPTIONS &_ioOptions, lsn::CMainWindow * _pmwMainWindow, size_t _stIdx );


	protected :
		// == Members.
		/** The layout for the per-game-setup panel. */
		static LSW_WIDGET_LAYOUT						m_wlPage[];


		// == Functions.
		/**
		 * Creates the pages.
		 *
		 * \param _pwParent The parent widget.
		 * \param _ioOptions The input options to potentially modify.
		 * \param _pmwMainWindow A pointer to the main window for USB controller access.
		 * \param _stIdx The page's configuration index.
		 * \param _pwlLayout The page layout.
		 * \param _sTotal The number of items to which _pwlLayout points.
		 * \return Returns the created page.
		 */
		static CWidget *								CreatePage( CWidget * _pwParent, LSN_INPUT_OPTIONS &_ioOptions, lsn::CMainWindow * _pmwMainWindow, size_t _stIdx, const LSW_WIDGET_LAYOUT * _pwlLayout, size_t _sTotal );
 		
	};

}	// namespace lsn

#endif	// #ifdef LSN_USE_WINDOWS
