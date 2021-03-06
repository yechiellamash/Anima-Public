#pragma once
#include <cmath>

#include <itkImage.h>
#include <itkMultiResolutionPyramidImageFilter.h>
#include <animaAxisRotationTransform.h>
#include <itkAffineTransform.h>
#include <itkProcessObject.h>

enum Metric
{
    MutualInformation = 0,
    NormalizedMutualInformation,
    MeanSquares
};

namespace anima
{

template <typename ScalarType = double>
class PyramidalSymmetryConstrainedRegistrationBridge : public itk::ProcessObject
{
public:
    typedef itk::Image <float,3> InputImageType;
    typedef typename InputImageType::Pointer InputImagePointer;
    typedef typename InputImageType::RegionType InputImageRegionType;

    typedef anima::AxisRotationTransform<ScalarType> TransformType;
    typedef typename TransformType::Pointer TransformPointer;
    typedef typename TransformType::ParametersType ParametersType;
    typedef typename TransformType::MatrixType MatrixType;
    typedef typename TransformType::OffsetType OffsetType;

    typedef itk::AffineTransform<ScalarType,3> BaseTransformType;
    typedef typename BaseTransformType::Pointer BaseTransformPointer;

    typedef itk::MultiResolutionPyramidImageFilter <InputImageType,InputImageType> PyramidType;
    typedef typename PyramidType::Pointer PyramidPointer;

    /** SmartPointer typedef support  */
    typedef PyramidalSymmetryConstrainedRegistrationBridge Self;
    typedef itk::ProcessObject Superclass;

    typedef itk::SmartPointer<Self> Pointer;
    typedef itk::SmartPointer<const Self> ConstPointer;

    itkNewMacro(Self)

    itkTypeMacro(PyramidalSymmetryConstrainedRegistrationBridge,itk::ProcessObject)

    void Update() ITK_OVERRIDE;

    void WriteOutputs();

    /**
    * Setter for images
    * */
    void SetReferenceImage(InputImagePointer referenceImage) {m_ReferenceImage = referenceImage;}
    void SetFloatingImage(InputImagePointer floatingImage) {m_FloatingImage = floatingImage;}

    std::string GetResultFile() {return m_resultFile;}
    void SetResultFile(std::string resultFile) {m_resultFile=resultFile;}

    std::string GetOutputTransformFile() {return m_outputTransformFile;}
    void SetOutputTransformFile(std::string outputTransformFile) {m_outputTransformFile=outputTransformFile;}

    Metric GetMetric() {return m_Metric;}
    void SetMetric(Metric metric) {m_Metric=metric;}

    unsigned int GetOptimizerMaximumIterations() {return m_OptimizerMaximumIterations;}
    void SetOptimizerMaximumIterations(unsigned int OptimizerMaximumIterations) {m_OptimizerMaximumIterations=OptimizerMaximumIterations;}

    double GetSearchRadius() {return m_SearchRadius;}
    void SetSearchRadius(double SearchRadius) {m_SearchRadius=SearchRadius;}

    double GetSearchAngleRadius() {return m_SearchAngleRadius;}
    void SetSearchAngleRadius(double SearchAngleRadius) {m_SearchAngleRadius=SearchAngleRadius;}

    double GetFinalRadius() {return m_FinalRadius;}
    void SetFinalRadius(double FinalRadius) {m_FinalRadius=FinalRadius;}

    double GetHistogramSize() {return m_HistogramSize;}
    void SetHistogramSize(double HistogramSize) {m_HistogramSize = HistogramSize;}

    unsigned int GetNumberOfPyramidLevels() {return m_NumberOfPyramidLevels;}
    void SetNumberOfPyramidLevels(unsigned int NumberOfPyramidLevels) {m_NumberOfPyramidLevels=NumberOfPyramidLevels;}

    void SetFastRegistration(bool arg) {m_FastRegistration = arg;}

    void SetRefSymmetryTransform(BaseTransformType *trsf) {m_RefSymmetryTransform = trsf;}
    void SetFloSymmetryTransform(BaseTransformType *trsf) {m_FloSymmetryTransform = trsf;}

protected:
    PyramidalSymmetryConstrainedRegistrationBridge();
    virtual ~PyramidalSymmetryConstrainedRegistrationBridge();

    void SetupPyramids();

private:
    //Symmetry constrained transform
    TransformPointer m_OutputTransform;
    BaseTransformPointer m_OutputRealignTransform;

    //Transform to realign image onto its mid-sagittal plane
    BaseTransformPointer m_RefSymmetryTransform, m_FloSymmetryTransform, m_InitialTransform;

    InputImagePointer m_OutputImage;

    Metric m_Metric;

    double m_SearchRadius;
    double m_SearchAngleRadius;
    double m_FinalRadius;
    unsigned int m_OptimizerMaximumIterations;
    unsigned int m_HistogramSize;
    unsigned int m_NumberOfPyramidLevels;
    bool m_FastRegistration;

    std::string m_outputTransformFile;
    std::string m_resultFile;

    InputImagePointer m_ReferenceImage, m_FloatingImage;
    PyramidPointer m_ReferencePyramid, m_FloatingPyramid;
};

} // end of namespace anima

#include "animaPyramidalSymmetryConstrainedRegistrationBridge.hxx"
