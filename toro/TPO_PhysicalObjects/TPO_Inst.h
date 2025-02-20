//===========================================================================//
// Purpose : Declaration and inline definitions for a TPO_Inst class.
//
//           Inline methods include:
//           - SetName (required for TCT_SortedNameDynamicVector_c class)
//           - GetName (required for TCT_SortedNameDynamicVector_c class)
//           - GetCompare (required for TCT_BSearch and TCT_QSort classes)
//           - GetCellName
//           - GetPinList
//           - GetSource
//           - GetInputOutputType
//           - GetNamesLogicBitsList
//           - GetLatchClockType, GetLatchInitState
//           - GetSubcktPinMapList
//           - GetPackInstHierMapList
//           - GetPlaceFabricName
//           - GetPlaceStatus, GetPlaceOrigin
//           - GetPlaceRegionList, GetPlaceRelativeList
//           - SetCellName
//           - SetPinList
//           - SetSource
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

#ifndef TPO_INST_H
#define TPO_INST_H

#include <cstdio>
#include <string>
using namespace std;

#include "TC_Bit.h"
#include "TC_NameType.h"

#include "TGS_Typedefs.h"
#include "TGS_Region.h"

#include "TGO_Typedefs.h"
#include "TGO_Point.h"

#include "TLO_Typedefs.h"
#include "TLO_Cell.h"

#include "TPO_Typedefs.h"
#include "TPO_PinMap.h"
#include "TPO_InstHierMap.h"
#include "TPO_PlaceRelative.h"

//===========================================================================//
// Purpose        : Class declaration
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/15/12 jeffr : Original
//===========================================================================//
class TPO_Inst_c
{
public:

   TPO_Inst_c( void );
   TPO_Inst_c( const string& srName );
   TPO_Inst_c( const char* pszName );
   TPO_Inst_c( const string& srName,
               const string& srCellName,
               const TPO_PinList_t& pinList,
               TPO_InstSource_t source,
               const TPO_LogicBitsList_t& logicBitsList );
   TPO_Inst_c( const char* pszName,
               const char* pszCellName,
               const TPO_PinList_t& pinList,
               TPO_InstSource_t source,
               const TPO_LogicBitsList_t& logicBitsList );
   TPO_Inst_c( const string& srName,
               const string& srCellName,
               const TPO_PinList_t& pinList,
               TPO_InstSource_t source,
               TPO_LatchType_t clockType,
               TPO_LatchState_t initState );
   TPO_Inst_c( const char* pszName,
               const char* pszCellName,
               const TPO_PinList_t& pinList,
               TPO_InstSource_t source,
               TPO_LatchType_t clockType,
               TPO_LatchState_t initState );
   TPO_Inst_c( const string& srName,
               const string& srCellName,
               TPO_InstSource_t source,
               const TPO_PinMapList_t& pinMapList );
   TPO_Inst_c( const char* pszName,
               const char* pszCellName,
               TPO_InstSource_t source,
               const TPO_PinMapList_t& pinMapList );
   TPO_Inst_c( const TPO_Inst_c& inst );
   ~TPO_Inst_c( void );

   TPO_Inst_c& operator=( const TPO_Inst_c& inst );
   bool operator<( const TPO_Inst_c& inst ) const;
   bool operator==( const TPO_Inst_c& inst ) const;
   bool operator!=( const TPO_Inst_c& inst ) const;

   void Print( FILE* pfile = stdout, size_t spaceLen = 0,
               const char* pszUsage = 0 ) const;
   void PrintBLIF( FILE* pfile = stdout, size_t spaceLen = 0 ) const;

   void SetName( const string& srName );
   void SetName( const char* pszName );
   const char* GetName( void ) const;
   const char* GetCompare( void ) const;

   const char* GetCellName( void ) const;
   const TPO_PinList_t& GetPinList( void ) const;
   TPO_InstSource_t GetSource( void ) const;

   TC_TypeMode_t GetInputOutputType( void ) const;
   const TPO_LogicBitsList_t& GetNamesLogicBitsList( void ) const;
   TPO_LatchType_t GetLatchClockType( void ) const;
   TPO_LatchState_t GetLatchInitState( void ) const;
   const TPO_PinMapList_t& GetSubcktPinMapList( void ) const;

