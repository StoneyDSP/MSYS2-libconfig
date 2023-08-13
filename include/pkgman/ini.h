/**
 * @file ini.h
 *
 * @version @LibCommon_VERSION@
 *
 * @authors Pacman Development Team <pacman-dev@archlinux.org>
 *
 * @copyright Copyright (c) 2006-2021 Pacman Development Team <pacman-dev@archlinux.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 *
*/

#ifndef PKGMAN_INI_H_INCLUDED
#define PKGMAN_INI_H_INCLUDED

#include "pkgman/pkgman_config.h"

#ifdef PKGMAN_CPLUSPLUS
extern "C" {
#endif

typedef int (ini_parser_fn)(const char *file, int line, const char *section, char *key, char *value, void *data);

int parse_ini(const char *file, ini_parser_fn cb, void *data);

#ifdef PKGMAN_CPLUSPLUS
}
#endif

#endif /** PKGMAN_INI_H */
