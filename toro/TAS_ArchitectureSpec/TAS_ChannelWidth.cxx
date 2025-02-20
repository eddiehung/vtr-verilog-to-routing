//===========================================================================//
// Purpose : Method definitions for the TAS_ChannelWidth class.
//
//           Public methods include:
//           - TAS_ChannelWidth_c, ~TAS_ChannelWidth_c
//           - operator=
//           - operator==, operator!=
//           - Print
//           - PrintXML
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

#include "TC_StringUtils.h"

#include "TIO_PrintHandler.h"

#include "TAS_StringUtils.h"
#include "TAS_ChannelWidth.h"

//===========================================================================//
// Method         : TAS_ChannelWidth_c
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
TAS_ChannelWidth_c::TAS_ChannelWidth_c( 
      void )
      :
      usageMode( TAS_CHANNEL_USAGE_UNDEFINED ),
      width( 0.0 ),
      distrMode( TAS_CHANNEL_DISTR_UNDEFINED ),
      peak( 0.0 ),
      xpeak( 0.0 ),
      dc( 0.0 )
{
}

//===========================================================================//
TAS_ChannelWidth_c::TAS_ChannelWidth_c( 
      const TAS_ChannelWidth_c& channelWidth )
      :
      usageMode( channelWidth.usageMode ),
      width( channelWidth.width ),
      distrMode( channelWidth.distrMode ),
      peak( channelWidth.peak ),
      xpeak( channelWidth.xpeak ),
      dc( channelWidth.dc )
{
}

//===========================================================================//
// Method         : ~TAS_ChannelWidth_c
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
TAS_ChannelWidth_c::~TAS_ChannelWidth_c( 
      void )
{
}

//===========================================================================//
// Method         : operator=
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
TAS_ChannelWidth_c& TAS_ChannelWidth_c::operator=( 
      const TAS_ChannelWidth_c& channelWidth )
{
   if( &channelWidth != this )
   {
      this->usageMode = channelWidth.usageMode;
      this->width = channelWidth.width;
      this->distrMode = channelWidth.distrMode;
      this->peak = channelWidth.peak;
      this->xpeak = channelWidth.xpeak;
      this->dc = channelWidth.dc;
   }
   return( *this );
}

//===========================================================================//
// Method         : operator==
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
bool TAS_ChannelWidth_c::operator==( 
      const TAS_ChannelWidth_c& channelWidth ) const
{
   return(( this->usageMode == channelWidth.usageMode ) &&
          ( TCTF_IsEQ( this->width, channelWidth.width )) &&
          ( this->distrMode == channelWidth.distrMode ) &&
          ( TCTF_IsEQ( this->peak, channelWidth.peak )) &&
          ( TCTF_IsEQ( this->xpeak, channelWidth.xpeak )) &&
          ( TCTF_IsEQ( this->dc, channelWidth.dc )) ?
          true : false );
}

//===========================================================================//
// Method         : operator!=
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
bool TAS_ChannelWidth_c::operator!=( 
      const TAS_ChannelWidth_c& channelWidth ) const
{
   return( !this->operator==( channelWidth ) ? true : false );
}

