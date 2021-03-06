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

#include <AuroraFW/GEngine/Input.h>
#include <AuroraFW/CoreLib/Callback.h>
#include <algorithm>
#include <assert.h>

namespace AuroraFW {
	namespace GEngine {
		InputManager::InputManager(const Window *parent)
			: _parent(parent)
		{
			for(int i = 0; i < AFW_GENGINE_INPUT_MAX_KEYS; i++)
			{
				_keys[i] = false;
			}

			for(int i = 0; i < AFW_GENGINE_INPUT_MAX_MOUSE_BUTTONS; i++)
			{
				_mouseButtons[i] = false;
			}

			glfwSetWindowUserPointer(_parent->window, this);
			glfwSetKeyCallback(_parent->window, _keyCallback);
			glfwSetMouseButtonCallback(_parent->window, _mouseButtonCallback);
			glfwSetCursorPosCallback(_parent->window, _cursorPosCallback);
			glfwSetScrollCallback(_parent->window, _scrollCallback);
			glfwSetCharCallback(_parent->window, _charCallback);
		}

		InputManager::~InputManager()
		{}

		bool InputManager::isKeyPressed(const InputKey& key) const
		{
			if(static_cast<int>(key) >= (AFW_GENGINE_INPUT_MAX_KEYS + AFW_GENGINE_INPUT_KEY_OFFSET))
				return false;
			return _keys[static_cast<int>(key)];
		}

		bool InputManager::isMouseButtonPressed(const InputButton& btn) const
		{
			if(static_cast<int>(btn) >= (AFW_GENGINE_INPUT_MAX_MOUSE_BUTTONS + AFW_GENGINE_INPUT_MOUSE_BUTTONS_OFFSET))
				return false;
			return _mouseButtons[static_cast<int>(btn)];
		}

		void InputManager::getMousePosition(double& x, double& y) const
		{
			x = _mx;
			y = _my;
		}

		void InputManager::_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			InputManager *in = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
			in->_keys[key] = action != GLFW_RELEASE;

			std::for_each(in->_keyCallbacks.begin(), in->_keyCallbacks.end(), [key, scancode, action, mods](std::function<void(InputKey, int, InputAction, InputMod)> func) {
				func(static_cast<InputKey>(key), scancode, static_cast<InputAction>(action), static_cast<InputMod>(mods));
			});
		}

		void InputManager::_mouseButtonCallback(GLFWwindow *window, int btn, int action, int mods)
		{
			InputManager *in = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
			in->_mouseButtons[btn] = action != GLFW_RELEASE;

			std::for_each(in->_mouseButtonCallbacks.begin(), in->_mouseButtonCallbacks.end(), [btn, action, mods](std::function<void(InputButton, InputAction, InputMod)> func) {
				func(static_cast<InputButton>(btn), static_cast<InputAction>(action), static_cast<InputMod>(mods));
			});
		}

		void InputManager::_cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
		{
			InputManager *in = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
			in->_mx = xpos;
			in->_my = ypos;

			std::for_each(in->_cursorPosCallbacks.begin(), in->_cursorPosCallbacks.end(), [xpos, ypos](std::function<void(double, double)> func) {
				func(xpos, ypos);
			});
		}

		void InputManager::_scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
		{
			InputManager *in = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
			in->_sx += xoffset;
			in->_sy += yoffset;

			std::for_each(in->_scrollCallbacks.begin(), in->_scrollCallbacks.end(), [xoffset, yoffset](std::function<void( double, double)> func) {
				func(xoffset, yoffset);
			});
		}

		void InputManager::_charCallback(GLFWwindow *window, uint codepoint)
		{
			InputManager *in = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

			std::for_each(in->_charCallbacks.begin(), in->_charCallbacks.end(), [codepoint](std::function<void(uint)> func) {
				func(codepoint);
			});
		}

		void InputManager::addKeyCallback(std::function<void(InputKey, int, InputAction, InputMod)> func)
		{
			_keyCallbacks.push_back(func);
		}

		void InputManager::removeKeyCallback(std::function<void(InputKey, int, InputAction, InputMod)> func)
		{
			_keyCallbacks.erase(std::find_if(_keyCallbacks.begin(),_keyCallbacks.end(),
				[func](std::function<void(InputKey, int, InputAction, InputMod)> _f){
					return getCallbackPtr(_f) == getCallbackPtr(func);
				}));
		}

		void InputManager::addMouseButtonCallback(std::function<void(InputButton, InputAction, InputMod)> func)
		{
			_mouseButtonCallbacks.push_back(func);
		}

		void InputManager::removeMouseButtonCallback(std::function<void(InputButton, InputAction, InputMod)> func)
		{
			_mouseButtonCallbacks.erase(std::find_if(_mouseButtonCallbacks.begin(),_mouseButtonCallbacks.end(),
				[func](std::function<void(InputButton, InputAction, InputMod)> _f){
					return getCallbackPtr(_f) == getCallbackPtr(func);
				}));
		}

		void InputManager::addCursorPosCallback(std::function<void(double,double)> func)
		{
			_cursorPosCallbacks.push_back(func);
		}

		void InputManager::removeCursorPosCallback(std::function<void(double,double)> func)
		{
			_cursorPosCallbacks.erase(std::find_if(_cursorPosCallbacks.begin(),_cursorPosCallbacks.end(),
				[func](std::function<void(double,double)> _f){
					return getCallbackPtr(_f) == getCallbackPtr(func);
				}));
		}

		void InputManager::addScrollCallback(std::function<void(double,double)> func)
		{
			_scrollCallbacks.push_back(func);
		}

		void InputManager::removeScrollCallback(std::function<void(double,double)> func)
		{
			_scrollCallbacks.erase(std::find_if(_scrollCallbacks.begin(),_scrollCallbacks.end(),
				[func](std::function<void(double,double)> _f){
					return getCallbackPtr(_f) == getCallbackPtr(func);
				}));
		}

		void InputManager::addCharCallback(std::function<void(uint)> func)
		{
			_charCallbacks.push_back(func);
		}

		void InputManager::removeCharCallback(std::function<void(uint)> func)
		{
			_charCallbacks.erase(std::find_if(_charCallbacks.begin(),_charCallbacks.end(),
				[func](std::function<void(uint)> _f){
					return getCallbackPtr(_f) == getCallbackPtr(func);
				}));
		}
	}
}
