//===========================================================================//
// Purpose : Declaration and inline definitions for a TFV_FabricView class.
//
//           Inline methods include:
//           - GetName
//           - GetRegion
//           - GetPolygon
//           - GetLayerRange
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

#ifndef TFV_FABRIC_VIEW_H
#define TFV_FABRIC_VIEW_H

#include <cstdio>
#include <string>
using namespace std;

#include "TGS_Typedefs.h"
#include "TGS_Box.h"
#include "TGS_Rect.h"
#include "TGS_Region.h"

#include "TGO_Polygon.h"

#include "TFV_Typedefs.h"
#include "TFV_FabricLayer.h"

//===========================================================================//
// Purpose        : Class declaration
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 08/15/12 jeffr : Original
//===========================================================================//
class TFV_FabricView_c 
{
public:

   TFV_FabricView_c( void );
   TFV_FabricView_c( const string& srName,
                     const TGS_Region_c& region,
                     const TGO_Polygon_c* ppolygon = 0 );
   TFV_FabricView_c( const char* pszName,
                     const TGS_Region_c& region,
                     const TGO_Polygon_c* ppolygon = 0 );
   TFV_FabricView_c( const TGS_Region_c& region,
                     const TGO_Polygon_c* ppolygon = 0 );
   TFV_FabricView_c( const TFV_FabricView_c& fabricView );
   ~TFV_FabricView_c( void );

   TFV_FabricView_c& operator=( const TFV_FabricView_c& fabricView );
   bool operator==( const TFV_FabricView_c& fabricView ) const;
   bool operator!=( const TFV_FabricView_c& fabricView ) const;

   void Print( FILE* pfile = stdout, size_t spaceLen = 0 ) const;

   const char* GetName( void ) const;
   const TGS_Region_c& GetRegion( void ) const;
   const TGO_Polygon_c& GetPolygon( void ) const;
   const TGS_LayerRange_t& GetLayerRange( void ) const;

   bool Init( const string& srName,
              const TGS_Region_c& region,
              const TGO_Polygon_c* ppolygon = 0 );
   bool Init( const char* pszName,
              const TGS_Region_c& region,
              const TGO_Polygon_c* ppolygon = 0 );
   bool Init( const TGS_Region_c& region,
              const TGO_Polygon_c* ppolygon = 0 );
   bool Init( const TFV_FabricView_c& fabricView );

   void Clear( void );

   bool Add( TGS_Layer_t layer,
             const TGS_Region_c& region,
             TFV_AddMode_t addMode = TFV_ADD_MERGE );
   bool Add( const TGS_Rect_c& rect,
             TFV_AddMode_t addMode = TFV_ADD_MERGE );
   bool Add( TGS_Layer_t layer,
             const TGS_Region_c& region,
             const TFV_FabricData_c& fabricData,
             TFV_AddMode_t addMode = TFV_ADD_MERGE );
   bool Add( const TGS_Rect_c& rect,
             const TFV_FabricData_c& fabricData,
             TFV_AddMode_t addMode = TFV_ADD_MERGE );
   bool Add( TGS_Layer_t layer,
             const TFV_FabricFigure_t& fabricFigure,
             TFV_AddMode_t addMode = TFV_ADD_MERGE );
   bool Add( const TFV_FabricView_c& fabricView );

   bool Delete( TGS_Layer_t layer,
                const TGS_Region_c& region,
                TFV_DeleteMode_t deleteMode = TFV_DELETE_INTERSECT );
   bool Delete( const TGS_Rect_c& rect,
                TFV_DeleteMode_t deleteMode = TFV_DELETE_INTERSECT );
   bool Delete( TGS_Layer_t layer,
                const TGS_Region_c& region,
                const TFV_FabricData_c& fabricData,
                TFV_DeleteMode_t deleteMode = TFV_DELETE_INTERSECT );
   bool Delete( const TGS_Rect_c& rect,
                const TFV_FabricData_c& fabricData,
                TFV_DeleteMode_t deleteMode = TFV_DELETE_INTERSECT );
   bool Delete( TGS_Layer_t layer,
                const TFV_FabricFigure_t& fabricFigure,
                TFV_DeleteMode_t deleteMode = TFV_DELETE_INTERSECT );

