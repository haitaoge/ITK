/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkVnlFFTComplexConjugateToRealImageFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkVnlFFTComplexConjugateToRealImageFilter_h
#define __itkVnlFFTComplexConjugateToRealImageFilter_h
#include "itkFFTComplexConjugateToRealImageFilter.h"

namespace itk
{

template <typename TPixel, unsigned int Dimension = 3>
class VnlFFTComplexConjugateToRealImageFilter :
    public FFTComplexConjugateToRealImageFilter<TPixel,Dimension>
{
public:
  /** Standard class typedefs.*/ 
  typedef Image< std::complex<TPixel>,Dimension> TInputImageType;
  typedef Image<TPixel,Dimension> TOutputImageType;

  typedef VnlFFTComplexConjugateToRealImageFilter Self;
  typedef FFTComplexConjugateToRealImageFilter<TPixel,Dimension> Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self> constPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(VnlFFTComplexConjugateToRealImageFilter,
               FFTComplexConjugateToRealImageFilter);

  /** Image type typedef support. */
  typedef TInputImageType ImageType;
  typedef typename ImageType::SizeType ImageSizeType;

  //
  // these should be defined in every FFT filter class
  virtual void GenerateData();  // generates output from input
protected:
  VnlFFTComplexConjugateToRealImageFilter()  { }
  virtual ~VnlFFTComplexConjugateToRealImageFilter(){ }
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  VnlFFTComplexConjugateToRealImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkVnlFFTComplexConjugateToRealImageFilter.txx"
#endif

#endif
