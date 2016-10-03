/*****************************************************************************
* Copyright 2015-2016 Alexander Barthel albar965@mailbox.org
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef ATOOLS_FS_NAVDATABASEERRORS_H
#define ATOOLS_FS_NAVDATABASEERRORS_H

#include "fs/scenery/sceneryarea.h"

#include <QList>

namespace atools {
namespace fs {

/*
 * This class collects exception messages for each BGL file and scenery database entry.
 */
class NavDatabaseErrors
{
public:
  NavDatabaseErrors();

  int getTotalErrors() const;

  struct BglFileError
  {
    QString bglFilepath, errorMessage;
  };

  struct SceneryErrors
  {
    atools::fs::scenery::SceneryArea scenery;
    QList<atools::fs::NavDatabaseErrors::BglFileError> bglFileErrors;
  };

  QList<atools::fs::NavDatabaseErrors::SceneryErrors> sceneryErrors;
};

} // namespace fs
} // namespace atools

#endif // ATOOLS_FS_NAVDATABASEERRORS_H