   const TPO_InstHierMapList_t& GetPackInstHierMapList( void ) const;

   const char* GetPlaceFabricName( void ) const;
   TPO_StatusMode_t GetPlaceStatus( void ) const;
   const TGO_Point_c& GetPlaceOrigin( void ) const;
   const TGS_RegionList_t& GetPlaceRegionList( void ) const;
   const TPO_PlaceRelativeList_t& GetPlaceRelativeList( void ) const;
   
   void SetCellName( const string& srCellName );
   void SetCellName( const char* pszCellName );
   void SetPinList( const TPO_PinList_t& pinList );
   void SetSource( TPO_InstSource_t source );

   void SetInputOutputType( TC_TypeMode_t type );
   void SetNamesLogicBitsList( const TPO_LogicBitsList_t& logicBitsList );
   void SetLatchClockType( TPO_LatchType_t clockType );
   void SetLatchInitState( TPO_LatchState_t initState );
   void SetSubcktPinMapList( const TPO_PinMapList_t& pinMapList );

   void SetPackInstHierMapList( const TPO_InstHierMapList_t& instHierMapList );

   void SetPlaceFabricName( const string& srFabricName );
   void SetPlaceFabricName( const char* pszFabricName );
   void SetPlaceStatus( TPO_StatusMode_t status );
   void SetPlaceOrigin( const TGO_Point_c& origin );
   void SetPlaceRegionList( const TGS_RegionList_t& regionList );
   void SetPlaceRelativeList( const TPO_PlaceRelativeList_t& relativeList );

   void AddPin( const TPO_Pin_t& pin );

   const TPO_Pin_t* FindPin( TC_TypeMode_t type ) const;

   size_t FindPinCount( TC_TypeMode_t type,
                        const TLO_CellList_t& cellList ) const;

   void Clear( void );

   bool IsValid( void ) const;

private:

   string           srName_;      // Defines instance name
   string           srCellName_;  // Defines instance's master cell name
   TPO_PinList_t    pinList_;     // List of instance's pins

   TPO_InstSource_t source_;      // Defines instance source (optional)
                                  // For example: ".input", ".names", or ".latch"
   class TPO_InstInputOutput_c
   {
   public:

      TC_TypeMode_t type;         // Defines port type (optional)
                                  // For example: ".input" or ".output"
   } inputOutput_;

   class TPO_InstNames_c
   {
   public:

      TPO_LogicBitsList_t logicBitsList;  
                                  // Defines PLA logic bits (optional for ".names")
   } names_;                      // For example: "1--1 1", "-1-1 1", or "0-11 1"

   class TPO_InstLatch_c
   {
   public:
   
      TPO_LatchType_t clockType;  // Defines clocking type (optional for ".latch")
                                  // For example: FE, RE, AH, AL, or AS
      TPO_LatchState_t initState; // Defines initial state (optional for ".latch")
                                  // For example: true, false, or don't care
   } latch_;

   class TPO_InstSubckt_c
   {
   public:

      TPO_PinMapList_t pinMapList;// Defines ".subckt" pin-to-pin map table
   } subckt_;

   class TPO_InstPack_c
   {
   public:

      TPO_InstHierMapList_t instHierMapList;
                                  // Defines packing (instance to PB architecture)
   } pack_;

   class TPO_InstPlace_c
   {
   public:

      string srFabricName;        // Defines placement fabric name (optional)
      TPO_StatusMode_t status;    // Defines placement status mode (optional)
      TGO_Point_c origin;         // Defines placement origin point (optional)
      TGS_RegionList_t regionList;// Defines placement region(s) (optional)
      TPO_PlaceRelativeList_t relativeList;
                                  // Defines placement relative(s) (optional)
   } place_;

private:

   enum TPO_DefCapacity_e 
   { 
      TPO_PIN_LIST_DEF_CAPACITY = 64,
      TPO_LOGIC_BITS_LIST_DEF_CAPACITY = 8,
      TPO_PIN_MAP_LIST_DEF_CAPACITY = 64,
      TPO_INST_HIER_MAP_LIST_DEF_CAPACITY = 1,
      TPO_RELATIVE_LIST_DEF_CAPACITY = 1,
      TPO_REGION_LIST_DEF_CAPACITY = 1
   };
};

