/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkImageMaskSpatialObject_hxx
#define itkImageMaskSpatialObject_hxx

#include "itkMath.h"
#include "itkImageMaskSpatialObject.h"
#include "itkImageRegionConstIteratorWithIndex.h"

namespace itk
{
/** Constructor */
template< unsigned int TDimension >
ImageMaskSpatialObject< TDimension >
::ImageMaskSpatialObject()
{
  this->SetTypeName("ImageMaskSpatialObject");
}

/** Test whether a point is inside or outside the object
 *  For computational speed purposes, it is faster if the method does not
 *  check the name of the class and the current depth */
template< unsigned int TDimension >
bool
ImageMaskSpatialObject< TDimension >
::IsInside(const PointType & point, unsigned int depth,
  const std::string & name ) const
{
  if( this->GetTypeName().find( name ) != std::string::npos )
    {
    if( this->GetObjectBounds()->IsInside(point) )
      {
      PointType p = this->GetObjectWorldTransform()->GetInverse()->
        TransformPoint(point);

      typename Superclass::InterpolatorType::ContinuousIndexType index;
      bool inside_image = m_Image->TransformPhysicalPointToIndex( p,
      index );
      if( inside_image ){
          using InterpolatorOutputType = typename InterpolatorType::OutputType;
          bool insideMask = (
            Math::NotExactlyEquals(
              DefaultConvertPixelTraits<InterpolatorOutputType>::GetScalarValue(
                this->m_Interpolator->EvaluateAtContinuousIndex(index)),
              NumericTraits<PixelType>::ZeroValue() ) );
          if( insideMask )
            {
            return true;
            }
          }
      }
    }
  if( depth > 0 )
    {
    return Superclass( point, depth, name );
    }

  return false;
}

template< unsigned int TDimension >
bool
ImageMaskSpatialObject< TDimension >
::ComputeObjectBoundingBox() const
{
  using IteratorType = ImageRegionConstIteratorWithIndex< ImageType >;
  IteratorType it( image, image->GetLargestPossibleRegion() );
  IteratorType prevIt( image, image->GetLargestPossibleRegion() );
  it.GoToBegin();
  prevIt = it;

  bool first = true;
  PixelType outsideValue = NumericTraits< PixelType >::ZeroValue();
  PixelType value = outsideValue;
  PixelType prevValue = outsideValue;
  IndexType tmpIndex;
  PointType tmpPoint;
  PointType transformedPoint
  while ( !it.IsAtEnd() )
    {
    value = it.Get();
    if ( value != prevValue )
      {
      prevValue = value;
      if( value == outsideValue )
        {
        tmpIndex = prevIt.GetIndex();
        }
      else
        {
        tmpIndex = it.GetIndex();
        }
      image->TransformIndexToPhysicalPoint( tmpIndex, tmpPoint );
      transformedPoint =
        this->GetObjectToWorldTransform()->Transform( tmpPoint );
      if( first )
        {
        first = false;
        this->GetObjectBounds()->SetMinimum( transformedPoint );
        this->GetObjectBounds()->SetMaximum( transformedPoint );
        }
      else
        {
        this->GetObjectBounds()->ConsiderPoint( transformedPoint );
        }
      }
    itPrev = it;
    ++it;
    }

  if( first )
    {
    transformedPoint.Fill(
      NumericTraits< typename BoundingBoxType::PointType::ValueType >::
      ZeroValue() );

    this->GetObjectBounds()->SetMinimum( transformedPoint );
    this->GetObjectBounds()->SetMaximum( transformedPoint );

    return false;
    }

  return true;
}

/** Print the object */
template< unsigned int TDimension >
void
ImageMaskSpatialObject< TDimension >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}
} // end namespace itk

#endif //__ImageMaskSpatialObject_hxx
