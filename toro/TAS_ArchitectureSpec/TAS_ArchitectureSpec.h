//===========================================================================//
// Purpose : Declaration and inline definitions for a TAS_ArchitectureSpec 
//           class.
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

#ifndef TAS_ARCHITECTURE_SPEC_H
#define TAS_ARCHITECTURE_SPEC_H

#include <cstdio>
#include <string>
using namespace std;

#include "TAS_Typedefs.h"
#include "TAS_Config.h"
#include "TAS_PhysicalBlock.h"
#include "TAS_SwitchBox.h"
#include "TAS_Segment.h"
#include "TAS_CarryChain.h"
#include "TAS_Cell.h"

//===========================================================================//
// Purpose        : Class declaration
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 05/15/12 jeffr : Original
//===========================================================================//
class TAS_ArchitectureSpec_c
{
public:

   TAS_ArchitectureSpec_c( void );
   TAS_ArchitectureSpec_c( const TAS_ArchitectureSpec_c& architectureSpec );
   ~TAS_ArchitectureSpec_c( void );

   TAS_ArchitectureSpec_c& operator=( const TAS_ArchitectureSpec_c& architectureSpec );
   bool operator==( const TAS_ArchitectureSpec_c& architectureSpec ) const;
   bool operator!=( const TAS_ArchitectureSpec_c& architectureSpec ) const;

   void Print( FILE* pfile = stdout, size_t spaceLen = 0 ) const;

   void PrintXML( void ) const;
   void PrintXML( FILE* pfile, size_t spaceLen = 0 ) const;

   bool InitDefaults( void );
   bool InitValidate( void );

   bool IsValid( void ) const;

private:

   void InitDefaultsConfig_( TAS_Config_c* pconfig ) const;
   bool InitDefaultsBlockHier_( void );
   bool InitDefaultsBlockHier_( TAS_PhysicalBlockList_t* pphysicalBlockList,
                                TAS_PhysicalBlock_c* pphysicalBlock );
   void InitDefaultsParentLinks_( TAS_PhysicalBlock_c* pphysicalBlock,
                                  const TAS_PhysicalBlock_c* pphysicalBlockParent,
                                  const TAS_Mode_c* pmodeParent ) const;
   void InitDefaultsParentLinks_( TAS_Mode_c* pmode,
                                  const TAS_PhysicalBlock_c* pphysicalBlockParent ) const;
   void InitDefaultsCellList_( TAS_CellList_t* pcellList ) const;

   bool InitValidateConfig_( void );
   bool InitValidatePhysicalBlockList_( TAS_PhysicalBlockList_t* pphysicalBlockList,
                                        const TAS_CellList_t& cellList,
                                        size_t hierarchyLevel = 0 ) const;
   bool InitValidatePhysicalBlock_( TAS_PhysicalBlock_c* pphysicalBlock,
                                    const TAS_CellList_t& cellList,
                                    size_t hierarchyLevel = 0 ) const;
   bool InitValidateModeList_( TAS_ModeList_t* pmodeList,
                               const TAS_CellList_t& cellList,
                               size_t hierarchyLevel = 0 ) const;
   bool InitValidateMode_( TAS_Mode_c* pmode,
                           const TAS_CellList_t& cellList,
                           size_t hierarchyLevel = 0 ) const;
   bool InitValidatePinAssignList_( const TAS_PinAssignList_t& pinAssignList,
                                    unsigned int height ) const;
   bool InitValidateGridAssignList_( const TAS_GridAssignList_t& gridAssignList ) const;
   bool InitValidateSegmentList_( const TAS_SegmentList_t& segmentList,
                                  const TAS_SwitchBoxSortedList_t& switchBoxSortedList ) const;
   bool InitValidateSegment_( const TAS_Segment_c& segment,
                              const TAS_SwitchBoxSortedList_t& switchBoxSortedList ) const;
   bool InitValidateCellList_( const TAS_CellList_t& cellList ) const;
   bool InitValidateCell_( const TAS_Cell_c& cell ) const;

   TAS_PhysicalBlock_c* FindPhysicalBlockHier_( const TAS_PhysicalBlockList_t& physicalBlockList,
                                                      const TAS_PhysicalBlock_c& physicalBlock ) const;

   bool HasPhysicalBlockUsage_( void ) const;

public:

   string srName;

   TAS_Config_c            config;
   TAS_PhysicalBlockList_t physicalBlockList;
   TAS_ModeList_t          modeList;
   TAS_SwitchBoxList_t     switchBoxList;
   TAS_SegmentList_t       segmentList;
   TAS_CarryChainList_t    carryChainList;
   TAS_CellList_t          cellList;

   class TAS_ArchitectureSpecSorted_c
   {
   public:

      TAS_PhysicalBlockSortedList_t physicalBlockList;
      TAS_ModeSortedList_t          modeList; 
      TAS_SwitchBoxSortedList_t     switchBoxList;
   } sorted;

private:

   enum TAS_DefCapacity_e 
   { 
      TAS_PHYSICAL_BLOCK_LIST_DEF_CAPACITY = 64,
      TAS_MODE_LIST_DEF_CAPACITY           = 8,
      TAS_SWITCH_BOX_LIST_DEF_CAPACITY     = 8,
      TAS_SEGMENT_LIST_DEF_CAPACITY        = 64,
      TAS_CARRY_CHAIN_LIST_DEF_CAPACITY    = 1,
      TAS_CELL_LIST_DEF_CAPACITY           = 16
   };
};

#endif
