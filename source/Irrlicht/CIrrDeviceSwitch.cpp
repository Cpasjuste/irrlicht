// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_SWITCH_DEVICE_

#include <stdio.h>
#include <stdlib.h>

#include "CIrrDeviceSwitch.h"
#include "IEventReceiver.h"
#include "irrList.h"
#include "os.h"
#include "CTimer.h"
#include "irrString.h"
#include "Keycodes.h"
#include "COSOperator.h"
#include "SIrrCreationParameters.h"


namespace irr
{
	namespace video
	{
		#ifdef _IRR_COMPILE_WITH_OPENGL_
		IVideoDriver* createOpenGLDriver(const SIrrlichtCreationParameters& params,
				io::IFileSystem* io, CIrrDeviceSwitch* device);
		#endif
	} // end namespace video

} // end namespace irr


namespace irr
{

//! constructor
CIrrDeviceSwitch::CIrrDeviceSwitch(const SIrrlichtCreationParameters& param)
	: CIrrDeviceStub(param), /*Screen((SDL_Surface*)param.WindowId),*/ SDL_Flags(0),
	MouseX(0), MouseY(0), MouseButtonStates(0),
	Width(param.WindowSize.Width), Height(param.WindowSize.Height),
	Resizable(false), WindowHasFocus(false), WindowMinimized(false)
{

}


//! destructor
CIrrDeviceSwitch::~CIrrDeviceSwitch()
{

}


bool CIrrDeviceSwitch::createWindow()
{
	return true;
}


//! create the driver
void CIrrDeviceSwitch::createDriver()
{
	switch(CreationParams.DriverType)
	{
	case video::DEPRECATED_EDT_DIRECT3D8_NO_LONGER_EXISTS:
		os::Printer::log("DIRECT3D8 Driver is no longer supported in Irrlicht. Try another one.", ELL_ERROR);
		break;

	case video::EDT_DIRECT3D9:
		#ifdef _IRR_COMPILE_WITH_DIRECT3D_9_

		VideoDriver = video::createDirectX9Driver(CreationParams, FileSystem, HWnd);
		if (!VideoDriver)
		{
			os::Printer::log("Could not create DIRECT3D9 Driver.", ELL_ERROR);
		}
		#else
		os::Printer::log("DIRECT3D9 Driver was not compiled into this dll. Try another one.", ELL_ERROR);
		#endif // _IRR_COMPILE_WITH_DIRECT3D_9_

		break;

	case video::EDT_SOFTWARE:
		#ifdef _IRR_COMPILE_WITH_SOFTWARE_
		VideoDriver = video::createSoftwareDriver(CreationParams.WindowSize, CreationParams.Fullscreen, FileSystem, this);
		#else
		os::Printer::log("No Software driver support compiled in.", ELL_ERROR);
		#endif
		break;

	case video::EDT_BURNINGSVIDEO:
		#ifdef _IRR_COMPILE_WITH_BURNINGSVIDEO_
		VideoDriver = video::createBurningVideoDriver(CreationParams, FileSystem, this);
		#else
		os::Printer::log("Burning's video driver was not compiled in.", ELL_ERROR);
		#endif
		break;

	case video::EDT_OPENGL:
		#ifdef _IRR_COMPILE_WITH_OPENGL_
		VideoDriver = video::createOpenGLDriver(CreationParams, FileSystem, this);
		#else
		os::Printer::log("No OpenGL support compiled in.", ELL_ERROR);
		#endif
		break;

	case video::EDT_NULL:
		VideoDriver = video::createNullDriver(FileSystem, CreationParams.WindowSize);
		break;

	default:
		os::Printer::log("Unable to create video driver of unknown type.", ELL_ERROR);
		break;
	}
}


//! runs the device. Returns false if device wants to be deleted
bool CIrrDeviceSwitch::run()
{
	return !Close;
}

//! Activate any joysticks, and generate events for them.
bool CIrrDeviceSwitch::activateJoysticks(core::array<SJoystickInfo> & joystickInfo)
{
	return false;
}



//! pause execution temporarily
void CIrrDeviceSwitch::yield()
{
	//SDL_Delay(0);
}


//! pause execution for a specified time
void CIrrDeviceSwitch::sleep(u32 timeMs, bool pauseTimer)
{
	const bool wasStopped = Timer ? Timer->isStopped() : true;
	if (pauseTimer && !wasStopped)
		Timer->stop();

	//SDL_Delay(timeMs);

	if (pauseTimer && !wasStopped)
		Timer->start();
}


//! sets the caption of the window
void CIrrDeviceSwitch::setWindowCaption(const wchar_t* text)
{
	core::stringc textc = text;
	//SDL_WM_SetCaption( textc.c_str( ), textc.c_str( ) );
}


//! presents a surface in the client area
bool CIrrDeviceSwitch::present(video::IImage* surface, void* windowId, core::rect<s32>* srcClip)
{
	return false;
}


//! notifies the device that it should close itself
void CIrrDeviceSwitch::closeDevice()
{
	Close = true;
}


//! \return Pointer to a list with all video modes supported
video::IVideoModeList* CIrrDeviceSwitch::getVideoModeList()
{
	return VideoModeList;
}


//! Sets if the window should be resizable in windowed mode.
void CIrrDeviceSwitch::setResizable(bool resize)
{

}


//! Minimizes window if possible
void CIrrDeviceSwitch::minimizeWindow()
{

}


//! Maximize window
void CIrrDeviceSwitch::maximizeWindow()
{
	// do nothing
}

//! Get the position of this window on screen
core::position2di CIrrDeviceSwitch::getWindowPosition()
{
    return core::position2di(-1, -1);
}


//! Restore original window size
void CIrrDeviceSwitch::restoreWindow()
{
	// do nothing
}


//! returns if window is active. if not, nothing need to be drawn
bool CIrrDeviceSwitch::isWindowActive() const
{
	return (WindowHasFocus && !WindowMinimized);
}


//! returns if window has focus.
bool CIrrDeviceSwitch::isWindowFocused() const
{
	return WindowHasFocus;
}


//! returns if window is minimized.
bool CIrrDeviceSwitch::isWindowMinimized() const
{
	return WindowMinimized;
}


//! Set the current Gamma Value for the Display
bool CIrrDeviceSwitch::setGammaRamp( f32 red, f32 green, f32 blue, f32 brightness, f32 contrast )
{
	/*
	// todo: Gamma in SDL takes ints, what does Irrlicht use?
	return (SDL_SetGamma(red, green, blue) != -1);
	*/
	return false;
}

//! Get the current Gamma Value for the Display
bool CIrrDeviceSwitch::getGammaRamp( f32 &red, f32 &green, f32 &blue, f32 &brightness, f32 &contrast )
{
/*	brightness = 0.f;
	contrast = 0.f;
	return (SDL_GetGamma(&red, &green, &blue) != -1);*/
	return false;
}

//! returns color format of the window.
video::ECOLOR_FORMAT CIrrDeviceSwitch::getColorFormat() const
{
		return CIrrDeviceStub::getColorFormat();
}


void CIrrDeviceSwitch::createKeyMap()
{

}

} // end namespace irr

#endif // _IRR_COMPILE_WITH_SWITCH_DEVICE_
