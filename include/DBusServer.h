//
// Created by mkd on 9/20/22.
//

#ifndef GANYMEDE_DBUSMANAGER_H
#define GANYMEDE_DBUSMANAGER_H


#include <functional>
#include <gio/gio.h>

#include "Types.h"



namespace ganymede {

	class DBusServer {

	public:

		/*********************************************************************************************
			Types
		 *********************************************************************************************/

		using TileCallbackFunction = std::function<void(DBusServer& dbusServer,
														unsigned widthDivision,
														unsigned widthMultiplier,
														unsigned xDivision,
														unsigned xMultiplier,
														unsigned xOffset,
														unsigned heightDivision,
														unsigned heightMultiplier,
														unsigned yDivision,
														unsigned yMultiplier,
														unsigned yOffset)>;
		using MaximizeCallbackFunction = std::function<void(DBusServer& dbusServer, POSITIONAL_FLAG flags)>;
		using FillCallbackFunction = std::function<void(DBusServer& dbusServer, POSITIONAL_FLAG flags)>;
		using ExpandCallbackFunction = std::function<void(DBusServer& dbusServer, POSITIONAL_FLAG flags)>;
		using SnapCallbackFunction = std::function<void(DBusServer& dbusServer, POSITIONAL_FLAG flags)>;
		using MoveCallbackFunction = std::function<void(DBusServer& dbusServer, POSITIONAL_FLAG flags)>;
		using HideCallbackFunction = std::function<void(DBusServer& dbusServer)>;
		using FullscreenCallbackFunction = std::function<void(DBusServer& dbusServer)>;
		using ShowDesktopCallbackFunction = std::function<void(DBusServer& dbusServer)>;
		using DebugCallbackFunction = std::function<void(DBusServer& dbusServer)>;

		/*********************************************************************************************
			Lifecycle
		 *********************************************************************************************/

		DBusServer();

		/*********************************************************************************************
			Public
		 *********************************************************************************************/

		GDBusNodeInfo* GetIntrospectionData(); // for static member

		TileCallbackFunction tileCallback() const;
		void tileCallback(TileCallbackFunction function);

		MaximizeCallbackFunction maximizeCallback() const;
		void maximizeCallback(MaximizeCallbackFunction function);

		FillCallbackFunction fillCallback() const;
		void fillCallback(FillCallbackFunction function);

		ExpandCallbackFunction expandCallback() const;
		void expandCallback(ExpandCallbackFunction function);

		SnapCallbackFunction snapCallback() const;
		void snapCallback(SnapCallbackFunction function);

		MoveCallbackFunction moveCallback() const;
		void moveCallback(MoveCallbackFunction function);

		HideCallbackFunction hideCallback() const;
		void hideCallback(HideCallbackFunction function);

		FullscreenCallbackFunction fullscreenCallback() const;
		void fullscreenCallback(FullscreenCallbackFunction function);

		ShowDesktopCallbackFunction showDesktopCallback() const;
		void showDesktopCallback(ShowDesktopCallbackFunction function);

		DebugCallbackFunction debugCallback() const;
		void debugCallback(DebugCallbackFunction function);

	private:

		/*********************************************************************************************
			Private
		 *********************************************************************************************/

		GDBusNodeInfo* 						_introspectionData;

		TileCallbackFunction 				_tileCallback;
		MaximizeCallbackFunction 			_maximizeCallback;
		FillCallbackFunction 				_fillCallback;
		ExpandCallbackFunction				_expandCallback;
		SnapCallbackFunction 				_snapCallback;
		MoveCallbackFunction 				_moveCallback;
		HideCallbackFunction 				_hideCallback;
		FullscreenCallbackFunction 			_fullscreenCallback;
		ShowDesktopCallbackFunction 		_showDesktopCallback;
		DebugCallbackFunction 				_debugCallback;
	};


#endif //GANYMEDE_DBUSMANAGER_H

}
