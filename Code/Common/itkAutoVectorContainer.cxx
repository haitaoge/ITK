/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkAutoVectorContainer.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) 2000 National Library of Medicine
  All rights reserved.

  See COPYRIGHT.txt for copyright details.

=========================================================================*/
// #include "itkAutoVectorContainer.h"


/**
 *
 */
template <typename TElementIdentifier, typename TElement>
itkAutoVectorContainer< TElementIdentifier , TElement >::Pointer
itkAutoVectorContainer< TElementIdentifier , TElement >
::New(void)
{
  return new Self;
}
  

/**
 * This is an "auto" vector, so the underlying STL vector may need to be
 * expanded to allow the given index to be valid.
 *
 * Once it is known that the index exists, just pass the indexing operator
 * through to the STL vector's version.
 */
template <typename TElementIdentifier, typename TElement>
itkAutoVectorContainer< TElementIdentifier , TElement >::Element&
itkAutoVectorContainer< TElementIdentifier , TElement >
::operator[](ElementIdentifier id)
{
  if(id >= this->Vector::size())
    {
    /**
     * The vector must be expanded.  If doubling in size is enough to
     * allow the new index, do so.  Otherwise, expand just enough to
     * allow the new index.
     */
    if((id+1) < (2*this->Vector::size()))
      this->Vector::resize(2*this->Vector::size());
    else
      this->Vector::resize(id+1);
    }
  
  return this->Vector::operator[](id);
}
  

/**
 * Check if the index range of the STL vector is large enough to allow the
 * given index without expansion.
 */
template <typename TElementIdentifier, typename TElement>
bool
itkAutoVectorContainer< TElementIdentifier , TElement >
::IndexExists(ElementIdentifier id)
{
  return ((id >= 0) && (id < this->Vector::size()));
}


/**
 * Make sure that the index range of the STL vector is large enough to allow
 * the given index, expanding it if necessary.  The index will contain
 * the default element regardless of whether expansion occured.
 */
template <typename TElementIdentifier, typename TElement>
void
itkAutoVectorContainer< TElementIdentifier , TElement >
::CreateIndex(ElementIdentifier id)
{
  if(id >= this->Vector::size())
    {
    /**
     * The vector must be expanded.  If doubling in size is enough to
     * allow the new index, do so.  Otherwise, expand just enough to
     * allow the new index.
     */
    if((id+1) < (2*this->Vector::size()))
      this->Vector::resize(2*this->Vector::size());
    else
      this->Vector::resize(id+1);
    }
  else if(id >= 0)
    {
    /**
     * No expansion was necessary.  Just overwrite the index's entry with
     * the default element.
     */
    this->Vector::operator[](id) = Element();
    }
}


/**
 * It doesn't make sense to delete a vector index.
 * Instead, just overwrite the index with the default element.
 */
template <typename TElementIdentifier, typename TElement>
void
itkAutoVectorContainer< TElementIdentifier , TElement >
::DeleteIndex(ElementIdentifier id)
{
  this->Vector::operator[](id) = Element();
}