//===========================================================================//
// Purpose        : Class inline definition(s)
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/15/12 jeffr : Original
//===========================================================================//
inline void TPO_Inst_c::SetName( 
      const string& srName )
{
   this->srName_ = srName;
}

//===========================================================================//
inline void TPO_Inst_c::SetName( 
      const char* pszName )
{
   this->srName_ = TIO_PSZ_STR( pszName );
}

//===========================================================================//
inline const char* TPO_Inst_c::GetName( 
      void ) const
{
   return( TIO_SR_STR( this->srName_ ));
}

//===========================================================================//
inline const char* TPO_Inst_c::GetCompare( 
      void ) const 
{
   return( TIO_SR_STR( this->srName_ ));
}

//===========================================================================//
inline const char* TPO_Inst_c::GetCellName( 
      void ) const 
{
   return( TIO_SR_STR( this->srCellName_ ));
}

//===========================================================================//
inline const TPO_PinList_t& TPO_Inst_c::GetPinList( 
      void ) const
{
   return( this->pinList_ );
}

//===========================================================================//
inline TPO_InstSource_t TPO_Inst_c::GetSource( 
      void ) const
{
   return( this->source_ );
}

//===========================================================================//
inline TC_TypeMode_t TPO_Inst_c::GetInputOutputType( 
      void ) const
{
   return( this->inputOutput_.type );
}

//===========================================================================//
inline const TPO_LogicBitsList_t& TPO_Inst_c::GetNamesLogicBitsList( 
      void ) const
{
   return( this->names_.logicBitsList );
}

//===========================================================================//
inline TPO_LatchType_t TPO_Inst_c::GetLatchClockType( 
      void ) const
{
   return( this->latch_.clockType );
}

//===========================================================================//
inline TPO_LatchState_t TPO_Inst_c::GetLatchInitState( 
      void ) const
{
   return( this->latch_.initState );
}

//===========================================================================//
inline const TPO_PinMapList_t& TPO_Inst_c::GetSubcktPinMapList( 
      void ) const
{
   return( this->subckt_.pinMapList );
}

//===========================================================================//
inline const TPO_InstHierMapList_t& TPO_Inst_c::GetPackInstHierMapList( 
      void ) const
{
   return( this->pack_.instHierMapList );
}

//===========================================================================//
inline const char* TPO_Inst_c::GetPlaceFabricName( 
      void ) const
{
   return( TIO_SR_STR( this->place_.srFabricName ));
}

//===========================================================================//
inline TPO_StatusMode_t TPO_Inst_c::GetPlaceStatus(
      void ) const
{
   return( this->place_.status );
}

//===========================================================================//
inline const TGO_Point_c& TPO_Inst_c::GetPlaceOrigin(
      void ) const
{
   return( this->place_.origin );
}

//===========================================================================//
inline const TGS_RegionList_t& TPO_Inst_c::GetPlaceRegionList( 
      void ) const
{
   return( this->place_.regionList );
}

//===========================================================================//
inline const TPO_PlaceRelativeList_t& TPO_Inst_c::GetPlaceRelativeList( 
      void ) const
{
   return( this->place_.relativeList );
}

//===========================================================================//
inline void TPO_Inst_c::SetCellName( 
      const string& srCellName )
{
   this->srCellName_ = srCellName;
}

//===========================================================================//
inline void TPO_Inst_c::SetCellName( 
      const char* pszCellName )
{
   this->srCellName_ = TIO_PSZ_STR( pszCellName );
}

//===========================================================================//
inline void TPO_Inst_c::SetPinList(
      const TPO_PinList_t& pinList )
{
   this->pinList_ = pinList;
}

//===========================================================================//
inline void TPO_Inst_c::SetSource(
      TPO_InstSource_t source )
{
   this->source_ = source;
}

//===========================================================================//
inline bool TPO_Inst_c::IsValid( 
      void ) const
{
   return( this->srName_.length( ) ? true : false );
}

#endif
