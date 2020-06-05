#include "toolbarbutton.h"

#include "toolbargroup.h"

using namespace lc::ui::api;

ToolbarButton::ToolbarButton(const char* buttonLabel, const char* icon, kaguya::LuaRef callback, const char* tooltip, bool checkable, QWidget* parent)
    :
    ToolbarButton(buttonLabel, icon, tooltip, checkable, parent)
{
    callbacks.push_back(callback);
}

ToolbarButton::ToolbarButton(const char* buttonLabel, const char* icon, const char* tooltip, bool checkable, QWidget* parent)
    :
    _label(buttonLabel),
    QPushButton("", parent),
    luaInterface(nullptr),
    checkable(checkable)
{
    this->setObjectName(buttonLabel);
    if (tooltip == "") {
        this->setToolTip(buttonLabel);
    }
    else {
        this->setToolTip(tooltip);
    }
    this->setFlat(true);

    if (checkable) {
        this->setCheckable(true);
    }

    changeIcon(icon);
}

std::string ToolbarButton::label() {
    return _label;
}

void ToolbarButton::setLabel(const char* newLabel) {
    _label = std::string(newLabel);
}

void ToolbarButton::setTooltip(const char* newToolTip) {
    this->setToolTip(newToolTip);
}

void ToolbarButton::addCallback(kaguya::LuaRef callback) {
    callbacks.push_back(callback);

    if (luaInterface != nullptr) {
        connectToCallback(callback);
    }
}

void ToolbarButton::changeIcon(const char* icon) {
    if (icon != nullptr) {
        this->setIcon(QIcon(icon));
        this->setIconSize(QSize(24, 24));
    }
}

void ToolbarButton::remove() {
    ToolbarGroup* toolbarGroup = static_cast<ToolbarGroup*>(this->parent());
    auto gridLayout = static_cast<QGridLayout*>(toolbarGroup->layout());
    gridLayout->removeWidget(this);
}

void ToolbarButton::setLuaInterface(LuaInterface* luaInterfaceIn) {
    if (luaInterface != nullptr) {
        return;
    }

    luaInterface = luaInterfaceIn;

    // loop through all already added callbacks and connect them
    for (kaguya::LuaRef cb : callbacks)
    {
        connectToCallback(cb);
    }
}

void ToolbarButton::connectToCallback(kaguya::LuaRef callback) {
    if (checkable) {
        luaInterface->luaConnect(this, "toggled(bool)", callback);
    }
    else {
        luaInterface->luaConnect(this, "pressed()", callback);
    }
}