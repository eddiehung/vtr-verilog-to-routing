//===========================================================================//
// Purpose : Method definitions for the TOS_PlaceOptions class.
//
//           Public methods include:
//           - TOS_PlaceOptions_c, ~TOS_PlaceOptions_c
//           - Print
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

#include "TC_MinGrid.h"
#include "TCT_Generic.h"

#include "TIO_PrintHandler.h"

#include "TOS_StringUtils.h"
#include "TOS_PlaceOptions.h"

//===========================================================================//
// Method         : TOS_PlaceOptions_c
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/01/12 jeffr : Original
// 01/15/13 jeffr : Added support for relativePlace members
// 01/18/13 jeffr : Added support for prePlaced members
// 07/23/13 jeffr : Added support for regionPlace members
//===========================================================================//
TOS_PlaceOptions_c::TOS_PlaceOptions_c( 
      void )
      :
      algorithmMode( TOS_PLACE_ALGORITHM_UNDEFINED ),
      channelWidth( 0 ),
      randomSeed( 0 ),
      initTemp( 0.0 ),
      initTempFactor( 0.0 ),
      initTempEpsilon( 0.0 ),
      exitTemp( 0.0 ),
      exitTempFactor( 0.0 ),
      exitTempEpsilon( 0.0 ),
      reduceTemp( 0.0 ),
      reduceTempFactor( 0.0 ),
      innerNum( 0.0 ),
      searchLimit( 0.0 ),
      costMode( TOS_PLACE_COST_UNDEFINED ),
      fixedDelay( 0.0 ),
      timingCostFactor( 0.0 ),
      timingUpdateInt( 0 ),
      timingUpdateCount( 0 ),
      slackInitWeight( 0.0 ),
      slackFinalWeight( 0.0 )
{
   this->regionPlace.enable = false;

   this->relativePlace.enable = false;
   this->relativePlace.rotateEnable = false;
   this->relativePlace.carryChainEnable = false;
   this->relativePlace.maxPlaceRetryCt = 0;
   this->relativePlace.maxMacroRetryCt = 0;

   this->prePlaced.enable = false;
}

//===========================================================================//
TOS_PlaceOptions_c::TOS_PlaceOptions_c( 
      TOS_PlaceAlgorithmMode_t algorithmMode_,
      unsigned int             channelWidth_,
      unsigned int             randomSeed_,
      double                   initTemp_,
      double                   initTempFactor_,
      double                   initTempEpsilon_,
      double                   exitTemp_,
      double                   exitTempFactor_,
      double                   exitTempEpsilon_,
      double                   reduceTemp_,
      double                   reduceTempFactor_,
      double                   innerNum_,
      double                   searchLimit_,
      TOS_PlaceCostMode_t      costMode_,
      double                   timingCostFactor_,
      unsigned int             timingUpdateInt_,
      unsigned int             timingUpdateCount_,
      double                   slackInitWeight_,
      double                   slackFinalWeight_,
      bool                     regionPlace_enable_,
      bool                     relativePlace_enable_,
      bool                     relativePlace_rotateEnable_,
      bool                     relativePlace_carryChainEnable_,
      unsigned int             relativePlace_maxPlaceRetryCt_,
      unsigned int             relativePlace_maxMacroRetryCt_,
      bool                     prePlaced_enable_ )
      :
      algorithmMode( algorithmMode_ ),
      channelWidth( channelWidth_ ), 
      randomSeed( randomSeed_ ),
      initTemp( initTemp_ ),
      initTempFactor( initTempFactor_ ),
      initTempEpsilon( initTempEpsilon_ ),
      exitTemp( exitTemp_ ),
      exitTempFactor( exitTempFactor_ ),
      exitTempEpsilon( exitTempEpsilon_ ),
      reduceTemp( reduceTemp_ ),
      reduceTempFactor( reduceTempFactor_ ),
      innerNum( innerNum_ ),
      searchLimit( searchLimit_ ),
      costMode( costMode_ ),
      fixedDelay( 0.0 ),
      timingCostFactor( timingCostFactor_ ),
      timingUpdateInt( timingUpdateInt_ ),
      timingUpdateCount( timingUpdateCount_ ),
      slackInitWeight( slackInitWeight_ ),
      slackFinalWeight( slackFinalWeight_ )
{
   this->regionPlace.enable = regionPlace_enable_;

   this->relativePlace.enable = relativePlace_enable_;
   this->relativePlace.rotateEnable = relativePlace_rotateEnable_;
   this->relativePlace.carryChainEnable = relativePlace_carryChainEnable_;
   this->relativePlace.maxPlaceRetryCt = relativePlace_maxPlaceRetryCt_;
   this->relativePlace.maxMacroRetryCt = relativePlace_maxMacroRetryCt_;

   this->prePlaced.enable = prePlaced_enable_;
}

//===========================================================================//
// Method         : ~TOS_PlaceOptions_c
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/01/12 jeffr : Original
//===========================================================================//
TOS_PlaceOptions_c::~TOS_PlaceOptions_c( 
      void )
{
}

