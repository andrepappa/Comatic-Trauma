#pragma once

#include <Windows.h>
#include <stdarg.h>
#include <string>
#include <iostream>

enum CON_COLOR
{
	BLACK		= 0x00,
	BLUE		= 0x01,
	GREEN		= 0x02,
	AQUA		= 0x03,
	RED			= 0x04,
	PURPLE		= 0x05,
	YELLOW		= 0x06,
	WHITE		= 0x07,
	GRAY		= 0x08,
	LIGHTBLUE	= 0x09,
	LIGHTGREEN	= 0x0A,
	LIGHTAQUA	= 0x0B,
	LIGHTRED	= 0x0C,
	LIGHTPURPLE	= 0x0D,
	LIGHTYELLOW	= 0x0E,
	BRIGHTWHITE	= 0x0F
};

namespace Util
{
	inline void PrintColor(std::string print, CON_COLOR color, std::ostream* out = &std::cout)
	{
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO defaultInfo;
		GetConsoleScreenBufferInfo(hstdout, &defaultInfo);

		SetConsoleTextAttribute(hstdout, color);
		(*out) << print;
		SetConsoleTextAttribute(hstdout, defaultInfo.wAttributes);
	}

	inline std::string BuildString(const char* Format, ...)
	{
		va_list Variables;
		int Len;
		char* Text;
		std::string Out;

		va_start(Variables, Format);
		Len = _vscprintf(Format, Variables) + 1;
		Text = (char *)malloc(Len * sizeof(char));
		vsprintf_s(Text, Len, Format, Variables);
		va_end(Variables);
		Out = std::string(Text);
		free(Text);

		return Out;
	}

	inline void msgStd(std::string Text)
	{
		Util::PrintColor(Util::BuildString("%s\n", Text.c_str()), WHITE);
	}
	inline void msgNote(std::string Text)
	{
		Util::PrintColor(Util::BuildString("[NOTE:] %s\n", Text.c_str()), GREEN);
	}
	inline void msgWarn(std::string Text)
	{
		Util::PrintColor(Util::BuildString("[WARN:] %s\n", Text.c_str()), YELLOW);
	}
	inline void msgErr(std::string Text)
	{
		Util::PrintColor(Util::BuildString("[ ERR:] %s\n", Text.c_str()), RED);
	}

}