/*
    SPDX-FileCopyrightText: 2012 Jasem Mutlaq <mutlaqja@ikarustech.com>
    SPDX-FileCopyrightText: 2021 Wolfgang Reissenberger <sterne-jaeger@openfuture.de>

    SPDX-License-Identifier: GPL-2.0-or-later
 */

#pragma once

#include "ui_capturepreviewwidget.h"
#include "captureprocessoverlay.h"

#include "capture.h"
#include "sequencejob.h"
#include "fitsviewer/fitsdata.h"
#include "fitsviewer/summaryfitsview.h"
#include "ekos/scheduler/scheduler.h"

#include <QObject>
#include <QWidget>

class CapturePreviewWidget : public QWidget, public Ui::CapturePreviewWidget
{
    Q_OBJECT
public:
    explicit CapturePreviewWidget(QWidget *parent = nullptr);

    void shareCaptureProcess(Ekos::Capture *process);
    void shareSchedulerProcess(Ekos::Scheduler *process);
    void shareMountProcess(Ekos::Mount *process);

    /**
     * @brief display information about the currently running job
     * @param currently active job
     */
    void updateJobProgress(Ekos::SequenceJob *job, const QSharedPointer<FITSData> &data);

    /**
     * @brief Show the next frame from the capture history
     */
    void showNextFrame();

    /**
     * @brief Show the previous frame from the capture history
     */
    void showPreviousFrame();

    /**
     * @brief Delete the currently displayed frame
     */
    void deleteCurrentFrame();

    /**
     * @brief Set the summary FITS view
     */
    void setSummaryFITSView(SummaryFITSView *view);

    /**
     * @brief enable / disable display widgets
     */
    void setEnabled(bool enabled);

    /**
     * @brief reset display values
     */
    void reset();

signals:

public slots:
    /**
     * @brief update display when the capture status changes
     * @param status current capture status
     */
    void updateCaptureStatus(Ekos::CaptureState status);

    /**
     * @brief update the count down value of the current exposure
     * @param delta time difference
     */
    void updateCaptureCountDown(int delta);

private:
    Ekos::Scheduler *schedulerProcess = nullptr;
    Ekos::Capture *captureProcess = nullptr;
    Ekos::Mount *mountProcess = nullptr;

    // cache frame data
    CaptureProcessOverlay::FrameData m_currentFrame;

    // target the mount is pointing to (may be different to the scheduler job name)
    QString m_mountTarget = "";

    // summary FITS view
    SummaryFITSView *m_fitsPreview = nullptr;
    // FITS data overlay
    CaptureProcessOverlay *overlay = nullptr;
};
