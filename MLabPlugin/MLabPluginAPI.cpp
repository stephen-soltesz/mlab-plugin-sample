/**********************************************************\

  Auto-generated MLabPluginAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "MLabPluginAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant MLabPluginAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant MLabPluginAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo("So far, you clicked this many times: ", n++);

    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn MLabPluginPtr MLabPluginAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
MLabPluginPtr MLabPluginAPI::getPlugin()
{
    MLabPluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string MLabPluginAPI::get_testString()
{
    return m_testString;
}

void MLabPluginAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string MLabPluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void MLabPluginAPI::testEvent()
{
    fire_test();
}
