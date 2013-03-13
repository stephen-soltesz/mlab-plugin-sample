/**********************************************************\

  Auto-generated MLabPluginAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "MLabPluginAPI.h"
#include "curl/curl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <boost/asio.hpp>

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#define _ITERATOR_DEBUG_LEVEL 0

using namespace boost::posix_time;
using boost::asio::ip::tcp;
#include "lib.hpp"

//tcp::resolver::query query("test" ,1234);

#define PORT        12345
#define DIRSIZE     8192
#define min(x,y)    (x < y ? x : y)
#define OK          0

#if 0
double get_ts() {
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    return (tv1.tv_sec + tv1.tv_usec/1.0e6);
}

int status(MLabPluginAPI *t, double tdiff, int amount) {
    char buf[100];
    snprintf(buf, sizeof(buf), "% 7.3f sec, %8d bytes -- %7.3f Mbps\n", 
             tdiff, amount, ((8.0*amount)/tdiff)/1.0e6);
    fprintf(stderr, buf);
    t->status(std::string(buf));// fire_status(buf);
    return 0;
}

int send_length(int sd, int h_length) {
    int n_length = htonl(h_length); 
    /* send length requested from server */
    if (send(sd, &n_length, sizeof(n_length), 0) == -1) {
        perror("send length");
        return -1;
    }
    return OK;
}

int recv_data(MLabPluginAPI *t, int sd, int h_length, FB::VariantMap& retMap) {
    double t0=0;
    double t1=0;
    double t2=0;
    double tdiff=0;
    double last_status=0;
    struct timeval tv1;
    struct timeval tv2;
    char    data[DIRSIZE];
    int    h_recvd=0;
    int    recvd_length;
    int    ret=0;

    t1 = get_ts();
    h_recvd = 0;

    while ( h_recvd < h_length ) {
        recvd_length = min(sizeof(data), h_length-h_recvd);
        ret = recv(sd, data, recvd_length , 0); 
        if ( ret == -1 ) {
            perror("receiving failed:");
            break;
        }
        if ( ret == 0 ) {
            fprintf(stderr, "ret==0\n");
            fprintf(stderr, "received: %d\n", h_length);
            fprintf(stderr, "received: %d\n", h_recvd);
            retMap["status"] = "error";
            break;
        }
        h_recvd += ret;
        t2 = get_ts();
        tdiff = t2-t1;
        if ( last_status + 1 < tdiff ) {
            status(t, tdiff, h_recvd);
            fprintf(stderr, "status time: %f\n", get_ts()-t2);
            snprintf(data, sizeof(data), "status time: %f\n", get_ts()-t2);
            t->log(std::string(data));
            last_status = tdiff;
        }
    }

    t2 = get_ts();
    tdiff = t2-t1;
    status(t, tdiff, h_recvd);

    t->status("done\n");
    retMap["requested"] = h_length;
    retMap["received"] = h_recvd;
    retMap["time"] = t2-t1;
    retMap["mbps"] = ((8.0*h_recvd)/((float)(t2-t1)))/1e6;
    fprintf(stderr, "requested: %d\n", h_length);
    fprintf(stderr, "received:  %d\n", h_recvd);
    fprintf(stderr, "t2-t1:     %f\n", t2-t1);
    fprintf(stderr, "Mbits/sec: %0.6f\n", ((8.0*h_recvd)/((float)(t2-t1)))/1e6);

    return OK;
}

int connect_to_server(const char *hostname)
{
    struct sockaddr_in pin;
    struct hostent *hp;
    int     sd=0;

    /* go find out about the desired host machine */
    if ((hp = gethostbyname(hostname)) == 0) {
        perror("gethostbyname");
        return -1;
    }

    /* fill in the socket structure with host information */
    memset(&pin, 0, sizeof(pin));
    pin.sin_family = AF_INET;
    pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
    pin.sin_port = htons(PORT);

    /* grab an Internet domain socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    /* connect to PORT on HOST */
    if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
        perror("connect");
        return -1;
    }

    return sd;
}
#endif

