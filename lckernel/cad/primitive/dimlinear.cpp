#include "cad/primitive/dimlinear.h"
#include "dimlinear.h"


using namespace lc;
using namespace entity;

DimLinear::DimLinear(geo::Coordinate definitionPoint,
                     geo::Coordinate middleOfText,
                     TextConst::AttachmentPoint attachmentPoint,
                     double textAngle,
                     double lineSpacingFactor,
                     TextConst::LineSpacingStyle lineSpacingStyle,
                     std::string explicitValue,
                     geo::Coordinate definitionPoint2,
                     geo::Coordinate definitionPoint3,
                     double angle,
                     double oblique,
                     meta::Layer_CSPtr layer,
                     meta::MetaInfo_CSPtr metaInfo,
                     meta::Block_CSPtr block) :
    CADEntity(std::move(layer), std::move(metaInfo), std::move(block)),
    Dimension(std::move(definitionPoint),
              std::move(middleOfText),
              attachmentPoint,
              textAngle,
              lineSpacingFactor,
              lineSpacingStyle,
              std::move(explicitValue)),
    _angle(angle),
    _oblique(oblique),
    _definitionPoint2(std::move(definitionPoint2)),
    _definitionPoint3(std::move(definitionPoint3)) {
}


DimLinear::DimLinear(const DimLinear_CSPtr& other, bool sameID) :
    CADEntity(other, sameID),
    Dimension(*other),
    _angle(other->_angle),
    _oblique(other->_oblique),
    _definitionPoint2(other->_definitionPoint2),
    _definitionPoint3(other->_definitionPoint3) {
}

DimLinear::DimLinear(const lc::builder::DimLinearBuilder& builder) :
    CADEntity(builder),
    Dimension(builder),
    _angle(builder.angle()),
    _oblique(builder.oblique()),
    _definitionPoint2(builder.definitionPoint2()),
    _definitionPoint3(builder.definitionPoint3()) {
}

CADEntity_CSPtr DimLinear::move(const geo::Coordinate& offset) const {
    auto newDimLinear = std::make_shared<DimLinear>(this->definitionPoint() + offset,
                        this->middleOfText() + offset,
                        this->attachmentPoint(),
                        this->textAngle(),
                        this->lineSpacingFactor(),
                        this->lineSpacingStyle(),
                        this->explicitValue(),
                        this->_definitionPoint2 + offset,
                        this->_definitionPoint3 + offset,
                        this->_angle,
                        this->_oblique,
                        this->layer(), metaInfo(), block()
                                                   );
    newDimLinear->setID(this->id());
    return newDimLinear;
}

CADEntity_CSPtr DimLinear::copy(const geo::Coordinate& offset) const {
    auto newDimLinear = std::make_shared<DimLinear>(this->definitionPoint() + offset,
                        this->middleOfText() + offset,
                        this->attachmentPoint(),
                        this->textAngle(),
                        this->lineSpacingFactor(),
                        this->lineSpacingStyle(),
                        this->explicitValue(),
                        this->_definitionPoint2 + offset,
                        this->_definitionPoint3 + offset,
                        this->_angle,
                        this->_oblique,
                        this->layer(), metaInfo(), block()
                                                   );
    return newDimLinear;
}

CADEntity_CSPtr DimLinear::rotate(const geo::Coordinate& rotation_center, double rotation_angle) const {
    auto newDimLinear = std::make_shared<DimLinear>(this->definitionPoint().rotate(rotation_center, rotation_angle),
                        this->middleOfText().rotate(rotation_center, rotation_angle),
                        this->attachmentPoint(),
                        this->textAngle(),
                        this->lineSpacingFactor(),
                        this->lineSpacingStyle(),
                        this->explicitValue(),
                        this->_definitionPoint2.rotate(rotation_center, rotation_angle),
                        this->_definitionPoint3.rotate(rotation_center, rotation_angle),
                        this->_angle,
                        this->_oblique,
                        this->layer(), metaInfo(), block()
                                                   );
    newDimLinear->setID(this->id());
    return newDimLinear;
}

CADEntity_CSPtr DimLinear::scale(const geo::Coordinate& scale_center, const geo::Coordinate& scale_factor) const {
    auto newDimLinear = std::make_shared<DimLinear>(this->definitionPoint().scale(scale_center, scale_factor),
                        this->middleOfText().scale(scale_center, scale_factor),
                        this->attachmentPoint(),
                        this->textAngle(),
                        this->lineSpacingFactor(),
                        this->lineSpacingStyle(),
                        this->explicitValue(),
                        this->_definitionPoint2.scale(scale_center, scale_factor),
                        this->_definitionPoint3.scale(scale_center, scale_factor),
                        this->_angle,
                        this->_oblique,
                        this->layer(), metaInfo(), block()
                                                   );
    newDimLinear->setID(this->id());
    return newDimLinear;
}

