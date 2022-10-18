//
// Created by mkd on 9/20/22.
//

#include "DBusServer.h"

#include <stdio.h>
#include <libwnck/libwnck.h>
//#include <gio/gio.h>
//#include <stdlib.h>


using namespace std;
using namespace ganymede;


// test: dbus-send --session --print-reply --type=method_call --dest=net.mkd.Ganymede /net/mkd/Ganymede net.mkd.Ganymede.DoSomething int32:1
// format strings: https://docs.gtk.org/glib/gvariant-format-strings.html
static const gchar introspectionXML[] =
		"<node>"
		"  <interface name='net.mkd.Ganymede'>"
		"    <annotation name='net.mkd.Annotation' value='OnInterface'/>"
		"    <annotation name='net.mkd.Annotation' value='AlsoOnInterface'/>"
		"    <method name='DoSomething'>"
		"      <annotation name='net.mkd.Annotation' value='OnMethod'/>"
		"      <arg type='i' name='action' direction='in'/>"
		"      <arg type='i' name='response' direction='out'/>"
		"    </method>"
		"    <method name='Tile'>"
		"      <annotation name='net.mkd.Annotation' value='OnMethod'/>"
		"      <arg type='u' name='widthDivision' direction='in'/>"
		"      <arg type='u' name='widthMultiplier' direction='in'/>"
		"      <arg type='u' name='xDivision' direction='in'/>"
		"      <arg type='u' name='xMultiplier' direction='in'/>"
		"      <arg type='u' name='xOffset' direction='in'/>"
		"      <arg type='u' name='heightDivision' direction='in'/>"
		"      <arg type='u' name='heightMultiplier' direction='in'/>"
		"      <arg type='u' name='yDivision' direction='in'/>"
		"      <arg type='u' name='yMultiplier' direction='in'/>"
		"      <arg type='u' name='yOffset' direction='in'/>"
		"    </method>"
		"  </interface>"
		"</node>";



static void on_bus_acquired(GDBusConnection* connection,
							const gchar* name,
							gpointer user_data);
static void on_name_acquired(GDBusConnection* connection,
							 const gchar* name,
							 gpointer user_data);
static void on_name_lost(GDBusConnection* connection,
						 const gchar* name,
						 gpointer user_data);
//static gboolean on_timeout_cb(gpointer user_data);
static void handle_method_call(GDBusConnection* connection,
							   const gchar* sender,
							   const gchar* object_path,
							   const gchar* interface_name,
							   const gchar* method_name,
							   GVariant* parameters,
							   GDBusMethodInvocation* invocation,
							   gpointer user_data);
static GVariant* handle_get_property(GDBusConnection* connection,
									 const gchar* sender,
									 const gchar* object_path,
									 const gchar* interface_name,
									 const gchar* property_name,
									 GError** error,
									 gpointer user_data);
static gboolean handle_set_property(GDBusConnection* connection,
									const gchar* sender,
									const gchar* object_path,
									const gchar* interface_name,
									const gchar* property_name,
									GVariant* value,
									GError** error,
									gpointer user_data);

static void on_bus_acquired(GDBusConnection* connection,
							const gchar* name,
							gpointer user_data) {
	printf("on_bus_acquired()\n");

	guint registration_id;

	DBusServer* manager = (DBusServer*)user_data;

	/* for now */
	static const GDBusInterfaceVTable interface_vtable =
			{
					handle_method_call,
					handle_get_property,
					handle_set_property
			};

	registration_id = g_dbus_connection_register_object(connection,
														"/net/mkd/Ganymede",
														manager->GetIntrospectionData()->interfaces[0],
														&interface_vtable,
														user_data,  /* user_data */
														NULL,  /* user_data_free_func */
														NULL); /* GError** */
}

static void on_name_acquired(GDBusConnection* connection,
							 const gchar* name,
							 gpointer user_data) {
	printf("on_name_acquired()\n");
}

static void on_name_lost(
		GDBusConnection* connection,
		const gchar* name,
		gpointer user_data) {
	printf("on_name_lost()\n");
}