/* int main(int argc, char **argv)
{
    char     hostname[100];
    int      sd;
    uint32_t n_length=0;
    uint32_t h_length=0;

    if (argc!=3) { 
        fprintf(stderr, "%s <hostname> <size>\n", argv[0]);
        exit(1);
    }
*/
 
void MLabPluginAPI::transferTest(const std::string& hostname, long h_length, const FB::JSObjectPtr &callback)
{
    boost::thread m_thread;
    m_thread = boost::thread(boost::bind(&MLabPluginAPI::transferTest_thread, this, hostname, h_length, callback));
    m_thread.detach();  // cleans up on exit
}

//FB::variant MLabPluginAPI::transferTest(const std::string& hostname, long h_length)
//void MLabPluginAPI::transferTest_thread(const std::string& hostname, long h_length, FB::JSObjectPtr &callback)
void MLabPluginAPI::transferTest_thread(const std::string& hostname, long h_length, const FB::JSObjectPtr &callback)
{
    FB::VariantMap retMap;
    int ret=0;
    SampleTestClient stc(hostname, this);

    retMap["status"] = "ok";

    ret = stc.run_client_test(hostname, h_length, DIRECTION_CLIENT_DOWNLOAD);
    if ( ret != OK ) {
        retMap["status"] = "error";
        goto transfer_end;
    }
#if 0
    sd = connect_to_server(hostname.c_str());
    if ( sd == -1 ) {
        perror("socket");
        retMap["status"] = "error";
        goto transfer_end;
    }

    if ( send_length(sd, h_length) != OK ) {
        retMap["status"] = "error";
        goto transfer_end;
    }

    if ( recv_data(this, sd, h_length, retMap) != OK ) {
        retMap["status"] = "error";
        goto transfer_end;
    }
#endif

transfer_end:
    //close(sd);
    //callback->InvokeAsync("", FB::variant_list_of(shared_from_this())(retMap));
    callback->InvokeAsync("", FB::variant_list_of(retMap));
    status(hostname + " ok\n");
    return;
}



struct BufferStruct {
    char *memory;
    size_t size;
};

static size_t cb_memoryWrite(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct BufferStruct *mem = (struct BufferStruct *)userp;
    char *ret=NULL;
    
    ret = (char *)realloc(mem->memory, mem->size + realsize + 1);
    if (ret == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        free(mem->memory);
        return 0; // TODO: what should actually be done here?
    }
    mem->memory = ret;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

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

FB::variant MLabPluginAPI::status(const std::string& msg)
{
    fire_status(msg);
    // return "foobar";
    return msg;
}

FB::variant MLabPluginAPI::webtest(const std::string& val)
{
    //fire_echo("downloading a file");

    CURL *curl;
    CURLcode res_code;
    struct BufferStruct chunk;
    std::string res;
    
    curl = curl_easy_init();
    if(curl) {
        chunk.memory = (char *)malloc(1);  /* will be grown as needed by the realloc above */
        chunk.size = 0;    /* no data at this point */
        
        curl_easy_setopt(curl, CURLOPT_URL, val.c_str());
        
        /* send all data to this function  */
//      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb_memoryWrite);
        
        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, cb_memoryWrite);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&chunk);

        /* some servers don't like requests that are made without a user-agent
         field, so we provide one */
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        res_code = curl_easy_perform(curl);
        if ( res_code != CURLE_OK ) {
            res = "error";
        } else {
            res = std::string(chunk.memory, chunk.size);
        }
        free(chunk.memory);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return res;
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

long MLabPluginAPI::add( long a, long b, long c)
{
    return a+b+c;
}

FB::variant MLabPluginAPI::get_hostname() 
{
    std::string paramVal;
    boost::optional<std::string> myParam = getPlugin()->getParam("hostname");
    
    if (myParam) {
        return *myParam;
    } else {
        return "no hostname, sorry";
    }
}
