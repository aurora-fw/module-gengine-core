/****************************************************************************
** ┌─┐┬ ┬┬─┐┌─┐┬─┐┌─┐  ┌─┐┬─┐┌─┐┌┬┐┌─┐┬ ┬┌─┐┬─┐┬┌─
** ├─┤│ │├┬┘│ │├┬┘├─┤  ├┤ ├┬┘├─┤│││├┤ ││││ │├┬┘├┴┐
** ┴ ┴└─┘┴└─└─┘┴└─┴ ┴  └  ┴└─┴ ┴┴ ┴└─┘└┴┘└─┘┴└─┴ ┴
** A Powerful General Purpose Framework
** More information in: https://aurora-fw.github.io/
**
** Copyright (C) 2017 Aurora Framework, All rights reserved.
**
** This file is part of the Aurora Framework. This framework is free
** software; you can redistribute it and/or modify it under the terms of
** the GNU Lesser General Public License version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE included in
** the packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
****************************************************************************/

#ifndef AURORAFW_GENGINE_WINDOW_H
#define AURORAFW_GENGINE_WINDOW_H

#include <AuroraFW/Global.h>
#if(AFW_TARGET_PRAGMA_ONCE_SUPPORT)
	#pragma once
#endif

#include <AuroraFW/Internal/Config.h>

#include <AuroraFW/GEngine/_GLFW.h>

#include <AuroraFW/STDL/STL/String.h>

#include <stdexcept>

//typedef struct GLFWwindow GLFWwindow;
//typedef struct GLFWmonitor GLFWmonitor;

/** @file AuroraFW/GEngine/Window.h
 * Window header. This contains the struct WindowProperties, and
 * the class Window, used to display objects on the screen.
 * @since snapshot20170917
 */

namespace AuroraFW {
	namespace GEngine {
		/**
		 * A struct to define properties for the window.
		 * A struct used to declare specific definitions while creating a
		 * window, such as resolution.
		 * @since snapshot20170930
		 */
		class Window;
		class GLContext;

		struct AFW_API WindowProperties {
			/**
			 * The width specified for the window.
			 * @see height
			 * @since snapshot20170930
			 */
			uint width = 800;

			/**
			 * The height specified for the window.
			 * @see width
			 * @since snapshot20170930
			 */
			uint height = 600;

			/**
			 * Tells if the window should be fullscreen or not.
			 * @see vsync
			 * @since snapshot20170930
			 */
			bool fullscreen = false;

			/**
			 * Tells if v-sync should be enabled.
			 * @see fullscreen
			 * @since snapshot20170930
			 */
			bool vsync = true;

			bool resizable = false;
			bool visible = true;
			bool decorated = true;
			bool focused = true;
			bool autoIconify = true;
			bool floating = false;
			bool maximized = false;
			int refreshRate = -1;
			int auxBuffers = 0;
			int samples = 0;
			bool stereo = false;
			bool sRGB = false;
			bool doubleBuffer = true;
			//TODO: http://www.glfw.org/docs/latest/window_guide.html#window_hints

			bool swapBuffers = true;
			bool windowSettingsDialog = true;
		};

		class InputManager;
		class ImGuiLoader;

		class AFW_API Window {
			friend InputManager;
			friend ImGuiLoader;
		public:
			/**
			 * Constructs a Window.
			 * @param gapp The Application connected to this window.
			 * @param name The name of the window.
			 * @param wp The WindowProperties desired.
			 * @see WindowProperties
			 * @see ~Window()
			 * @since snapshot20170930
			 */
			Window(std::string , const WindowProperties = {});

			/**
			 * Destructs the Window object.
			 * @see Window()
			 * @since snapshot20170930
			 */
			~Window();

			/**
			 * The copy constructor was deleted, since Window is not suitable to be copied.
			 * @since snapshot20170930
			 */
			Window(const Window&) = delete;

			/**
			 * The copy assignment was deleted, since Window is not suitable to be copied.
			 * @since snapshot20170930
			 */
			Window& operator=(const Window&) = delete;

			/**
			 * Update the window events.
			 * @see clear()
			 * @since snapshot20170930
			 */
			void update();

			/**
			 * Swap buffers and present window stuff
			 * @see clear()
			 * @since snapshot20180303
			 */
			void present();

			/**
			 * Returs whether the window is closed or not.
			 * @return <code>true</code> if the window was closed. <code>false</code> otherwise.
			 * @since snapshot20170930
			 */
			bool isClosed() const;

			/**
			 * Returns the width of the window.
			 * @return Width of the window.
			 * @see getHeight()
			 * @since snapshot20170930
			 */
			AFW_FORCE_INLINE uint width() const { return wp.width; }

			/**
			 * Returns the height of the window.
			 * @return Height of the window.
			 * @see getWidth()
			 * @since snapshot20170930
			 */
			AFW_FORCE_INLINE uint height() const { return wp.height; }

			AFW_FORCE_INLINE WindowProperties properties() { return wp; }

			AFW_FORCE_INLINE bool getFloating() const { return wp.floating; }
			inline void setFloating(bool val) { _isCreated ? throw std::runtime_error("Can't change window properties after creation!") : wp.floating = val; }

			inline bool getResizable() const { return wp.resizable; }
			inline void setResizable(bool val) { _isCreated ? throw std::runtime_error("Can't change window properties after creation!") : wp.resizable = val; }

			inline bool getDoubleBuffer() const { return wp.doubleBuffer; }
			inline void setDoubleBuffer(bool val) { _isCreated ? throw std::runtime_error("Can't change window properties after creation!") : wp.doubleBuffer = val;}

			inline bool setSamples(int s) { _isCreated ? throw std::runtime_error("Can't change window properties after creation!") : wp.samples = s; }

		protected:
			/**
			 * The <a href="http://www.glfw.org/docs/latest/group__window.html" target="_blank">GLFWwindow</a> used to render.
			 * @since snapshot20170930
			 */
			GLFWwindow *window;
			WindowProperties wp;

		private:
		  void _openWindowSettingsDialog();
		  //void Init();
		  const GLFWmonitor *_monitor;
		  std::string _name;
		  bool _isCreated = false;
		};
	}
}

#endif // AURORAFW_GENGINE_WINDOW_H
