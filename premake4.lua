solution "SlackDescBuilder"
	
configurations { "release","debug" }
configuration { "release" }
	defines { "NDEBUG" }
	flags { "Optimize" }
configuration { "debug" }
	defines {"DEBUG","_DEBUG"}
	flags { "Symbols","ExtraWarnings"}	

project "SlackDescBuilder"
	kind "WindowedApp"
	language "C++"
	files { "*.h", "*.cpp"}
	configuration "windows" 
		files{"*.rc"}
		links {"wxmsw28u"}
	configuration {"linux"}
		buildoptions { "`wx-config --cxxflags`","`pkg-config --cflags gtk+-2.0`" }
		linkoptions { "`wx-config --libs`","`pkg-config --libs gtk+-2.0`" }