static void handle_method_call(GDBusConnection* connection,
							   const gchar* sender,
							   const gchar* object_path,
							   const gchar* interface_name,
							   const gchar* method_name,
							   GVariant* parameters,
							   GDBusMethodInvocation* invocation,
							   gpointer user_data) {
	printf("handle_method_call(): %s\n", method_name);

	if (g_strcmp0(method_name, "Tile") == 0) {



		DBusServer* server = (DBusServer*)user_data;

		GError* local_error;

		guint32 widthDivision, widthMultiplier, xDivision, xMultiplier, xOffset,
			heightDivision, heightMultiplier, yDivision, yMultiplier, yOffset;

		g_variant_get(parameters, "(uuuuuuuuuu)",
					  &widthDivision, &widthMultiplier, &xDivision, &xMultiplier, &xOffset,
					  &heightDivision, &heightMultiplier, &yDivision, &yMultiplier, &yOffset);
		printf("widthDivision: %u\n"
			   "widthMultiplier: %u\n"
			   "xDivision: %u\n"
			   "xMultiplier: %u\n"
			   "xOffset: %u\n"
			   "heightDivision: %u\n"
			   "heightMultiplier: %u\n"
			   "yDivision: %u\n"
			   "yMultiplier: %u\n"
			   "yOffset: %u\n",
			   widthDivision, widthMultiplier, xDivision, xMultiplier, xOffset,
			   heightDivision, heightMultiplier, yDivision, yMultiplier, yOffset);

		if (server->tileCallback()) {
			(server->tileCallback())(*server,
					widthDivision, widthMultiplier, xDivision, xMultiplier, xOffset,
					heightDivision, heightMultiplier, yDivision, yMultiplier, yOffset);
		}

//		g_variant_get(parameters, "(u)", &widthDivision);
//		printf("widthDivision: %u\n", widthDivision);
//
//		g_variant_get(parameters, "(u)", &xDivision);
//		printf("xDivision: %u\n", xDivision);
//
//		g_variant_get(parameters, "(u)", &xOffset);
//		printf("xOffset: %u\n", xOffset);
//
//		g_variant_get(parameters, "(u)", &heightDivision);
//		printf("heightDivision: %u\n", heightDivision);
//
//		g_variant_get(parameters, "(u)", &yDivision);
//		printf("yDivision: %u\n", yDivision);
//
//		g_variant_get(parameters, "(u)", &yOffset);
//		printf("yOffset: %u\n", yOffset);


//		WnckScreen* screen = wnck_screen_get_default();
//		WnckWindow* activeWin = wnck_screen_get_active_window(screen);
//		printf("active win class group: %s\n", wnck_window_get_class_group_name(activeWin));
//
//		switch (action) {
//			case 0:
//				printf("SETTING GEOMETRY\n");
//
//				if (wnck_window_is_fullscreen(activeWin)) wnck_window_set_fullscreen(activeWin, false);
//				if (wnck_window_is_maximized(activeWin)) wnck_window_unmaximize(activeWin);
//
//				wnck_window_set_geometry(activeWin,
//										 WNCK_WINDOW_GRAVITY_CURRENT,
//										 (WnckWindowMoveResizeMask)
//												 (WNCK_WINDOW_CHANGE_X
//												  | WNCK_WINDOW_CHANGE_Y
//												  | WNCK_WINDOW_CHANGE_WIDTH
//												  | WNCK_WINDOW_CHANGE_HEIGHT),
//										 128, 128, 480, 240);
//				break;
//			case 1:
//				printf("SETTING GEOMETRY\n");
//
//				int activeX, activeY, activeW, activeH;
//				wnck_window_get_geometry(activeWin, &activeX, &activeY, &activeW, &activeH);
//				printf("%d %d %d %d\n", activeX, activeY, activeW, activeH);
//				break;
//			case 2:
//				break;
//			default:
//				break;
//		}
//
//		//g_free(actionAsString);
//
//		g_dbus_method_invocation_return_value(invocation, g_variant_new ("(i)", 0));
	}
	else if (g_strcmp0(method_name, "DoSomething") == 0) {

		// used for development and debugging

		GError* local_error;
		gint32 action;
		gchar* actionAsString;

		g_variant_get(parameters, "(i)", &action);
		actionAsString = g_strdup_printf("action: %i\n", action);

		WnckHandle* wnckHandle = wnck_handle_new(WNCK_CLIENT_TYPE_APPLICATION);
//		WnckScreen* screen = wnck_screen_get_default();
		WnckScreen* screen = wnck_handle_get_default_screen(wnckHandle);
		WnckWindow* activeWin = wnck_screen_get_active_window(screen);
		printf("active win class group: %s\n", wnck_window_get_class_group_name(activeWin));

		switch (action) {
			case 0:
				printf("SETTING GEOMETRY\n");

				if (wnck_window_is_fullscreen(activeWin)) wnck_window_set_fullscreen(activeWin, false);
				if (wnck_window_is_maximized(activeWin)) wnck_window_unmaximize(activeWin);

				wnck_window_set_geometry(activeWin,
										 WNCK_WINDOW_GRAVITY_CURRENT,
										 (WnckWindowMoveResizeMask)
												 (WNCK_WINDOW_CHANGE_X
												  | WNCK_WINDOW_CHANGE_Y
												  | WNCK_WINDOW_CHANGE_WIDTH
												  | WNCK_WINDOW_CHANGE_HEIGHT),
										 128, 128, 480, 240);
				break;
			case 1:
				printf("SETTING GEOMETRY\n");

				int activeX, activeY, activeW, activeH;
				wnck_window_get_geometry(activeWin, &activeX, &activeY, &activeW, &activeH);
				printf("%d %d %d %d\n", activeX, activeY, activeW, activeH);
				break;
			case 2:
				break;
			default:
				break;
		}

		g_free(actionAsString);

		g_dbus_method_invocation_return_value(invocation, g_variant_new ("(i)", 0));
	}
}

