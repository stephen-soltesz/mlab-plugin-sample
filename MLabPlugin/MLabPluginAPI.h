/**********************************************************\

  Auto-generated MLabPluginAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "MLabPlugin.h"
#include <boost/thread/thread.hpp>

#ifndef H_MLabPluginAPI
#define H_MLabPluginAPI

class MLabPluginAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn MLabPluginAPI::MLabPluginAPI(const MLabPluginPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    MLabPluginAPI(const MLabPluginPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        registerMethod("echo",      make_method(this, &MLabPluginAPI::echo));
        registerMethod("testEvent", make_method(this, &MLabPluginAPI::testEvent));
        registerMethod("add",       make_method(this, &MLabPluginAPI::add));
        registerMethod("webtest",   make_method(this, &MLabPluginAPI::webtest));
        registerMethod("transferTest",   make_method(this, &MLabPluginAPI::transferTest));
        registerMethod("status",      make_method(this, &MLabPluginAPI::status));
        //registerMethod("hostname",  make_method(this, &MLabPluginAPI::add));
        
        // Read-write property
        registerProperty("testString",
                         make_property(this,
                                       &MLabPluginAPI::get_testString,
                                       &MLabPluginAPI::set_testString));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &MLabPluginAPI::get_version));
        registerProperty("hostname",
                         make_property(this,
                                       &MLabPluginAPI::get_hostname));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn MLabPluginAPI::~MLabPluginAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~MLabPluginAPI() {};

    MLabPluginPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    FB::variant webtest(const std::string& val);
    //FB::VariantMap transferTest(const std::string& hostname, long h_length);
    void transferTest(const std::string& hostname, long h_length, const FB::JSObjectPtr& callback);
    void transferTest_thread(const std::string& hostname, long h_length, const FB::JSObjectPtr& callback);
    FB::variant status(const std::string& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));
    FB_JSAPI_EVENT(status, 1, (const FB::variant&));

    // Method test-event
    void testEvent();

    // adding a method for the first time..
    long add(long a, long b, long c);

    FB::variant get_hostname();

private:
    MLabPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_MLabPluginAPI

