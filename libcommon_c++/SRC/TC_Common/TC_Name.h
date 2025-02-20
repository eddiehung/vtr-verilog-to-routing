//===========================================================================//
// Purpose : Declaration and inline definitions for a (regexp) TC_Name class.
//
//           Inline methods include:
//           - TC_Name, ~TC_Name
//           - SetValue
//           - GetValue
//           - GetLength
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

#ifndef TC_NAME_H
#define TC_NAME_H

#include <cstdio>
#include <string>
using namespace std;

#include "TIO_Typedefs.h"

#include "TC_Typedefs.h"

//===========================================================================//
// Purpose        : Class declaration
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/01/12 jeffr : Original
//===========================================================================//
class TC_Name_c
{
public:

   TC_Name_c( const char* pszName = 0 );
   TC_Name_c( const string& srName );
   TC_Name_c( const char* pszName,
              int value );
   TC_Name_c( const string& srName,
              int value );
   TC_Name_c( const TC_Name_c& name );
   ~TC_Name_c( void );

   TC_Name_c& operator=( const TC_Name_c& name );
   bool operator<( const TC_Name_c& name ) const;
   bool operator==( const TC_Name_c& name ) const;
   bool operator!=( const TC_Name_c& name ) const;

   void Print( FILE* pfile = stdout, size_t spaceLen = 0 ) const;

   void ExtractString( string* psrName ) const;

   void SetName( const char* pszName );
   void SetName( const string& srName );
   void SetValue( int value );

   const string& GetString( void ) const;
   const char* GetCompare( void ) const;
   const char* GetName( void ) const;
   int GetValue( void ) const;
   size_t GetLength( void ) const;

   bool IsValid( void ) const;

private:

   string srName_;
   int    value_;
};

//===========================================================================//
// Purpose        : Class inline definition(s)
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/01/12 jeffr : Original
//===========================================================================//
inline TC_Name_c::TC_Name_c( 
      const char* pszName )
      :
      srName_( TIO_PSZ_STR( pszName )),
      value_( 0 )
{
}

//===========================================================================//
inline TC_Name_c::TC_Name_c( 
      const string& srName )
      :
      srName_( srName ),
      value_( 0 )
{
}

//===========================================================================//
inline TC_Name_c::TC_Name_c( 
      const char*  pszName,
            int    value )
      :
      srName_( TIO_PSZ_STR( pszName )),
      value_( value )
{
}

//===========================================================================//
inline TC_Name_c::TC_Name_c( 
      const string& srName,
            int     value )
      :
      srName_( srName ),
      value_( value )
{
}

//===========================================================================//
inline TC_Name_c::TC_Name_c( 
      const TC_Name_c& name )
      :
      srName_( name.srName_ ),
      value_( name.value_ )
{
}

//===========================================================================//
inline TC_Name_c::~TC_Name_c( 
      void )
{
}

//===========================================================================//
inline void TC_Name_c::SetName( 
      const char* pszName )
{
   this->srName_ = TIO_PSZ_STR( pszName );
}

//===========================================================================//
inline void TC_Name_c::SetName( 
      const string& srName )
{
   this->srName_ = srName;
}

//===========================================================================//
inline void TC_Name_c::SetValue(
      int value ) 
{
   this->value_ = value;
}

//===========================================================================//
inline const string& TC_Name_c::GetString( 
      void ) const 
{
   return( this->srName_ );
}

//===========================================================================//
inline const char* TC_Name_c::GetName( 
      void ) const 
{
   return( this->srName_.length( ) ? this->srName_.data( ) : 0 );
}

//===========================================================================//
inline int TC_Name_c::GetValue( 
      void ) const 
{
   return( this->value_ );
}

//===========================================================================//
inline size_t TC_Name_c::GetLength( 
      void ) const 
{
   return( this->srName_.length( ));
}

//===========================================================================//
inline bool TC_Name_c::IsValid( 
      void ) const
{
   return( this->srName_.length( ) ? true : false );
}

#endif 