static GVariant* handle_get_property(GDBusConnection* connection,
									 const gchar* sender,
									 const gchar* object_path,
									 const gchar* interface_name,
									 const gchar* property_name,
									 GError** error,
									 gpointer user_data) {
	printf("handle_get_property()\n");
}

static gboolean handle_set_property(GDBusConnection* connection,
									const gchar* sender,
									const gchar* object_path,
									const gchar* interface_name,
									const gchar* property_name,
									GVariant* value,
									GError** error,
									gpointer user_data) {
	printf("handle_set_property()\n");
}


DBusServer::DBusServer() {
	printf("DBusServer()\n");

	guint owner_id;

	g_type_init();

	_introspectionData = g_dbus_node_info_new_for_xml(introspectionXML, NULL);

	owner_id = g_bus_own_name(G_BUS_TYPE_SESSION,
							  "net.mkd.Ganymede",
							  G_BUS_NAME_OWNER_FLAGS_NONE,
							  on_bus_acquired,
							  on_name_acquired,
							  on_name_lost,
							  this,
							  NULL);
}

GDBusNodeInfo* DBusServer::GetIntrospectionData() {
	return _introspectionData;
}

DBusServer::TileCallbackFunction DBusServer::tileCallback() const {
	return _tileCallback;
}

void DBusServer::tileCallback(TileCallbackFunction function) {
	_tileCallback = function;
}

DBusServer::MaximizeCallbackFunction DBusServer::maximizeCallback() const {
	return _maximizeCallback;
}

void DBusServer::maximizeCallback(MaximizeCallbackFunction function) {
	_maximizeCallback = function;
}

DBusServer::FillCallbackFunction DBusServer::fillCallback() const {
	return _fillCallback;
}

void DBusServer::fillCallback(FillCallbackFunction function) {
	_fillCallback = function;
}

DBusServer::ExpandCallbackFunction DBusServer::expandCallback() const {
	return _expandCallback;
}

void DBusServer::expandCallback(ExpandCallbackFunction function) {
	_expandCallback = function;
}

DBusServer::SnapCallbackFunction DBusServer::snapCallback() const {
	return _snapCallback;
}

void DBusServer::snapCallback(SnapCallbackFunction function) {
	_snapCallback = function;
}

DBusServer::MoveCallbackFunction DBusServer::moveCallback() const {
	return _moveCallback;
}

void DBusServer::moveCallback(MoveCallbackFunction function) {
	_moveCallback = function;
}

DBusServer::HideCallbackFunction DBusServer::hideCallback() const {
	return _hideCallback;
}

void DBusServer::hideCallback(HideCallbackFunction function) {
	_hideCallback = function;
}

DBusServer::FullscreenCallbackFunction DBusServer::fullscreenCallback() const {
	return _fullscreenCallback;
}

void DBusServer::fullscreenCallback(FullscreenCallbackFunction function) {
	_fullscreenCallback = function;
}

DBusServer::ShowDesktopCallbackFunction DBusServer::showDesktopCallback() const {
	return _showDesktopCallback;
}

void DBusServer::showDesktopCallback(ShowDesktopCallbackFunction function) {
	_showDesktopCallback = function;
}

DBusServer::DebugCallbackFunction DBusServer::debugCallback() const {
	return _debugCallback;
}

void DBusServer::debugCallback(DebugCallbackFunction function) {
	_debugCallback = function;
}
