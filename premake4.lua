solution "SlackDescBuilder"

Win32Libs={
	"kernel32","user32","gdi32","comdlg32","winspool","winmm",
	"shell32","comctl32","ole32","oleaut32","uuid","rpcrt4",
	"advapi32","wsock32","odbc32","oleacc","wldap32"
	}	
wxWidgetReleaseLibs={
	"wxmsw28u","wxtiff","wxjpeg","wxpng","wxzlib","wxexpat","wxregexu"
	}
WXWIN="D:/MinGW/wxWidgets-2.8.12"	
	
configurations { "release","debug" }
configuration {"debug"}
	defines {"__WXDEBUG__","wxUSE_UNICODE"}
	defines {"DEBUG","_DEBUG"}
	flags { "Symbols","ExtraWarnings" }

configuration {"release"}
	defines {"wxUSE_UNICODE"}
	defines {"NDEBUG"}
	flags { "Optimize","ExtraWarnings" }

project "SlackDescBuilder"
	kind "WindowedApp"
	language "C++"
	files { "*.h", "*.cpp"}
	configuration "windows" 
		defines {"__WXMSW__"}
		includedirs  (WXWIN.."/include")
		includedirs  (WXWIN.."/lib/gcc_lib/mswu")
		libdirs (WXWIN.."/lib/gcc_lib")
		links {wxWidgetReleaseLibs}
		links {Win32Libs}
	configuration {"linux"}
		buildoptions { "`wx-config --cxxflags`","`pkg-config --cflags gtk+-2.0`" }
		linkoptions { "`wx-config --libs`","`pkg-config --libs gtk+-2.0`" }

