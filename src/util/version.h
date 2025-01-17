/*****************************************************************************
* Copyright 2015-2020 Alexander Barthel alex@littlenavmap.org
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

#ifndef ATOOLS_UTIL_VERSION_H
#define ATOOLS_UTIL_VERSION_H

#include <QCoreApplication>

namespace atools {
namespace util {

/*
 * Parses version numbers like "0.9.5", "1.12.24-rc9" (major.minor.patchlevel[.name][namesubver]) into their parts.
 */
class Version
{
  Q_DECLARE_TR_FUNCTIONS(Version)

public:
  /* Initialize from given parameters */
  explicit Version(int verMajor, int verMinor, int verPatchlevel = -1, const QString& verName = QString(), int verNameSub = -1);
  explicit Version(const QString& str);

  /* Initialize from application version */
  Version();
  ~Version();

  /* 1 from "1.12.24-rc9" */
  int getMajor() const
  {
    return majorVersion;
  }

  /* 12 from "1.12.24-rc9" */
  int getMinor() const
  {
    return minorVersion;
  }

  /* 24 from "1.12.24-rc9" */
  int getPatchlevel() const
  {
    return patchlevelVersion;
  }

  /* rc from "1.12.24-rc9" */
  const QString& getName() const
  {
    return name;
  }

  /* 9 from "1.12.24-rc9" */
  int getNameSubVersion() const
  {
    return nameSubVersion;
  }

  /* All like "1.12.24-rc9" */
  const QString& getVersionString() const
  {
    return versionString;
  }

  bool isStable() const;
  bool isReleaseCandidate() const;
  bool isBeta() const;
  bool isDevelop() const;

  /* Compare major, minor and patchlevel */
  bool operator<(const Version& other) const;

  bool operator>(const Version& other) const
  {
    return other < *this;
  }

  bool operator<=(const Version& other) const
  {
    return !(*this > other);
  }

  bool operator>=(const Version& other) const
  {
    return !(*this < other);
  }

  bool operator==(const Version& other) const
  {
    return versionString == other.versionString;
  }

  bool operator!=(const Version& other) const
  {
    return !(*this == other);
  }

  bool isValid() const;

private:
  friend QDebug operator<<(QDebug out, const atools::util::Version& version);
  void initFromString(const QString& str);
  int namePriority() const;

  int majorVersion = -1, minorVersion = -1, patchlevelVersion = -1, nameSubVersion = -1;
  QString name, versionString;

};

} // namespace util
} // namespace atools

#endif // ATOOLS_UTIL_VERSION_H
