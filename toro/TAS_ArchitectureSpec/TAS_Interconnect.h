//===========================================================================//
// Purpose : Declaration and inline definitions for a TAS_Interconnect class.
//
//           Inline methods include:
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

#ifndef TAS_INTERCONNECT_H
#define TAS_INTERCONNECT_H

#include <cstdio>
#include <string>
using namespace std;

#include "TAS_Typedefs.h"
#include "TAS_TimingDelayLists.h"

//===========================================================================//
// Purpose        : Class declaration
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/15/12 jeffr : Original
//===========================================================================//
class TAS_Interconnect_c
{
public:

   TAS_Interconnect_c( void );
   TAS_Interconnect_c( const string& srName );
   TAS_Interconnect_c( const char* pszName );
   TAS_Interconnect_c( const TAS_Interconnect_c& interconnect );
   ~TAS_Interconnect_c( void );

   TAS_Interconnect_c& operator=( const TAS_Interconnect_c& interconnect );
   bool operator==( const TAS_Interconnect_c& interconnect ) const;
   bool operator!=( const TAS_Interconnect_c& interconnect ) const;

   void Print( FILE* pfile = stdout, size_t spaceLen = 0 ) const;

   void PrintXML( void ) const;
   void PrintXML( FILE* pfile, size_t spaceLen ) const;

   bool IsValid( void ) const;

public:

   string srName;                       // Interconnect name

   TAS_InterconnectMapType_t mapType;   // Selects map: COMPLETE|DIRECT|MUX

   TAS_InputNameList_t inputNameList;   // List of 1+ input pin names
   TAS_OutputNameList_t outputNameList; // List of 1+ output pin names

   TAS_TimingDelayLists_c timingDelayLists; 
                             // Defines max, clock setup, and clock-to-Q delays
private:

   enum TAS_DefCapacity_e 
   { 
      TAS_INPUT_NAME_LIST_DEF_CAPACITY = 64,
      TAS_OUTPUT_NAME_LIST_DEF_CAPACITY = 64
   };
};

//===========================================================================//
// Purpose        : Class inline definition(s)
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/15/12 jeffr : Original
//===========================================================================//
inline bool TAS_Interconnect_c::IsValid( 
      void ) const
{
   return( this->srName.length( ) ? true : false );
}

#endif
