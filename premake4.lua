solution "SlackDescBuilder"
	location ("build/" .. _ACTION )	
	dofile "../premake4/common.lua"
	dofile "../premake4/wxWidget.lua"
	
project "SlackDescBuilder"
	kind "WindowedApp"
	language "C++"
	files { "*.h", "*.cpp"}
	targetdir "bin"
	configuration "windows" 
		files{"*.rc"}
		links {wxWidgetLibs}