//===========================================================================//
// Method         : Print
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
void TAS_ChannelWidth_c::Print( 
      FILE*  pfile,
      size_t spaceLen ) const
{
   TC_MinGrid_c& MinGrid = TC_MinGrid_c::GetInstance( );
   unsigned int precision = MinGrid.GetPrecision( );

   TIO_PrintHandler_c& printHandler = TIO_PrintHandler_c::GetInstance( );

   string srUsageMode;
   TAS_ExtractStringChannelUsageMode( this->usageMode, &srUsageMode );

   string srDistrMode;
   TAS_ExtractStringChannelDistrMode( this->distrMode, &srDistrMode );

   switch( this->usageMode )
   {
   case TAS_CHANNEL_USAGE_IO:
      printHandler.Write( pfile, spaceLen, "<%s width=\"%0.*f\"/>",
                                           TIO_SR_STR( srUsageMode ),
                                           precision, this->width );
      break;

   case TAS_CHANNEL_USAGE_X:
   case TAS_CHANNEL_USAGE_Y:
      switch( this->distrMode )
      {
      case TAS_CHANNEL_DISTR_UNIFORM:
         printHandler.Write( pfile, spaceLen, "<%s distr=\"%s\" peak=\"%0.*f\"/>",
                                              TIO_SR_STR( srUsageMode ),
                                              TIO_SR_STR( srDistrMode ),
                                              precision, this->peak );
         break;

      case TAS_CHANNEL_DISTR_GAUSSIAN:
      case TAS_CHANNEL_DISTR_PULSE:
         printHandler.Write( pfile, spaceLen, "<%s distr=\"%s\" peak=\"%0.*f\" xpeak=\"%0.*f\" dc=\"%0.*f\" width=\"%0.*f\"/>",
                                              TIO_SR_STR( srUsageMode ),
                                              TIO_SR_STR( srDistrMode ),
                                              precision, this->peak,
                                              precision, this->xpeak,
                                              precision, this->dc,
                                              precision, this->width );
         break;

      case TAS_CHANNEL_DISTR_DELTA:
         printHandler.Write( pfile, spaceLen, "<%s distr=\"%s\" peak=\"%0.*f\" xpeak=\"%0.*f\" dc=\"%0.*f\"/>",
                                              TIO_SR_STR( srUsageMode ),
                                              TIO_SR_STR( srDistrMode ),
                                              precision, this->peak,
                                              precision, this->xpeak,
                                              precision, this->dc );
         break;

      case TAS_CHANNEL_DISTR_UNDEFINED:
         break;
      }
      break;

   case TAS_CHANNEL_USAGE_UNDEFINED:
      break;
   }
}

//===========================================================================//
// Method         : PrintXML
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 07/15/12 jeffr : Original
//===========================================================================//
void TAS_ChannelWidth_c::PrintXML( 
      void ) const
{
   FILE* pfile = 0;
   size_t spaceLen = 0;

   this->PrintXML( pfile, spaceLen );
}

//===========================================================================//
void TAS_ChannelWidth_c::PrintXML( 
      FILE*  pfile,
      size_t spaceLen ) const
{
   TC_MinGrid_c& MinGrid = TC_MinGrid_c::GetInstance( );
   unsigned int precision = MinGrid.GetPrecision( );

   TIO_PrintHandler_c& printHandler = TIO_PrintHandler_c::GetInstance( );

   string srUsageMode;
   TAS_ExtractStringChannelUsageMode( this->usageMode, &srUsageMode );

   string srDistrMode;
   TAS_ExtractStringChannelDistrMode( this->distrMode, &srDistrMode );

   switch( this->usageMode )
   {
   case TAS_CHANNEL_USAGE_IO:
      printHandler.Write( pfile, spaceLen, "<%s width=\"%0.*f\"/>\n",
                                           TIO_SR_STR( srUsageMode ),
                                           precision, this->width );
      break;

   case TAS_CHANNEL_USAGE_X:
   case TAS_CHANNEL_USAGE_Y:
      switch( this->distrMode )
      {
      case TAS_CHANNEL_DISTR_UNIFORM:
         printHandler.Write( pfile, spaceLen, "<%s distr=\"%s\" peak=\"%0.*f\"/>\n",
                                              TIO_SR_STR( srUsageMode ),
                                              TIO_SR_STR( srDistrMode ),
                                              precision, this->peak );
         break;

      case TAS_CHANNEL_DISTR_GAUSSIAN:
      case TAS_CHANNEL_DISTR_PULSE:
         printHandler.Write( pfile, spaceLen, "<%s distr=\"%s\" peak=\"%0.*f\" xpeak=\"%0.*f\" dc=\"%0.*f\" width=\"%0.*f\"/>\n",
                                              TIO_SR_STR( srUsageMode ),
                                              TIO_SR_STR( srDistrMode ),
                                              precision, this->peak,
                                              precision, this->xpeak,
                                              precision, this->dc,
                                              precision, this->width );
         break;

      case TAS_CHANNEL_DISTR_DELTA:
         printHandler.Write( pfile, spaceLen, "<%s distr=\"%s\" peak=\"%0.*f\" xpeak=\"%0.*f\" dc=\"%0.*f\"/>\n",
                                              TIO_SR_STR( srUsageMode ),
                                              TIO_SR_STR( srDistrMode ),
                                              precision, this->peak,
                                              precision, this->xpeak,
                                              precision, this->dc );
         break;

      case TAS_CHANNEL_DISTR_UNDEFINED:
         break;
      }
      break;

   case TAS_CHANNEL_USAGE_UNDEFINED:
      break;
   }
}
