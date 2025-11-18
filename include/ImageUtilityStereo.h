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

#ifndef FLIR_SPINNAKER_IMAGE_UTILITY_STEREO_H
#define FLIR_SPINNAKER_IMAGE_UTILITY_STEREO_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"
#include "PointCloud.h"
#include "CameraDefs.h"
#include "Image.h"
#include "ImagePtr.h"
#include "CameraPtr.h"

namespace Spinnaker
{
    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /**@{*/

    /**
     *  @defgroup ImageUtilityStereo_h Image Utility Stereo Class
     */
    /**@{*/

    /**
     * @brief Static helper functions for stereo related computations.
     */

    class SPINNAKER_API ImageUtilityStereo
    {
      public:
        /**
         * Returns true if the camera is a stereo camera or false otherwise.
         *
         * @param pCamera The camera
         *
         * @return True if the camera is stereo camera, or false otherwise
         */
        static bool IsStereoCamera(CameraPtr pCamera);

        /**
         * Filters speckles from a copy of the input mono disparity image. Note that
         * only Mono16 pixel format image is supported.
         *
         * @param disparityImage The disparity image
         * @param maxSpeckleSize The maximum allowed speckle size
         * @param speckleThreshold The speckle size threshold
         * @param disparityScaleFactor The coordinate scale factor
         * @param invalidDataValue The value assigned to invalid data
         *
         * @return Speckle filtered image
         */
        static ImagePtr FilterSpeckles(
            const ImagePtr& disparityImage,
            const int maxSpeckleSize,
            const int speckleThreshold,
            const float disparityScaleFactor,
            const float invalidDataValue);

        /**
         * Filters speckles in-place on the input mono disparity image. Note that
         * only Mono16 pixel format image is supported.
         *
         * @param disparityImage The disparity image
         * @param maxSpeckleSize The maximum allowed speckle size
         * @param speckleThreshold The speckle size threshold
         * @param disparityScaleFactor The coordinate scale factor
         * @param invalidDataValue The value assigned to invalid data
         */
        static void FilterSpecklesFromImage(
            ImagePtr& disparityImage,
            const int maxSpeckleSize,
            const int speckleThreshold,
            const float disparityScaleFactor,
            const float invalidDataValue);

        /**
         * Computes 3D point from disparity value.
         *
         * @param disparity The disparity value
         * @param stereoCameraParameters The parameters for the stereo camera
         * @param stereo3DPoint The computed 3D point
         *
         * @see StereoCameraParameters
         *
         * @return True if the function finished successfully, or false otherwise
         */
        static bool Compute3DPointFromPixel(
            const uint16_t disparity,
            const StereoCameraParameters& stereoCameraParameters,
            Stereo3DPoint& stereo3DPoint);

        /**
         * Computes 3D point cloud from a stereo pair consisting of a disparity/rectified
         * image using a stereo matching algorithm.
         *
         * @param disparityImage The disparity image from a stereo pair consisting of a
         *                       disparity/rectified image.
         * @param rectifiedImage The rectified image from a stereo pair consisting of a
         *                       disparity/rectified image.
         * @param pointCloudParameters The parameters for computing the point cloud
         * @param stereoCameraParameters The parameters for the stereo camera
         *
         * @see StereoCameraParameters
         * @see PointCloudParameters
         *
         * @return A PointCloud object containing the computed point cloud
         */
        static PointCloud ComputePointCloud(
            const ImagePtr& disparityImage,
            const ImagePtr& rectifiedImage,
            const PointCloudParameters& pointCloudParameters,
            const StereoCameraParameters& stereoCameraParameters);

        /**
         * Computes 3D point cloud from a stereo pair consisting of a disparity/rectified
         * image using a stereo matching algorithm.
         *
         * @param disparityImage The disparity image from a stereo pair consisting of a 
         *                       disparity/rectified image.
         * @param rectifiedImage The rectified image from a stereo pair consisting of a
         *                       disparity/rectified image.
         * @param pointCloudParameters The parameters for computing the point cloud
         * @param stereoCameraParameters The parameters for the stereo camera
         * @param pointCloud The computed point cloud will be stored in this object
         *
         * @see StereoCameraParameters
         * @see PointCloudParameters
         */
        static void ComputePointCloud(
            const ImagePtr& disparityImage,
            const ImagePtr& rectifiedImage,
            const PointCloudParameters& pointCloudParameters,
            const StereoCameraParameters& stereoCameraParameters,
            PointCloud& pointCloud);

        /**
         * Computes the distance of a point to the camera world coordinates origin,
         * from the disparity image.
         *
         * @param disparityImage The disparity image
         * @param stereoParam The stereo camera parameters
         * @param imagePixel The pixel in the image
         * @param distance The distance of the point to the camera world coordinates origin
         *
         * @return True if the function finished successfully, or false otherwise.
         */
        static bool ComputeDistanceToPoint(
            const ImagePtr& disparityImage,
            const StereoCameraParameters& stereoParam,
            const ImagePixel& imagePixel,
            float& distance);

        /**
         * Computes the distance between two points in the disparity image.
         *
         * @param disparityImage The disparity image
         * @param stereoParam The stereo camera parameters
         * @param imagePixel1 The first pixel in the image
         * @param imagePixel2 The second pixel in the image
         * @param distance The distance between the two points
         *
         * @return True if the function finished successfully, or false otherwise
         */
        static bool ComputeDistanceBetweenPoints(
            const ImagePtr& disparityImage,
            const StereoCameraParameters& stereoParam,
            const ImagePixel& imagePixel1,
            const ImagePixel& ImagePixel2,
            float& distance);

        /**
         * Computes a depth image.
         * A depth image reinterprets disparity data by mapping the disparity for each
         * pixel to a depth (z) value based on the image focal length and baseline.
         * The source image is required to carry disparity information.
         *
         * @param disparityImage The source image from which to create the depth values
         * @param invalidDepthVal value to mark invalid pixels, where the depth should not be computed for
         * @param minDepthVal The actual minimum depth in the image
         * @param maxDepthVal The actual maximum depth in the image
         *
         * @return The depth image
         */
        static ImagePtr CreateDepthImage(
            const ImagePtr& disparityImage,
            const StereoCameraParameters& stereoCameraParameters,
            const uint16_t invalidDepthVal,
            float& minDepthVal,
            float& maxDepthVal);

        /**
         * Computes a depth image.
         * A depth image reinterprets disparity data by mapping the disparity for each
         * pixel to a depth (z) value based on the image focal length and baseline.
         * The source image is required to carry disparity information.
         * The destination is required to be initialized with Mono16 pixel format,
         * and have the same width, height, x offset, and y offset as the source image.
         *
         * @param disparityImage The source image from which to create the depth values
         * @param stereoCameraParameters The stereo camera parameters
         * @param invalidDepthVal value to mark invalid pixels, where the depth should not be computed for
         * @param depthImage The destination image in which to store the created depth values
         * @param minDepthVal The actual minimum depth in the image
         * @param maxDepthVal The actual maximum depth in the image
         */
        static void CreateDepthImage(
            const ImagePtr& disparityImage,
            const StereoCameraParameters& stereoCameraParameters,
            const uint16_t invalidDepthVal,
            ImagePtr& depthImage,
            float& minDepthVal,
            float& maxDepthVal);

        static uint16_t maxDepthThresholdInMm;
        static uint16_t maxDepthThresholdInMeter;
    };

    /**@}*/

    /**@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IMAGE_UTILITY_STEREO_H