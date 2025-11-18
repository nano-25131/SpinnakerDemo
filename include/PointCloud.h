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

#ifndef FLIR_SPINNAKER_POINTCLOUD_H
#define FLIR_SPINNAKER_POINTCLOUD_H

#include "Interface/IPointCloud.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "SpinnakerDefs.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /**@{*/

    /**
     *  @defgroup PointCloud_h Image Class
     */
    /**@{*/

    /**
     * @brief The PointCloud object class.
     */
    class SPINNAKER_API PointCloud : public IPointCloud
    {
      public:
        /** @brief Create an PointCloud object. */
        PointCloud();

        /** @brief Destroy the PointCloud object. */
        ~PointCloud();

        /**
         * Copy Constructor
         */  
        PointCloud(const PointCloud& other);

        /**
         * Assignment operator.
         */
        PointCloud& operator=(const PointCloud& otherPointCloud);

        /**
         * @brief Adds a point to the point cloud.
         *
         * @param[in] point The point to be added.
         */
        void AddPoint(const Stereo3DPoint point);

        /**
         * @brief Returns the Stereo3DPoint at the specified index
         *
         * @return Stereo3DPoint object
         */
        Stereo3DPoint GetPoint(const unsigned int index) const;

        /**
         * @brief Returns the number of points in the point cloud.
         *
         * @return The number of points in the point cloud.
         */
        size_t GetNumPoints() const;

        /**
         * The function writes the point cloud data to the specified file in PLY format.
         * The data is written in the order of x, y, z, color (red, green, blue, alpha), image x, image y.
         * The point cloud data is written as a binary file.
         *
         * @brief Saves the point cloud to a PLY file.
         *
         * @param[in] filename The path to the PLY file to be saved.
         *
         * @see LoadPointCloudFromPly()
         */
        void SavePointCloudAsPly(const std::string&) const;

        /**
         * The function reads the file and parses the data into a vector of 3D points.
         * The data is then stored in the class as a vector of Stereo3DPoint objects.
         *
         * @brief Loads a point cloud from a PLY file.
         *
         * @param[in] filename The path to the PLY file to be loaded.
         *
         * @see SavePointCloudAsPly()
         */
        void LoadPointCloudFromPly(const std::string& filename);

        /**
         * The function prints a number of points from the point cloud to the console.
         * The number of points to print is specified by the user. The points are
         * printed in the following format: x, y, z, r, g, b, i, j.
         *
         * @brief Prints a number of points from the point cloud to the console.
         *
         * @param[in] numPointsToPrint The number of points to print.
         */
        void PrintPoints(unsigned int numPointsToPrint) const;

      protected:
        friend class PointCloudImpl;

        PointCloudData* GetPointCloudData() const;

      private:
          PointCloudData* m_pPointCloudData;
    };
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_POINTCLOUD_H