//===========================================================================//
// Method         : Print
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/01/12 jeffr : Original
// 01/15/13 jeffr : Added support for relativePlace members
// 01/18/13 jeffr : Added support for prePlaced members
// 07/23/13 jeffr : Added support for regionPlace members
//===========================================================================//
void TOS_PlaceOptions_c::Print( 
      FILE*  pfile,
      size_t spaceLen ) const
{
   TC_MinGrid_c& MinGrid = TC_MinGrid_c::GetInstance( );
   unsigned int precision = MinGrid.GetPrecision( );

   TIO_PrintHandler_c& printHandler = TIO_PrintHandler_c::GetInstance( );

   string srAlgorithmMode, srCostMode;
   TOS_ExtractStringPlaceAlgorithmMode( this->algorithmMode, &srAlgorithmMode );
   TOS_ExtractStringPlaceCostMode( this->costMode, &srCostMode );

   printHandler.Write( pfile, spaceLen, "PLACE_ALGORITHM            = %s\n", TIO_SR_STR( srAlgorithmMode ));

   if( this->channelWidth > 0 )
   {
      printHandler.Write( pfile, spaceLen, "PLACE_CHANNEL_WIDTH        = %u\n", this->channelWidth );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_CHANNEL_WIDTH\n" );
   }

   if( this->randomSeed > 0 )
   {
      printHandler.Write( pfile, spaceLen, "PLACE_RANDOM_SEED          = %u\n", this->randomSeed );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_RANDOM_SEED\n" );
   }
   if( TCTF_IsGT( this->initTemp, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_INIT            = %0.*f\n", precision, this->initTemp );
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_INIT_FACTOR     = %0.*f\n", precision, this->initTempFactor );
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_INIT_EPSILON    = %0.*f\n", precision, this->initTempEpsilon );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_INIT\n" );
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_INIT_FACTOR\n" );
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_INIT_EPSILON\n" );
   }
   if( TCTF_IsGT( this->exitTemp, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_EXIT            = %0.*f\n", precision, this->exitTemp );
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_EXIT_FACTOR     = %0.*f\n", precision, this->exitTempFactor );
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_EXIT_EPSILON    = %0.*f\n", precision, this->exitTempEpsilon );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_EXIT\n" );
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_EXIT_FACTOR\n" );
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_EXIT_EPSILON\n" );
   }
   if( TCTF_IsGT( this->reduceTemp, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_REDUCE          = %0.*f\n", precision, this->reduceTemp );
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_REDUCE_FACTOR   = %0.*f\n", precision, this->reduceTempFactor );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_REDUCE\n" );
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_REDUCE_FACTOR\n" );
   }
   if( TCTF_IsGT( this->innerNum, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TEMP_INNER_NUM       = %0.*f\n", precision, this->innerNum );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TEMP_INNER_NUM\n" );
   }
   if( TCTF_IsGT( this->searchLimit, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_SEARCH_LIMIT         = %0.*f\n", precision, this->searchLimit );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_SEARCH_LIMIT\n" );
   }

   printHandler.Write( pfile, spaceLen, "PLACE_COST_MODE            = %s\n", TIO_SR_STR( srCostMode ));

   if( TCTF_IsGT( this->timingCostFactor, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TIMING_COST_FACTOR   = %0.*f\n", precision, this->timingCostFactor );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TIMING_COST_FACTOR\n" );
   }
   if( this->timingUpdateInt > 0 )
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TIMING_UPDATE_INT    = %u\n", this->timingUpdateInt );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TIMING_UPDATE_INT\n" );
   }
   if( this->timingUpdateCount > 0 )
   {
      printHandler.Write( pfile, spaceLen, "PLACE_TIMING_UPDATE_COUNT  = %u\n", this->timingUpdateCount );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_TIMING_UPDATE_COUNT\n" );
   }
   if( TCTF_IsGT( this->slackInitWeight, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_SLACK_INIT_WEIGHT    = %0.*f\n", precision, this->slackInitWeight );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_SLACK_INIT_WEIGHT\n" );
   }
   if( TCTF_IsGT( this->slackFinalWeight, 0.0 ))
   {
      printHandler.Write( pfile, spaceLen, "PLACE_SLACK_FINAL_WEIGHT   = %0.*f\n", precision, this->slackFinalWeight );
   }
   else
   {
      printHandler.Write( pfile, spaceLen, "// PLACE_SLACK_FINAL_WEIGHT\n" );
   }

   printHandler.Write( pfile, spaceLen, "\n" );
   printHandler.Write( pfile, spaceLen, "PLACE_REGIONS_ENABLE       = %s\n", TIO_BOOL_STR( this->regionPlace.enable ));

   printHandler.Write( pfile, spaceLen, "PLACE_RELATIVE_ENABLE      = %s\n", TIO_BOOL_STR( this->relativePlace.enable ));
   printHandler.Write( pfile, spaceLen, "PLACE_RELATIVE_ROTATE      = %s\n", TIO_BOOL_STR( this->relativePlace.rotateEnable ));
   printHandler.Write( pfile, spaceLen, "PLACE_RELATIVE_CARRY_CHAIN = %s\n", TIO_BOOL_STR( this->relativePlace.carryChainEnable ));
   printHandler.Write( pfile, spaceLen, "PLACE_RELATIVE_INIT_PLACE  = %u\n", this->relativePlace.maxPlaceRetryCt );
   printHandler.Write( pfile, spaceLen, "PLACE_RELATIVE_INIT_MACRO  = %u\n", this->relativePlace.maxMacroRetryCt );

   printHandler.Write( pfile, spaceLen, "PLACE_PREPLACED_ENABLE     = %s\n", TIO_BOOL_STR( this->prePlaced.enable ));
}
