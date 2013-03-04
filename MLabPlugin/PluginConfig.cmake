#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for MLab Plugin
#
#\**********************************************************/

set(PLUGIN_NAME "MLabPlugin")
set(PLUGIN_PREFIX "MLP")
set(COMPANY_NAME "MeasurementLab")

# ActiveX constants:
set(FBTYPELIB_NAME MLabPluginLib)
set(FBTYPELIB_DESC "MLabPlugin 1.0 Type Library")
set(IFBControl_DESC "MLabPlugin Control Interface")
set(FBControl_DESC "MLabPlugin Control Class")
set(IFBComJavascriptObject_DESC "MLabPlugin IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "MLabPlugin ComJavascriptObject Class")
set(IFBComEventSource_DESC "MLabPlugin IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 4d80018f-0c91-5ac4-bd39-b58c106b1db4)
set(IFBControl_GUID b6c42510-9650-52e0-98d1-36c9453f0c3c)
set(FBControl_GUID 7339b939-cef6-50db-a7a6-dd6ce228d819)
set(IFBComJavascriptObject_GUID 6637a49a-f081-5d48-be3a-06cfdd777a51)
set(FBComJavascriptObject_GUID 7f89f6de-b93d-5f71-af55-7cec81e77316)
set(IFBComEventSource_GUID 791df30e-5e08-5a50-88ff-92397ac53424)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID ddaa5e07-eac7-565f-8381-0b3ebbde885c)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 0121ef9e-5e57-5340-9dc9-b0fc3ecbb62c)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "MeasurementLab.MLabPlugin")
set(MOZILLA_PLUGINID "measurementlab.net/MLabPlugin")

# strings
set(FBSTRING_CompanyName "Measurement Lab")
set(FBSTRING_PluginDescription "Plugin for M-Lab client-side tests")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Measurement Lab")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "MLab Plugin")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "MLab Plugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "MLab Plugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-mlabplugin")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
