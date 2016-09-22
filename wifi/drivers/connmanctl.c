/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2015 - Michael Lelli
 * 
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../wifi_driver.h"
#include <file/file_path.h>

static void *connmanctl_init(const char *device, uint64_t caps,
      unsigned width, unsigned height)
{
   (void)device;
   return (void*)-1;
}

static void connmanctl_free(void *data)
{
   (void)data;
}

static bool connmanctl_start(void *data)
{
   (void)data;
   return true;
}

static void connmanctl_stop(void *data)
{
   (void)data;
}

static void connmanctl_scan(struct string_list *list)
{
   union string_list_elem_attr attr;
   attr.i = RARCH_FILETYPE_UNSET;
   char ssid[512];

   FILE* file = popen("connmanctl services", "r");
   while (fgets (ssid, 512, file) != NULL)
      string_list_append(list, ssid, attr);

   pclose(file);
}

wifi_driver_t wifi_connmanctl = {
   connmanctl_init,
   connmanctl_free,
   connmanctl_start,
   connmanctl_stop,
   connmanctl_scan,
   "connmanctl",
};