   bool Find( TGS_Layer_t layer,
              const TGS_Region_c& region,
              TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool Find( const TGS_Rect_c& rect,
              TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool Find( TGS_Layer_t layer,
              const TGS_Point_c& point,
              TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool Find( const TGS_Point_c& point,
              TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool Find( TGS_Layer_t layer,
              const TGS_Region_c& region,
              TFV_FindMode_t findMode,
              TFV_FigureMode_t figureMode,
              TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool Find( const TGS_Rect_c& rect,
              TFV_FindMode_t findMode,
              TFV_FigureMode_t figureMode,
              TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool Find( TGS_Layer_t layer,
              const TGS_Region_c& region,
              TFV_FabricData_c** ppfabricData = 0 ) const;
   bool Find( const TGS_Rect_c& rect,
              TFV_FabricData_c** ppfabricData = 0 ) const;
   bool Find( TGS_Layer_t layer,
              const TGS_Point_c& point,
              TFV_FabricData_c** ppfabricData = 0 ) const;
   bool Find( TGS_Layer_t layer,
              const TGS_Region_c& region,
              TFV_FindMode_t findMode,
              TFV_FigureMode_t figureMode,
              TFV_FabricData_c** ppfabricData = 0 ) const;
   bool Find( const TGS_Rect_c& rect,
              TFV_FindMode_t findMode,
              TFV_FigureMode_t figureMode,
              TFV_FabricData_c** ppfabricData = 0 ) const;
   bool Find( TGS_Layer_t layer,
              const TGS_Point_c& point,
              TFV_FindMode_t findMode,
              TFV_FigureMode_t figureMode,
              TFV_FabricData_c** ppfabricData = 0 ) const;
   bool Find( TGS_Layer_t layer,
              TFV_FabricLayer_c** ppfabricLayer = 0 ) const;

   bool FindConnected( TGS_Layer_t layer,
                       const TGS_Region_c& region,
                       TGS_RectList_t* prectList ) const;
   bool FindConnected( const TGS_Rect_c& rect,
                       TGS_RectList_t* prectList ) const;

   bool FindNearest( TGS_Layer_t layer,
                     const TGS_Region_c& region,
                     TGS_Region_c* pfoundRegion,
                     double maxDistance = TC_FLT_MAX ) const;
   bool FindNearest( TGS_Layer_t layer,
                     const TGS_Region_c& region,
                     TGS_Rect_c* pfoundRect,
                     double maxDistance = TC_FLT_MAX ) const;
   bool FindNearest( const TGS_Rect_c& rect,
                     TGS_Rect_c* pfoundRect,
                     double maxDistance = TC_FLT_MAX ) const;
   bool FindNearest( TGS_Layer_t layer,
                     const TGS_Point_c& point,
                     TGS_Region_c* pfoundRegion,
                     double maxDistance = TC_FLT_MAX ) const;
   bool FindNearest( TGS_Layer_t layer,
                     const TGS_Point_c& point,
                     TGS_Rect_c* pfoundRect,
                     double maxDistance = TC_FLT_MAX ) const;
   bool FindNearest( TGS_Layer_t layer,
                     const TGS_Region_c& region,
                     TC_SideMode_t sideMode,
                     TGS_Region_c* pfoundRegion ) const;
   bool FindNearest( TGS_Layer_t layer,
                     const TGS_Region_c& region,
                     TC_SideMode_t sideMode,
                     TGS_Rect_c* pfoundRect ) const;
   bool FindNearest( const TGS_Rect_c& rect,
                     TC_SideMode_t sideMode,
                     TGS_Rect_c* pfoundRect ) const;

   TFV_FabricLayer_c* FindFabricLayer( TGS_Layer_t layer ) const;
   const TFV_FabricPlane_c* FindFabricPlane( TGS_Layer_t layer ) const;
   const TGS_Box_c& FindFabricBox( void ) const;

   bool ApplyIntersect( const TGS_Box_c& box );
   bool ApplyIntersect( const TGS_Rect_c& rect );
   bool ApplyIntersect( const TGS_Region_c& region );
  
   bool IsClear( TGS_Layer_t layer,
                 const TGS_Point_c& point ) const;
   bool IsClearAny( TGS_Layer_t layer,
                    const TGS_Region_c& region ) const;
   bool IsClearAny( const TGS_Rect_c& rect ) const;
   bool IsClearAll( TGS_Layer_t layer,
                    const TGS_Region_c& region ) const;
   bool IsClearAll( const TGS_Rect_c& rect ) const;

   bool IsSolid( TGS_Layer_t layer,
                 const TGS_Point_c& point,
                 TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool IsSolidAny( TGS_Layer_t layer,
                    const TGS_Region_c& region,
                    TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool IsSolidAny( const TGS_Rect_c& rect,
                    TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool IsSolidAll( TGS_Layer_t layer,
                    const TGS_Region_c& region,
                    TFV_FabricFigure_t** ppfabricFigure = 0 ) const;
   bool IsSolidAll( const TGS_Rect_c& rect,
                    TFV_FabricFigure_t** ppfabricFigure = 0 ) const;

   bool IsWithin( TGS_Layer_t layer ) const;
   bool IsWithin( const TGS_Point_c& point ) const;
   bool IsWithin( TGS_Layer_t layer,
                  const TGS_Point_c& point ) const;
   bool IsWithin( TGS_Layer_t layer,
                  const TGS_Region_c& region ) const;
   bool IsWithin( const TGS_Rect_c& rect ) const;
   bool IsWithin( const TGS_Box_c& box ) const;

   bool IsIntersecting( TGS_Layer_t layer,
                        const TGS_Region_c& region ) const;
   bool IsIntersecting( const TGS_Rect_c& rect ) const;

   bool IsValid( void ) const;

private:

   TFV_FabricLayerList_t* Allocate_( const TGS_Region_c& region,
                                     const TGS_LayerRange_t& layerRange );
   void Deallocate_( TFV_FabricLayerList_t* pfabricLayerList );

private:

   string           srName_; // Define name asso. with this fabric view
   TGS_Region_c     region_; // Define region dims asso. with this fabric view
   TGO_Polygon_c    polygon_;// Optional polygon asso. with this fabric view
   TGS_LayerRange_t layerRange_; 
                             // Define layer range asso. with this fabric view

   TFV_FabricLayerList_t* pfabricLayerList_;
                             // Ptr to allocated 3D layer list for fabric view
   TGS_Box_c fabricBox_;     // Local cached copy of 3D box for fabric view
};

//===========================================================================//
// Purpose        : Class inline definition(s)
// Author         : Jeff Rudolph
//---------------------------------------------------------------------------//
// Version history
// 08/15/12 jeffr : Original
//===========================================================================//
inline const char* TFV_FabricView_c::GetName( 
      void ) const
{
   return( this->srName_.length( ) ? this->srName_.data( ) : 0 );
}

//===========================================================================//
inline const TGS_Region_c& TFV_FabricView_c::GetRegion( 
      void ) const
{
   return( this->region_ );
}

//===========================================================================//
inline const TGO_Polygon_c& TFV_FabricView_c::GetPolygon( 
      void ) const
{
   return( this->polygon_ );
}

//===========================================================================//
inline const TGS_LayerRange_t& TFV_FabricView_c::GetLayerRange( 
      void ) const
{
   return( this->layerRange_ );
}

#endif
