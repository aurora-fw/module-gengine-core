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

#include <AuroraFW/GEngine/Application.h>
#include <AuroraFW/GEngine/OpenGL.h>
#include <AuroraFW/GEngine/Input.h>

#include <AuroraFW/GEngine/_GLEW.h>
#include <AuroraFW/GEngine/_OpenGL.h>
#include <AuroraFW/GEngine/_Vulkan.h>
#include <AuroraFW/GEngine/_GLFW.h>

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
		struct AFW_EXPORT WindowProperties {
			/**
			 * Constructs a WindowProperties object with the given info.
			 * @param width The width of the window.
			 * @param height The height of the window.
			 * @param fullscreen If the window shall be in fullscreen or not.
			 * @param vsync If V-sync should be enabled.
			 * @since snapshot20170930
			 */
			WindowProperties(const uint& , const uint& , const bool& = false, const bool& = false);

			/**
			 * The width specified for the window.
			 * @see height
			 * @since snapshot20170930
			 */
			uint width;

			/**
			 * The height specified for the window.
			 * @see width
			 * @since snapshot20170930
			 */
			uint height;

			/**
			 * Tells if the window should be fullscreen or not.
			 * @see vsync
			 * @since snapshot20170930
			 */
			bool fullscreen;

			/**
			 * Tells if v-sync should be enabled.
			 * @see fullscreen
			 * @since snapshot20170930
			 */
			bool vsync;
		};

		class InputManager;

		class AFW_EXPORT Window {
			friend InputManager;
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
			Window(const GEngine::Application& , const char* , const WindowProperties& );

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
			 * Updates/renders the window.
			 * @see clear()
			 * @since snapshot20170930
			 */
			void update();

			/**
			 * Clears the window.
			 * @see update()
			 * @since snapshot20170930
			 */
			void clear() const;

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
			inline uint getWidth() const { return _width; }

			/**
			 * Returns the height of the window.
			 * @return Height of the window.
			 * @see getWidth()
			 * @since snapshot20170930
			 */
			inline uint getHeight() const { return _height; }

		protected:
			/**
			 * The <a href="http://www.glfw.org/docs/latest/group__window.html" target="_blank">GLFWwindow</a> used to render.
			 * @since snapshot20170930
			 */
			GLFWwindow *window;

		private:
			//void Init();
			const GLFWmonitor *_monitor;
			const char *_name;
			uint _width, _height;
			const bool _fullscreen, _vsync;
		};
	}
}

#endif // AURORAFW_GENGINE_WINDOW_H
