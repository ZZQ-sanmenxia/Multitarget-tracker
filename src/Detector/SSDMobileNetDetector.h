#pragma once

#include "BaseDetector.h"

#include <opencv2/dnn.hpp>
#include <opencv2/dnn/shape_utils.hpp>

// MobileNet Single-Shot Detector (https://arxiv.org/abs/1704.04861) to detect objects
// .caffemodel model's file is available here:  https://github.com/chuanqi305/MobileNet-SSD
// Default network is 300x300 and 20-classes VOC

///
/// \brief The SSDMobileNetDetector class
///
class SSDMobileNetDetector : public BaseDetector
{
public:
    SSDMobileNetDetector(const cv::UMat& colorFrame);
    ~SSDMobileNetDetector(void);

    bool Init(const config_t& config);

    void Detect(const cv::UMat& colorFrame);

	bool CanGrayProcessing() const
	{
		return false;
	}

private:
    cv::dnn::Net m_net;

    void DetectInCrop(const cv::UMat& colorFrame, const cv::Rect& crop, regions_t& tmpRegions);

	cv::UMat m_inputBlob;

    static const int m_inWidth = 300;
    static const int m_inHeight = 300;

    float m_WHRatio = 1.f;
    float m_inScaleFactor = 0.007843f;
    float m_meanVal = 127.5;
    float m_confidenceThreshold = 0.5f;
    float m_maxCropRatio = 2.0f;
    std::vector<std::string> m_classNames;
};
