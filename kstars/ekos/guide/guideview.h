/*  Ekos GuideView
 *  Child of FITSView with few additions necessary for Internal Guider

    Copyright (C) 2020 Hy Murveit

    This application is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 */

#pragma once

#include "fitsviewer/fitsview.h"

#include <QList>

class QPainter;

/**
 * The main change relative to fitsview is to add the capability of displaying
 * the 'neighbor guide stars' for the SEP Multi Star guide algorithm.
 */
class GuideView : public FITSView
{
        Q_OBJECT
    public:
        explicit GuideView(QWidget *parent = nullptr, FITSMode mode = FITS_NORMAL, FITSScale filter = FITS_NONE);

        // Calls the parent drawOverlay, then draws circles around the guide-star
        // neighbors and lines between the guide star and the neighbors.
        void drawOverlay(QPainter *, double scale) override;

        // Adds a neighbor at x,y. Set found to true if the neighbor was associated
        // with a detected star.
        void addGuideStarNeighbor(double x, double y, bool found);

        // Remove all the neighbors.
        void clearNeighbors();

    protected:

    private:
        struct Neighbor
        {
            // x and y input-image coordinates for the potential guide star neighbors.
            double x;
            double y;
            // Was the neighbor at this location was associated with a detected star.
            bool found;
        };

        void drawNeighbor(QPainter *painter, const Neighbor &neighbor);
        QList<Neighbor> neighbors;
    signals:
};
