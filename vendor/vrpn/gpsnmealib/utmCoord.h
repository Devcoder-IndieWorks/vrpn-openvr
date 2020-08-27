// UtmCoord.h: Definition of the CUtmCoord class.
//
// This class represents a coordinate on the UTM grid.
//
// Like all other typed coordinate classes, this class contains an internal
// lat/lon coordinate.  This lat/lon coordinate is created by converting the
// lat/lon coordinate from a UTM coordinate.  Since either lat/lon or UTM can
// be set and read, a conversion may be necessary from one type to another.
// This conversion is quite slow on machines without FPUs, so these conver-
// sions are done internally only when the converted coordinates are required
// by code using a UTM object (this is known as 'lazy evaluation.')  In order
// to implement this lazy evaluation code, this class uses member functions
// to access the coordinates (since those member functions modify the lazy
// evaluation flags), rather than manipulating the coordinates directly.
//
// If the lat/lon coordinate contained within an object of this class is
// outside of the UTM grid boundary (>= 84 N or <= 80 S), the vertical UTM
// zone character is set to an asterisk ('*').  You can check the vertical
// UTM zone contained within this class to determine if the coordinate is
// outside of the UTM grid boundary.
//
// Written by Jason Bevins in 1998.  File is in the public domain.
//

#ifndef __UTM_COORD_HPP
#define __UTM_COORD_HPP

#include <string>                       // for string

#include "typedCoord.h"                 // for COORD_TYPE, etc

// These constants are used by the CreateDisplayStrings() and the
// CreateXYCoordStrings() functions to parse the string generated by the
// CreateCoordString() function.  Modify these constants when you modify the
// code that generates the string.  These constants do not affect the code
// that generate these strings, but you may write parsing functions that
// require the positions of the individual elements in the strings.
const int UTM_ZONE_POS     = 0;
const int UTM_ZONE_LEN     = 3;
const int UTM_EASTING_POS  = 4;
const int UTM_EASTING_LEN  = 6;
const int UTM_NORTHING_POS = 11;
const int UTM_NORTHING_LEN = 7;


class UTMCoord: public TypedCoord
{
public:
  UTMCoord ();
  UTMCoord (int utmXZone, char utmYZone, double easting,
            double northing);
  UTMCoord (const TypedCoord& other);
  UTMCoord (const UTMCoord& other);
  void copyUTMCoord (const UTMCoord& other);
  void copyOtherCoord (const TypedCoord& other);
  UTMCoord& operator= (const UTMCoord& other);
  UTMCoord& operator= (const TypedCoord& other);
  virtual const std::string& createCoordString (std::string& coordString) const;
  virtual COORD_TYPE getCoordType () const {return COORD_UTM;}
  virtual void getLatLonCoord (double& lat, double& lon) const;
  virtual void getUTMCoord (int& utmXZone, char& utmYZone,
                            double& easting, double& northing) const;
  void getUTMZone (int& utmXZone, char& utmYZone) const;
  virtual void getXYCoord (double& x, double& y) const;
  bool isOutsideUTMGrid () const;
  virtual void setLatLonCoord (double lat, double lon);
  virtual void setUTMCoord (int utmXZone, char utmYZone, double easting,
                            double northing);

protected:
  // Lazy evaluation flags.
  mutable bool m_requireLatLonConvert;
  mutable bool m_requireUTMConvert;

  // UTM conversion functions.
  void latLonToUTM (double a, double f, int& utmXZone, char& utmYZone,
                    double& easting, double& northing, double lat, double lon) const;
  void latLonToUTMWGS84 (int& utmXZone, char& utmYZone, double& easting,
                         double& northing, double lat, double lon) const;
  void utmToLatLon (double a, double f, int utmXZone, char utmYZone,
                    double easting, double northing, double& lat, double& lon) const;
  void utmToLatLonWGS84 (int utmXZone, char utmYZone, double easting,
                         double northing, double& lat, double& lon) const;

  // UTM values.
  mutable int m_utmXZone;
  mutable char m_utmYZone;
  mutable double m_easting;
  mutable double m_northing;
};

#endif // _UTM_COORD_HPP
