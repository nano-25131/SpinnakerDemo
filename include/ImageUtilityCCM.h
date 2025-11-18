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

#ifndef FLIR_SPINNAKER_IMAGE_UTILITY_CCM_H
#define FLIR_SPINNAKER_IMAGE_UTILITY_CCM_H

#include "SpinnakerPlatform.h"
#include "SpinnakerDefs.h"

namespace Spinnaker
{
    class ImagePtr;

    /**
     *  @defgroup SpinnakerClasses Spinnaker Classes
     */
    /**@{*/

    /**
     *  @defgroup ImageUtilityCCM_h Image Utility CCM Class
     */
    /**@{*/

    /**
     * @brief Static function to create color corrected images from an image object
     */

    class SPINNAKER_API ImageUtilityCCM
    {
      public:
        /**
         * Create a color corrected image from the source image by applying
         * a color correction matrix calibrated according to the settings specified.
         * When using ImageUtilityCCM, users are advised to disable CCM on the camera before
         * capturing source images. This can be done through the camera node "ColorTransformationEnable".
         *
         * Color correction is currently supported for the following pixel formats:
         * - PixelFormat_BGR8
         * - PixelFormat_BGRa8
         * - PixelFormat_RGBa8
         * - PixelFormat_RGB8
         * - PixelFormat_BGR16
         * - PixelFormat_BGRa16
         * - PixelFormat_RGBa16
         * - PixelFormat_RGB16
         * The output image will have the same pixel format as the source image.
         *
         * @param srcImage The source image to which the CCM is applied
         * @param settings Selected CCM settings including CCMColorTemperature, CCMType, CCMSensor, etc
         *
         * @return The color corrected image
         *
         * @see CCMSettings
         */
        static ImagePtr CreateColorCorrected(const ImagePtr& srcImage, const CCMSettings& settings);

        /**
         * Create a color corrected image from the source image by applying
         * a color correction matrix calibrated according to the settings specified.
         * When using ImageUtilityCCM, users are advised to disable CCM on the camera before
         * capturing source images. This can be done through the camera node "ColorTransformationEnable".
         *
         * Color correction is currently supported for the following pixel formats:
         * - PixelFormat_BGR8
         * - PixelFormat_BGRa8
         * - PixelFormat_RGBa8
         * - PixelFormat_RGB8
         * - PixelFormat_BGR16
         * - PixelFormat_BGRa16
         * - PixelFormat_RGBa16
         * - PixelFormat_RGB16
         *
         * The destination image height and width must be the same as the source image.
         *
         * @param srcImage The source image to which the CCM is applied
         * @param destImage The destination image in which to store the color corrected image
         * @param settings Selected CCM settings including CCMColorTemperature, CCMType, CCMSensor, etc
         *
         * @see CCMSettings
         */
        static void CreateColorCorrected(const ImagePtr& srcImage, ImagePtr& destImage, const CCMSettings& settings);

        /**
         * Returns an encrypted custom CCM string based on the input comma separated matrix 
         * entries string. The matrix can be of either 3x3 Linear CCM or 9x3 Advanced CCM type.
         * The custom code can be set in the CCMSettings to create a custom color corrected image
         * that is not available in the existing preset temperature/application type.
         *
         * @param ccmMatrixEntries String that contains comma separted CCM matrix entries
         *
         * @see CCMSettings
         * @see CreateColorCorrected
         * 
         * @return std::string Encrypted custom CCM code
         */
        static std::string EncryptColorCorrectionMatrix(std::string ccmMatrixEntries);

        /**
         * Fetch the CCM setting color temperature  enum and return as a string.
         *
         * @param colorTemperature The CMM setting color temperature enum
         *
         * @return The CCM color temperature as a string
         *
         * @see CCMSettings
         */
        static std::string ColorTemperatureToString(const CCMColorTemperature& colorTemperature);

         /**
         * Fetch the CCM setting type enum and return as a string.
         *
         * @param type The CMM setting type enum
         *
         * @return The CCM type as a string
         *
         * @see CCMSettings
         */
        static std::string TypeToString(const CCMType& type);

         /**
         * Fetch the CCM setting sensor enum and return as a string.
         *
         * @param sensor The CMM setting sensor enum
         *
         * @return The CCM sensor as a string
         *
         * @see CCMSettings
         */
        static std::string SensorToString(const CCMSensor& sensor);

         /**
         * Fetch the CCM setting color space enum and return as a string.
         *
         * @param colorSpace The CMM setting color space enum
         *
         * @return The CCM color space as a string
         *
         * @see CCMSettings
         */
        static std::string ColorSpaceToString(const CCMColorSpace& colorSpace);

         /**
         * Fetch the CMM setting application enum and return as a string.
         *
         * @param application The CMM setting application enum
         *
         * @return The CMM application as a string
         *
         * @see CCMSettings
         */
        static std::string ApplicationToString(const CCMApplication& application);
    };

    /**@}*/

    /**@}*/
} // namespace Spinnaker

#endif // FLIR_SPINNAKER_IMAGE_UTILITY_CCM_H