#include "orchid.h"

namespace Orchid {

static QColor getColorFromPallete(const QPalette& pal, const Color color, const State& state);
static QColor getColorHardcoded(const QPalette& pal, const Color color, const State& state);

using CRole = QPalette::ColorRole;
using CGroup = QPalette::ColorGroup;

const QColor getColor(const QPalette& pal, const Color color, const State& state) {
    return getColorFromPallete(pal, color, state);
}

const QBrush getBrush(const QPalette& pal, const Color color, const State& state) {
    return QBrush(getColor(pal, color, state));
}

const QPen getPen(const QPalette& pal, const Color color, const State& state, const qreal penWidth) {
    return QPen(QBrush(getColor(pal, color, state)), penWidth);
}
const QPen getPen(const QPalette& pal, const Color color, const qreal penWidth) {
    return QPen(QBrush(getColor(pal, color)), penWidth);
}

static QColor getColorFromPallete(const QPalette& pal, const Color color, const State& state) {
    switch (color) {
        case menuSeparator:
        case outline: {
            const auto base = pal.color(CGroup::Normal, CRole::Base);
            return isDarkMode(pal) ? base.lighter(180) : base.darker(180);
        }
        case toolBtnBackground:
        case button: {
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Button);

            const auto base = pal.color(CGroup::Normal, CRole::Button);
            if (state.pressed)
                return isDarkMode(pal) ? base.lighter(140) : base.darker(140);
            if (state.hovered)
                return isDarkMode(pal) ? base.lighter(120) : base.darker(120);
            return base;
        }

        case toolBtnBackgroundChecked:
        case toggleButtonChecked:
            return pal.color(CGroup::Normal, CRole::Accent);

        case checkBoxCheck:
            return pal.color(CGroup::Normal, CRole::Window);

        case checkBoxOutline: {
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Text);
            const auto base = pal.color(CGroup::Normal, CRole::Text);
            return isDarkMode(pal) ? base.darker(120) : base.lighter(120);
        }
        case checkBoxInside: {
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Text);
            return isDarkMode(pal) ? QColor(129, 201, 149) : QColor(14, 156, 87);
        }
        case checkBoxHoverCircle: {
            QColor base = getColor(pal, Color::checkBoxInside, state);

            if (state.pressed) {
                base.setAlpha(40);
                return base;
            }

            base.setAlpha(20);
            return base;
        }

        case tabCheckedFill:
            return getColor(pal, Color::tabWidgetPageArea);

        case tabCheckedOutline:
            return getColor(pal, Color::outline);

        case tabUncheckedHover:
            return getColor(pal, Color::tabCheckedFill);

        case tabWidgetPageArea:
            return pal.color(CGroup::Normal, CRole::Base);

        case scrollBarHoverBackground: {
            const auto base = pal.color(CGroup::Normal, CRole::Base);
            return isDarkMode(pal) ? base.lighter(120) : base.darker(120);
        }

        case scrollBarHoverOutline:
            return getColor(pal, Color::outline);

        case scrollBarSlider: {
            const auto base = getColor(pal, Color::scrollBarHoverBackground);
            if (!state.enabled)
                return base;
            if (state.pressed)
                return isDarkMode(pal) ? base.lighter(250) : base.darker(250);
            if (state.hovered)
                return isDarkMode(pal) ? base.lighter(240) : base.darker(240);
            return isDarkMode(pal) ? base.lighter(230) : base.darker(130);
        }

        case sliderHandle:
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Accent);
            return pal.color(CGroup::Normal, CRole::Accent);

        case sliderHandleHoverCircle: {
            auto base = pal.color(CGroup::Normal, CRole::Accent);
            if (state.pressed) {
                base.setAlpha(80);
                return base;
            }
            base.setAlpha(50);
            return base;
        }

        case sliderLineBefore:
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Accent);
            return pal.color(CGroup::Normal, CRole::Accent);

        case sliderLineAfter: {
            const auto base = pal.color(CGroup::Disabled, CRole::Accent);
            if (!state.enabled)
                return isDarkMode(pal) ? base.darker(110) : base.lighter(110);
            return isDarkMode(pal) ? base.lighter(180) : base.darker(180);
        }
        case sliderTickmarks:
            return getColor(pal, sliderLineAfter);

        case lineEditBackground:
        case spinBoxBackground:
        case comboBoxBackground:
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Button);
            return pal.color(CGroup::Normal, CRole::Button);

        case lineEditOutline:
        case spinBoxOutline: {
            if (!state.enabled)
                return getColor(pal, lineEditBackground, state);
            if (state.hasFocus)
                return pal.color(CGroup::Normal, CRole::Accent);
            const QColor base = getColor(pal, lineEditBackground, state);

            if (state.hovered)
                return isDarkMode(pal) ? base.lighter(140) : base.darker(140);

            return base;
        }

        case spinBoxIndicator: {
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Text);
            const QColor base = pal.color(CGroup::Normal, CRole::Text);
            if (state.pressed)
                return isDarkMode(pal) ? base.lighter(150) : base.darker(150);
            if (state.hovered)
                return isDarkMode(pal) ? base.lighter(130) : base.darker(130);
            return base;
        }
        case spinBoxIndicatorHoverCircle: {
            QColor base = pal.color(CGroup::Normal, CRole::Text);
            if (state.pressed) {
                base.setAlpha(100);
                return base;
            }
            if (state.hovered) {
                base.setAlpha(40);
                return base;
            }
            return base;
        }

        case comboBoxOutline: {
            if (!state.enabled)
                return getColor(pal, lineEditBackground, state);
            if (state.pressed || state.hasFocus)
                return pal.color(CGroup::Normal, CRole::Accent);

            const QColor base = getColor(pal, lineEditBackground, state);

            if (state.hovered)
                return isDarkMode(pal) ? base.lighter(140) : base.darker(140);

            return base;
        }

        case menuText:
        case menuBarItemText:
        case comboBoxUneditableText:
        case toolBtnText:
        case progressBarText:
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Text);
            return pal.color(CGroup::Normal, CRole::Text);

        case menuShortcutText:
            if (isDarkMode(pal))
                return getColor(pal, Color::menuText, state).darker(130);
            return getColor(pal, Color::menuText, state).lighter(130);

        case menuBackground: {
            QColor base = pal.color(CGroup::Normal, CRole::AlternateBase);
            base.setAlpha(Constants::menuTransparency);
            return base;
        }

        case menuItemHoverBackground:
        case menuBarItemHoverBg:
            return isDarkMode(pal) ? QColor(255, 255, 255, 26) : QColor(0, 0, 0, 26);

        case toolBarBackground:
        case menuBarBackground:
            if (!state.enabled)
                return pal.color(CGroup::Disabled, CRole::Base);
            return pal.color(CGroup::Normal, CRole::Base);

        case toolBarHandle:
        case toolBarSeparator: {
            const QColor base = getColor(pal, Color::outline, state);
            return isDarkMode(pal) ? base.lighter(140) : base.darker(140);
        }

        case toolBtnBackgroundAutoRise:
            if (!state.enabled)
                return QColor(Qt::transparent);

            if (state.pressed)
                return isDarkMode(pal) ? QColor(255, 255, 255, 40) : QColor(0, 0, 0, 40);
            if (state.hovered)
                return isDarkMode(pal) ? QColor(255, 255, 255, 30) : QColor(0, 0, 0, 30);
            return QColor(Qt::transparent);

        case toolBtnBackgroundAutoRiseChecked: {
            if (!state.enabled) {
                QColor base = pal.color(CGroup::Normal, CRole::Button);
                base.setAlpha(120);
                return base;
            }
            if (state.pressed)
                return isDarkMode(pal) ? QColor(255, 255, 255, 45) : QColor(0, 0, 0, 45);
            if (state.hovered)
                return isDarkMode(pal) ? QColor(255, 255, 255, 38) : QColor(0, 0, 0, 38);
            return isDarkMode(pal) ? QColor(255, 255, 255, 26) : QColor(0, 0, 0, 26);
        }

        case toolBtnMenuSeparator:
            if (!state.enabled)
                return isDarkMode(pal) ? pal.color(CGroup::Disabled, CRole::Button).lighter(130) :
                                         pal.color(CGroup::Disabled, CRole::Button).darker(130);
            return isDarkMode(pal) ? pal.color(CGroup::Normal, CRole::Button).lighter(200) :
                                     pal.color(CGroup::Normal, CRole::Button).darker(200);

        case toolBtnFocusOutline:
            return pal.color(CGroup::Normal, CRole::Accent);

        case indicatorArrow:
            return pal.color(state.enabled ? CGroup::Normal : CGroup::Disabled, CRole::Text);

        case progressBarIndicator:
            return pal.color(state.enabled ? CGroup::Normal : CGroup::Disabled, CRole::Accent);

        case progressBarIndicatorBackground:
            return pal.color(state.enabled ? CGroup::Normal : CGroup::Disabled, CRole::Button);

        case branchIndicator:
            return isDarkMode(pal) ? pal.color(CGroup::Normal, CRole::Text).darker(190) : pal.color(CGroup::Normal, CRole::Text).lighter(190);

        case focusColor:
            return pal.color(CGroup::Normal, CRole::Highlight);

        default:
            break;
    }
    return QColor(Qt::red);
}

State::State(const QStyle::State& state) {
    enabled = state & QStyle::State_Enabled;
    hovered = state & QStyle::State_MouseOver;
    pressed = state & QStyle::State_Sunken;
    hasFocus = state & QStyle::State_HasFocus;
}

bool isDarkMode(const QPalette& pal) {
    return pal.color(QPalette::ColorRole::Window).lightness() < pal.color(QPalette::ColorRole::Text).lightness();
}

} // namespace Orchid
