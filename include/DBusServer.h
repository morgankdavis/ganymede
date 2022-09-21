//
// Created by mkd on 9/20/22.
//

#ifndef GANYMEDE_DBUSMANAGER_H
#define GANYMEDE_DBUSMANAGER_H


#include <gio/gio.h>


namespace ganymede {

	class DBusServer {

	public:

		DBusServer();

		GDBusNodeInfo* GetIntrospectionData();

	private:

		GDBusNodeInfo* _introspectionData;
	};


#endif //GANYMEDE_DBUSMANAGER_H

}
