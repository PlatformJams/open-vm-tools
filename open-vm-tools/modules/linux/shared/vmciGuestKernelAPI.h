/*********************************************************
 * Copyright (C) 2007 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 *********************************************************/

/*
 * vmciGuestKernelAPI.h --
 *
 *    Kernel API exported from the VMCI guest driver.
 */

#ifndef __VMCI_GUESTKERNELAPI_H__
#define __VMCI_GUESTKERNELAPI_H__

/* Macros to operate on the driver version number. */
#define VMCI_MAJOR_VERSION(v)       (((v) >> 16) & 0xffff)
#define VMCI_MINOR_VERSION(v)       ((v) & 0xffff)

#define INCLUDE_ALLOW_MODULE
#include "includeCheck.h"

#include "vmci_defs.h"
#include "vmci_call_defs.h"

/*
 * Note: APIs marked as compat are provided for compatibility with the host
 *       only. These APIs don't really make sense in the context of the guest.
 */

/* PUBLIC: VMCI Device Usage API. */

Bool VMCI_DeviceGet(void);
void VMCI_DeviceRelease(void);

/* PUBLIC: VMCI Datagram API. */

int VMCIDatagram_CreateHnd(VMCIId resourceID, uint32 flags,
			   VMCIDatagramRecvCB recvCB, void *clientData,
			   VMCIHandle *outHandle);
int VMCIDatagram_CreateHndPriv(VMCIId resourceID, uint32 flags,
			       VMCIPrivilegeFlags privFlags,
			       VMCIDatagramRecvCB recvCB, void *clientData,
			       VMCIHandle *outHandle); /* Compat */
int VMCIDatagram_DestroyHnd(VMCIHandle handle);
int VMCIDatagram_Send(VMCIDatagram *msg);

/* VMCI Utility API. */

VMCIId VMCI_GetContextID(void);
uint32 VMCI_Version(void);
int VMCI_ContextID2HostVmID(VMCIId contextID, void *hostVmID,
                            size_t hostVmIDLen);

/* VMCI Event API. */

typedef void (*VMCI_EventCB)(VMCIId subID, VMCI_EventData *ed,
			     void *clientData);

int VMCIEvent_Subscribe(VMCI_Event event, uint32 flags, VMCI_EventCB callback,
                        void *callbackData, VMCIId *subID);
int VMCIEvent_Unsubscribe(VMCIId subID);

/* VMCI Context API */

VMCIPrivilegeFlags VMCIContext_GetPrivFlags(VMCIId contextID); /* Compat */

/* VMCI Discovery Service API. */

int VMCIDs_Lookup(const char *name, VMCIHandle *out);

/* VMCI Doorbell API. */

#define VMCI_FLAG_DELAYED_CB    0x01

typedef void (*VMCICallback)(void *clientData);

int VMCIDoorbell_Create(VMCIHandle *handle, uint32 flags,
                        VMCIPrivilegeFlags privFlags,
                        VMCICallback notifyCB, void *clientData);
int VMCIDoorbell_Destroy(VMCIHandle handle);
int VMCIDoorbell_Notify(VMCIHandle handle,
                        VMCIPrivilegeFlags privFlags);

#endif /* !__VMCI_GUESTKERNELAPI_H__ */

