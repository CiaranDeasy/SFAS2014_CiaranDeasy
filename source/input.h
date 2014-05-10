/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 *
 * Edited for the Search for a Star Competition 2014
 *
 */

#if !defined(_INPUT_H)
#define _INPUT_H

#include "s3ePointer.h"


#define MAX_TOUCHES     10

/**
 * @class Input
 *
 * @brief Input - The Input class is responsible for handling all pointer input.
 *
 * Example usage:
 * @code
 *    // Set up input systems
 *    g_pInput = new Input();
 *
 *    // Update
 *    while (!s3eDeviceCheckQuitRequest())
 *    {
 *        // Update input system
 *        g_pInput->Update();
 *    }
 *
 *    // Cleanup
 *    delete g_pInput;
 * @endcode
 *
 */
class Input
{
public:
    int             m_X, m_Y;           // Touched position
    bool            m_Touched;          // Snapshot of touch state taken on input update
    bool            m_Pressed;          // Indicates that the touch was pressed this frame
    bool            m_Released;         // Indicates that the touch was released this frame

public:
    Input();

    /**
     * @fn    void Input::Update()
     *
     * @brief Updates the input system, called every frame.
     */
    void            Update();

    /**
     * @fn    void Input::Reset()
     *
     * @brief Clears all current touch state.
     */
    void            Reset();
    
private:
    // Callbacks
    static void     TouchButtonCB(s3ePointerEvent* event);
    static void     TouchMotionCB(s3ePointerMotionEvent* event);
    static void     MultiTouchButtonCB(s3ePointerTouchEvent* event);
    static void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);

    bool            m_LiveTouched;      // Updated by touch events
    int             m_Transitions;      // No of pressed/released events since last update
};

extern Input* g_pInput;


#endif  // _INPUT_H
