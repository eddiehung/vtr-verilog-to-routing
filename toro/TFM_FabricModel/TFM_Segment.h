//===========================================================================//
// Purpose : Declaration and inline definitions for a TFM_Segment class.
//
//           Inline methods include:
//           - SetName (required for TCT_SortedNameDynamicVector_c class)
//           - GetName (required for TCT_SortedNameDynamicVector_c class)
//           - GetCompare (required for TCT_BSearch and TCT_QSort classes)
//           - IsValid
//
//===========================================================================//

//---------------------------------------------------------------------------//
// Copyright (C) 2012-2013 Jeff Rudolph, Texas Instruments (jrudolph@ti.com) //
//                                                                           //
// Permission is hereby granted, free of charge, to any person obtaining a   //
// copy of this software and associated documentation files (the "Software"),//
// to deal in the Software without restriction, including without limitation //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,  //
// and/or sell copies of the Software, and to permit persons to whom the     //
// Software is furnished to do so, subject to the following conditions:      //
//                                                                           //
// The above copyright notice and this permission notice shall be included   //
// in all copies or substantial portions of the Software.                    //
//                                                                           //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   //
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                //
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN // 
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,  //
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR     //
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE //
// USE OR OTHER DEALINGS IN THE SOFTWARE.                                    //
//---------------------------------------------------------------------------//

#ifndef TFM_SEGMENT_H
#define TFM_SEGMENT_H

#include <cstdio>
#include <string>
using namespace std;

#include "TGS_Path.h"

//===========================================================================//
// Purpose        : Class declaration
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/20/12 jeffr : Original
//===========================================================================//
class TFM_Segment_c
{
public:

   TFM_Segment_c( void );
   TFM_Segment_c( const string& srName,
                  const TGS_Path_c& path,
                  unsigned int index );
   TFM_Segment_c( const char* pszName,
                  const TGS_Path_c& path,
                  unsigned int index );
   TFM_Segment_c( const string& srName );
   TFM_Segment_c( const char* pszName );
   TFM_Segment_c( const TFM_Segment_c& segment );
   ~TFM_Segment_c( void );

   TFM_Segment_c& operator=( const TFM_Segment_c& segment );
   bool operator==( const TFM_Segment_c& segment ) const;
   bool operator!=( const TFM_Segment_c& segment ) const;

   void Print( FILE* pfile = stdout, size_t spaceLen = 0 ) const;

   void SetName( const string& srName );
   void SetName( const char* pszName );
   const char* GetName( void ) const;
   const char* GetCompare( void ) const;

   bool IsValid( void ) const;

public:

   string srName;      // Unique identifier

   TGS_Path_c path;    // Defines routing segment line and width
   unsigned int index; // Defines routing segment track index

   class TFM_SegmentTiming_c
   {
   public:

      double res;      // Routing segment resistance (ohms)
      double cap;      // Routing segment capacitance (fF)
   } timing;
};

//===========================================================================//
// Purpose        : Class inline definition(s)
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/20/12 jeffr : Original
//===========================================================================//
inline void TFM_Segment_c::SetName( 
      const string& srName_ )
{
   this->srName = srName_;
}

//===========================================================================//
inline void TFM_Segment_c::SetName( 
      const char* pszName )
{
   this->srName = TIO_PSZ_STR( pszName );
}

//===========================================================================//
inline const char* TFM_Segment_c::GetName( 
      void ) const
{
   return( TIO_SR_STR( this->srName ));
}

//===========================================================================//
inline const char* TFM_Segment_c::GetCompare( 
      void ) const 
{
   return( TIO_SR_STR( this->srName ));
}

//===========================================================================//
inline bool TFM_Segment_c::IsValid( 
      void ) const
{
   return( this->srName.length( ) ? true : false );
}

#endif