const geo::Area DimLinear::boundingBox() const {
    lc::geo::Coordinate minPoints = lc::geo::Coordinate(std::min(definitionPoint().x(), std::min(definitionPoint2().x(), definitionPoint3().x())), std::min(definitionPoint().y(), std::min(definitionPoint2().y(), definitionPoint3().y())));
    lc::geo::Coordinate maxPoints = lc::geo::Coordinate(std::max(definitionPoint().x(), std::max(definitionPoint2().x(), definitionPoint3().x())), std::max(definitionPoint().y(), std::max(definitionPoint2().y(), definitionPoint3().y())));
    return geo::Area(minPoints, maxPoints);
}

CADEntity_CSPtr DimLinear::modify(meta::Layer_CSPtr layer, meta::MetaInfo_CSPtr metaInfo, meta::Block_CSPtr block) const {
    auto newDimLinear = std::make_shared<DimLinear>(
                            this->definitionPoint(),
                            this->middleOfText(),
                            this->attachmentPoint(),
                            this->textAngle(),
                            this->lineSpacingFactor(),
                            this->lineSpacingStyle(),
                            this->explicitValue(),
                            this->_definitionPoint2,
                            this->_definitionPoint3,
                            this->_angle,
                            this->_oblique,
                            layer,
                            metaInfo,
                            block
                        );
    newDimLinear->setID(this->id());
    return newDimLinear;
}

double DimLinear::angle() const {
    return _angle;
}
double DimLinear::oblique() const {
    return _oblique;
}

const geo::Coordinate& DimLinear::definitionPoint2() const noexcept {
    return _definitionPoint2;
}
const geo::Coordinate& DimLinear::definitionPoint3() const noexcept {
    return _definitionPoint3;
}

std::map<unsigned int, geo::Coordinate> DimLinear::dragPoints() const {
    std::map<unsigned int, geo::Coordinate> dragPoints;

    dragPoints[0] = definitionPoint();
    dragPoints[1] = middleOfText();
    dragPoints[2] = definitionPoint2();
    dragPoints[3] = definitionPoint3();

    return dragPoints;
}


CADEntity_CSPtr DimLinear::setDragPoints(std::map<unsigned int, lc::geo::Coordinate> dragPoints) const {
    try {
        auto newEntity = std::make_shared<DimLinear>(dragPoints.at(0),
                         dragPoints.at(1),
                         attachmentPoint(),
                         textAngle(),
                         lineSpacingFactor(),
                         lineSpacingStyle(),
                         explicitValue(),
                         dragPoints.at(2),
                         dragPoints.at(3),
                         angle(),
                         oblique(),
                         layer(), metaInfo(), block());
        newEntity->setID(id());
        return newEntity;
    }
    catch(std::out_of_range& e) {
        return shared_from_this();
    }
}

PropertiesMap DimLinear::availableProperties() const {
    PropertiesMap propertyValues;

    getDimensionProperties(propertyValues);
    propertyValues["definitionPoint2"] = this->definitionPoint2();
    propertyValues["definitionPoint3"] = this->definitionPoint3();
    propertyValues["angle"] = this->angle();
    propertyValues["oblique"] = this->oblique();

    return propertyValues;
}

CADEntity_CSPtr DimLinear::setProperties(const PropertiesMap& propertiesMap) const {
    lc::geo::Coordinate definitionPointp, middleOfTextp;
    double textAnglep, lineSpacingFactorp;
    std::string explicitValuep;
    lc::geo::Coordinate definitionPoint2p = this->definitionPoint2();
    lc::geo::Coordinate definitionPoint3p = this->definitionPoint3();
    double anglep = this->angle();
    double obliquep = this->oblique();

    setDimensionProperties(propertiesMap, definitionPointp, middleOfTextp, textAnglep, lineSpacingFactorp, explicitValuep);

    for (auto iter = propertiesMap.begin(); iter != propertiesMap.end(); ++iter)
    {
        if (iter->first == "definitionPoint2") {
            definitionPoint2p = boost::get<lc::geo::Coordinate>(iter->second);
        }

        if (iter->first == "angle") {
            anglep = boost::get<double>(iter->second);
        }

        if (iter->first == "oblique") {
            obliquep = boost::get<double>(iter->second);
        }
    }

    auto newDimLin = std::make_shared<DimLinear>(definitionPointp, middleOfTextp, attachmentPoint(), textAnglep, lineSpacingFactorp,
                     lineSpacingStyle(), explicitValuep, definitionPoint2p, definitionPoint3p, anglep, obliquep, layer(), metaInfo(), block());
    newDimLin->setID(this->id());
    return newDimLin;
}
