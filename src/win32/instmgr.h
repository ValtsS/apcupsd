/*
 * Copyright (C) 2009 Adam Kropelin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General
 * Public License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "astring.h"
#include "alist.h"
#include <windows.h>

#ifndef __INSTMGR_H
#define __INSTMGR_H

#include "balloonmgr.h"

class upsMenu;

struct InstanceConfig
{
   InstanceConfig() : menu(NULL), order(0) {}
   ~InstanceConfig() {}

   astring id;
   astring host;
   unsigned int port;
   unsigned int refresh;
   unsigned int order;
   upsMenu *menu;
};

class InstanceManager
{
public:
   InstanceManager(HINSTANCE appinst);
   ~InstanceManager();

   const alist<InstanceConfig> &Instances() { return _instances; }

   void CreateMonitors();
   int RemoveInstance(const char *id);
   void AddInstance();
   void UpdateInstance( const char *id, const char *host, int port, int refresh);
   void RemoveAll();
   void ResetInstances();

private:

   void Write();
   InstanceConfig ReadConfig(HKEY key, const char *id);
   alist<InstanceConfig>::iterator FindInstance(const char *id);
   astring CreateId();

   DWORD RegQueryDWORD(HKEY key, const char *name);
   astring RegQueryString(HKEY key, const char *name);
   void RegSetDWORD(HKEY key, const char *name, DWORD value);
   void RegSetString(HKEY key, const char *name, const char *value);

   static const char *INSTANCES_KEY;
   static const char *DEFAULT_HOST;
   static const unsigned int DEFAULT_PORT;
   static const unsigned int DEFAULT_REFRESH;

   alist<InstanceConfig> _instances;
   HINSTANCE _appinst;
   BalloonMgr _balmgr;
};

#endif