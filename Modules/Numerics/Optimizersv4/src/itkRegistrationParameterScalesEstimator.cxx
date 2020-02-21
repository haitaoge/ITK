/*=========================================================================
 *
 *  Copyright NumFOCUS
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
#include "itkRegistrationParameterScalesEstimator.h"

namespace itk
{
/** Print enum values */
std::ostream &
operator<<(std::ostream & out, const RegistrationParameterScalesEstimatorEnums::SamplingStrategy value)
{
  return out << [value] {
    switch (value)
    {
      case RegistrationParameterScalesEstimatorEnums::SamplingStrategy::FullDomainSampling:
        return "itk::RegistrationParameterScalesEstimatorEnums::SamplingStrategy::FullDomainSampling";
      case RegistrationParameterScalesEstimatorEnums::SamplingStrategy::CornerSampling:
        return "itk::RegistrationParameterScalesEstimatorEnums::SamplingStrategy::CornerSampling";
      case RegistrationParameterScalesEstimatorEnums::SamplingStrategy::RandomSampling:
        return "itk::RegistrationParameterScalesEstimatorEnums::SamplingStrategy::RandomSampling";
      case RegistrationParameterScalesEstimatorEnums::SamplingStrategy::CentralRegionSampling:
        return "itk::RegistrationParameterScalesEstimatorEnums::SamplingStrategy::CentralRegionSampling";
      case RegistrationParameterScalesEstimatorEnums::SamplingStrategy::VirtualDomainPointSetSampling:
        return "itk::RegistrationParameterScalesEstimatorEnums::SamplingStrategy::VirtualDomainPointSetSampling";
      default:
        return "INVALID VALUE FOR itk::RegistrationParameterScalesEstimatorEnums::SamplingStrategy";
    }
  }();
}
} // namespace itk
