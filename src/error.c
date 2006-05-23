/* Hey EMACS -*- linux-c -*- */
/* $Id$ */

/*  libCables - Ti Link Cable library, a part of the TiLP project
 *  Copyright (C) 1999-2005  Romain Lievin
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __WIN32__
#include <windows.h>
#endif
#include <glib.h>
#include <errno.h>

#include "gettext.h"
#include "export1.h"
#include "error.h"
#include "logging.h"

/**
 * ticables_error_get:
 * @number: error number (see error.h for list).
 * @message: a newly GLib allocated string which contains corresponding error *message.
 *
 * Attempt to match the message corresponding to the error number. The returned
 * string must be freed when no longer needed.
 * The error message has the following format:
 * - 1: the error message
 * - 2: the cause(s), explanations on how to fix it
 * - 3: the error returned by the system
 *
 * Return value: 0 if error has been caught, the error number otherwise (propagation).
 **/
TIEXPORT int TICALL ticables_error_get(CableError number, char **message)
{
	char *tmp;

	g_assert (message != NULL);

	switch(number)
	{
	case ERR_BUSY:
		*message = g_strconcat(
    		_("Msg: link cable is busy."),
    		"\n",
    		 _("Cause: a transfer is in progress."),
			 NULL);
    	break;

	case ERR_ROOT:
	    	*message = g_strconcat(
    		_("Msg: nable to use parallel/serial port: access refused."),
	    	"\n",
	    	_("Cause: you are not running program as root or setuid root."),
			NULL);
    	break;

	case ERR_TTDEV:
	    *message = g_strconcat(
                _("Msg: unable to use serial (/dev/ttySx) device."),
                "\n",
                _("Cause: the /dev/ttySx node doesn't exist or you don't have required permissions. See the log output for testing details."),
		NULL);

	case ERR_PPDEV:
            *message = g_strconcat(
                _("Msg: unable to use parport (/dev/parportX) device."),
                "\n",
                _("Cause: the /dev/parportX node doesn't exist or you don't have required permissions. See the log output for testing details."),
                NULL);

	case ERR_USBFS:
	    *message = g_strconcat(
                _("Msg: unable to use USB pseudo file system."),
                "\n",
                _("Cause: the USB fs is not mounted or you don't have permissions to use it. See the log oupput for testing details."),
                NULL);

	case ERR_ILLEGAL_ARG:
		*message = g_strconcat(
    		_("Msg: illegal operation or argument."),
			"\n",
			_("Cause: the program which uses this library is buggy. Fire-up the developer!"),
			NULL);
    break;

	case ERR_PORTTALK_NOT_FOUND:
		*message = g_strconcat(
    		_("Msg: PortTalk driver and/or library not found."),
			"\n",
			_("Cause: the driver may have been not started yet; it maye have been uninstalled; the library has been installed without NT administrator privileges."),
			NULL);
    break;

	case ERR_WRITE_ERROR:
    	*message = g_strconcat(
    		_("Msg: error occured while writing to the device."),
			NULL);
    	break;

  	case ERR_WRITE_TIMEOUT:
    	*message = g_strconcat(
    		_("Msg: timeout occured while writing to the device."),
    		"\n",
    		_("Cause: check that your link cable is plugged and/or the calculator is ready."),
			NULL);
    	break;

  	case ERR_READ_ERROR:
    	*message = g_strconcat(
    		_("Msg: error occured while reading to the device."),
			NULL);
    	break;

  	case ERR_READ_TIMEOUT:
    	*message = g_strconcat(
    		_("Msg: timeout occured while reading to the device."),
    		"\n",
    		_("Cause: check that your link cable is plugged and/or the calculator is ready."),
			NULL);
    	break;

	case ERR_PROBE_FAILED:
		*message = g_strconcat(
    		_("Msg: the probing od device failed."),
    		"\n",
    		_("Cause: internal error. If you get it, this is a bug!"),
			NULL);
    	break;

	case ERR_GRY_CREATEFILE:
	case ERR_GRY_SETUPCOMM:
	case ERR_GRY_GETCOMMSTATE:
	case ERR_GRY_SETCOMMSTATE:
	case ERR_GRY_GETCOMMTIMEOUT:
	case ERR_GRY_SETCOMMTIMEOUT:
	case ERR_GRY_PURGECOMM:
	case ERR_GRY_SETCOMMMASK:
		*message = g_strconcat(
    		_("Msg: unable to open COM port."),
    		"\n",
    		_("Cause: check your device is not used/locked by another application."),
			NULL);
		break;

	case ERR_SLV_LOADLIBRARY:
		*message = g_strconcat(
    		_("Msg: unable to load TiglUsb library."),
    		"\n",
    		_("Cause: is the LPG's SilverLink/DirectLink driver installed ?"),
			NULL);
		break;

	case ERR_SLV_FREELIBRARY:
		*message = g_strconcat(
    		_("Msg: unable to release TiglUsb library."),
    		"\n",
    		_("Cause: internal error"),
			NULL);
		break;

	case ERR_SLV_VERSION:
		*message = g_strconcat(
    		_("Msg: TiglUsb library version is wrong."),
    		"\n",
    		_("Cause: the library may require an earlier version. Update your driver!"),
			NULL);
		break;

	case ERR_SLV_OPEN:
		*message = g_strconcat(
    		_("Msg: failed to open SilverLink/DirectLink access."),
    		"\n",
    		_("Cause: check your USB cable is plugged and/or the calculator is ON!"),
			NULL);
		break;

	case ERR_SLV_RESET:
		*message = g_strconcat(
    		_("Msg: failed to reset SilverLink/DirectLink cable."),
    		"\n",
    		_("Cause: check your USB cable is well plugged ! It may be stalled, too: unplug/replug it."),
			NULL);
		break;

	case ERR_VTI_FINDWINDOW:
	case ERR_VTI_OPENFILEMAPPING:
	case ERR_VTI_MAPVIEWOFFILE:
		*message = g_strconcat(
    		_("Msg: failed to get VTI handle."),
    		"\n",
    		_("Cause: VTi may not be running. VTi must be launched before."),
			NULL);

	case ERR_VTI_IPCKEY:
	case ERR_VTI_SHMGET:
	case ERR_VTI_SHMAT:
	case ERR_VTI_SHMDT:
	case ERR_VTI_SHMCTL:
		*message = g_strconcat(
			_("Msg: unable to get a unique IPC (Inter Process Communication) key."),
			"\n",
			_("Cause: check that you have enough resources for allocating a shared memory segment."),
			NULL);
    break;

	case ERR_TIE_OPEN:
	case ERR_TIE_CLOSE:
    	*message = g_strconcat(
    		_("Msg: unable to open/close pipes for virtual linking."),
    		"\n",
    		_("Cause: check that you have permissions to create a pipe in the /tmp directory."),
			NULL);
    	break;

	case ERR_TTY_OPEN:
	case ERR_GRY_OPEN:
		*message = g_strconcat(
			_("Msg: unable to open serial device."),
			"\n",
			_("Cause: check that you permissions on /dev/ttySx device. Check your device is not locked."),
			NULL);
		break;

	case ERR_TTY_IOCTL:
	case ERR_GRY_IOCTL:
		*message = g_strconcat(
			_("Msg: unable to issue a specific command on serial device."),
			"\n",
			_("Cause: check that you permissions on /dev/ttySx device. Check your device is not locked."),
			NULL);
		break;

	case ERR_PPT_OPEN:
	    *message = g_strconcat(
		_("Msg: unable to open parallel device."),
		"\n",
		_("Cause: check that you permissions on /dev/parportX device. Check your device is not locked."),
		NULL);
	    break;

	case ERR_PPT_IOCTL:
	    *message = g_strconcat(
		_("Msg: unable to issue a specific command on parallel device."),
		"\n",
		_("Cause: check that you permissions on /dev/parportX device. Check your device is not locked."),
		NULL);
	    break;

	case ERR_LIBUSB_OPEN:
	case ERR_LIBUSB_CLAIM:
	case ERR_LIBUSB_CONFIG:
		*message = g_strconcat(
			_("Msg: unable to open USB device."),
			"\n",
			_("Cause: Check that your cable is connected or not stalled. Check your libusb and usbfs, too."),
			NULL);
		break;

	case ERR_LIBUSB_RESET:
		*message = g_strconcat(
			_("Msg: unable to reset USB device."),
			"\n",
			_("Cause: Check that your cable is connected or not stalled. Try to unplug/plug it."),
			NULL);
		break;	
	case ERR_NOT_OPEN:
		*message = g_strconcat(
			_("Msg: attempting to use a cable which has not been open before."),
			"\n",
			_("Cause: Internal error."),
			NULL);
		break;

  	default:
	    // propagate error code
	    return number;
    break;
  	}

#ifndef __WIN32__
  	if (errno != 0) 
	{
		gchar *str;
		tmp = *message;
		
		str = g_strdup_printf(" (errno = %i)", errno);
		*message = g_strconcat(tmp, "\n", "System: ", strerror(errno), str, "\n", NULL);
		g_free(tmp);
		g_free(str);
  	}
#else
  	if (GetLastError()) 
	{
		LPVOID lpMsgBuf;
		gchar *str;
		tmp = *message;

    	FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, 
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 
			0, 
			NULL);

		str = g_strdup_printf("(%li) %s", (long)GetLastError, (char *)lpMsgBuf);
		*message = g_strconcat(tmp, "\n", "System: ", str, NULL);
		g_free(tmp);
		g_free(str);
  	}
#endif

	return 0;
}
