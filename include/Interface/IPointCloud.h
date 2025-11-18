//=============================================================================
// Copyright (c) 2025 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#ifndef FLIR_SPINNAKER_IPOINTCLOUD_H
#define FLIR_SPINNAKER_IPOINTCLOUD_H

#include "SpinnakerDefs.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */

    /**@{*/

    /**
     *  @defgroup IPointCloud_h Point Cloud Class
     */

    /**@{*/

    /**
     * @brief The interface file for PointCloud class.
     */
    class SPINNAKER_API IPointCloud
    {
      public:
        virtual ~IPointCloud(void){};

        struct PointCloudData; // Forward declaration
        virtual IPointCloud::PointCloudData* GetPointCloudData() const = 0;
        virtual void AddPoint(const Stereo3DPoint point) = 0;
        virtual Stereo3DPoint GetPoint(const unsigned int index) const = 0;
        virtual size_t GetNumPoints() const = 0;
        virtual void SavePointCloudAsPly(const std::string&) const = 0;
        virtual void LoadPointCloudFromPly(const std::string& filename) = 0;
        virtual void PrintPoints(unsigned int numPointsToPrint) const = 0;

      protected:
        friend class PointCloud;
        friend class PointCloudImpl;
        IPointCloud::PointCloudData* m_pPointCloudData;

        IPointCloud(){};
        IPointCloud(const IPointCloud&){};
        IPointCloud& operator=(const IPointCloud&);
    };

    /**@}*/

    /**@}*/

} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IPOINTCLOUD_H