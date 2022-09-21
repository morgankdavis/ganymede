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


// dbus-send --session --print-reply --type=method_call --dest=org.gtk.GDBus.Ganymede /org/gtk/GDBus/Ganymede org.gtk.GDBus.Ganymede.DoSomething int32:3
static const gchar introspectionXML[] =
		"<node>"
		"  <interface name='org.gtk.GDBus.Ganymede'>"
		"    <annotation name='org.gtk.GDBus.Annotation' value='OnInterface'/>"
		"    <annotation name='org.gtk.GDBus.Annotation' value='AlsoOnInterface'/>"
		"    <method name='DoSomething'>"
		"      <annotation name='org.gtk.GDBus.Annotation' value='OnMethod'/>"
		"      <arg type='i' name='action' direction='in'/>"
		"      <arg type='i' name='response' direction='out'/>"
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



DBusServer::DBusServer() {
	printf("DBusServer()\n");

	guint owner_id;

	g_type_init();

	_introspectionData = g_dbus_node_info_new_for_xml(introspectionXML, NULL);

	owner_id = g_bus_own_name(G_BUS_TYPE_SESSION,
							  "org.gtk.GDBus.Ganymede",
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
														"/org/gtk/GDBus/Ganymede",
														manager->GetIntrospectionData()->interfaces[0],
														&interface_vtable,
														NULL,  /* user_data */
														NULL,  /* user_data_free_func */
														NULL); /* GError** */

	/* swap value of properties Foo and Bar every two seconds */
//	g_timeout_add_seconds(2,
//						  on_timeout_cb,
//						  connection);
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

//static gboolean on_timeout_cb(gpointer user_data) {
//	printf("on_timeout_cb()\n");
//}

static void handle_method_call(GDBusConnection* connection,
							   const gchar* sender,
							   const gchar* object_path,
							   const gchar* interface_name,
							   const gchar* method_name,
							   GVariant* parameters,
							   GDBusMethodInvocation* invocation,
							   gpointer user_data) {
	printf("handle_method_call()\n");

	if (g_strcmp0(method_name, "DoSomething") == 0) {

		GError* local_error;
		gint32 action;
		gchar* actionAsString;

		g_variant_get(parameters, "(i)", &action);
		actionAsString = g_strdup_printf("action: %i\n", action);

		WnckScreen* screen = wnck_screen_get_default();
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

//		local_error = NULL;
//		g_dbus_connection_emit_signal (connection,
//									   NULL,
//									   object_path,
//									   interface_name,
//									   "VelocityChanged",
//									   g_variant_new ("(ds)",
//													  speed_in_mph,
//													  speed_as_string),
//									   &local_error);
//		g_assert_no_error (local_error);
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


