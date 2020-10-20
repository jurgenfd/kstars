/***************************************************************************
                          fitssepdetector.h  -  FITS Image
                             -------------------
    begin                : Sun March 29 2020
    copyright            : (C) 2004 by Jasem Mutlaq, (C) 2020 by Eric Dejouhanet
    email                : eric.dejouhanet@gmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   Some code fragments were adapted from Peter Kirchgessner's FITS plugin*
 *   See http://members.aol.com/pkirchg for more details.                  *
 ***************************************************************************/

#pragma once

#include "fitsstardetector.h"
#include "skybackground.h"

class FITSSEPDetector : public FITSStarDetector
{
        Q_OBJECT

    public:
        explicit FITSSEPDetector(FITSData *parent): FITSStarDetector(parent) {};

        /** @brief Find sources in the parent FITS data file.
         * @see FITSStarDetector::findSources().
         */
        QFuture<bool> findSources(QRect const &boundary = QRect()) override;

        /** @brief Find sources in the parent FITS data file as well as background sky information.
         */
        bool findSourcesAndBackground(QRect const &boundary = QRect());

        /** @brief Configure the detection method.
         * @see FITSStarDetector::configure().
         * @note No parameters are currently available for configuration.
         * @todo Provide parameters for detection configuration.
         */
        void configure(const QString &setting, const QVariant &value) override;

    protected:
        /** @internal Consolidate a float data buffer from FITS data.
         * @param buffer is the destination float block.
         * @param x, y, w, h define a (x,y)-(x+w,y+h) sub-frame to extract from the FITS data out to block 'buffer'.
         * @param image_data is the FITS data block to extract from.
         */
        template <typename T>
        void getFloatBuffer(float * buffer, int x, int y, int w, int h, FITSData const * image_data) const;

    private:

        void clearSolver();

        int numStars = 100;
        double fractionRemoved = 0.2;
        int deblendNThresh = 32;
        double deblendMincont = 0.005;
        bool radiusIsBoundary = true;
};

